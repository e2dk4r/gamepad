#include <liburing.h>

#include <fcntl.h>
#include <libudev.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POLLIN 0x001  /* There is data to read.  */
#define POLLPRI 0x002 /* There is urgent data to read.  */
#define POLLOUT 0x004 /* Writing now will not block.  */

typedef unsigned char u8;

#define OP_UDEV_MONITOR (1 << 0)
#define OP_JOYSTICK_POLL (1 << 1)
#define OP_JOYSTICK_READ (1 << 2)
#define OP_JOYSTICK_CLOSE (1 << 3)

struct op {
  u8 type;
  int fd;
};

struct op_joystick {
  u8 type;
  int fd;
  const char *path;
};

struct op_joystick_read {
  u8 type;
  int fd;
  struct input_event event;
};

#define JOYSTICK_PATH_MAX 32
struct JoystickInfo {
  char path[JOYSTICK_PATH_MAX];
  u8 path_length;
};
/*
 * returns 0 when no joystick found
 */
u8 enumarateJoysticks(u8 *pCount, struct JoystickInfo *infos);
u8 enumarateJoysticks(u8 *pCount, struct JoystickInfo *infos) {
  u8 joystickCount = 0;
  struct udev *udev = udev_new();
  struct udev_enumerate *udev_enumerate = udev_enumerate_new(udev);
  udev_enumerate_add_match_subsystem(udev_enumerate, "input");
  udev_enumerate_add_match_property(udev_enumerate, "ID_INPUT_JOYSTICK", "1");

  if (udev_enumerate_scan_devices(udev_enumerate) < 0) {
    goto exit;
  }

  struct udev_list_entry *devices =
      udev_enumerate_get_list_entry(udev_enumerate);
  struct udev_list_entry *entry;

  for (entry = devices; entry; entry = udev_list_entry_get_next(entry)) {
    const char *path = udev_list_entry_get_name(entry);
    struct udev_device *udev_device = udev_device_new_from_syspath(udev, path);
    const char *devnode = udev_device_get_devnode(udev_device);
    /* /dev/input/eventXX not found */
    if (!devnode) {
      continue;
    }

    /* device found */
    if (infos) {
      struct JoystickInfo *info = &infos[joystickCount];

      size_t devnode_length = 0;
      while (devnode[devnode_length] && devnode_length < JOYSTICK_PATH_MAX)
        devnode_length++;

      info->path_length = devnode_length;
      for (size_t index = 0;
           index < devnode_length && index < JOYSTICK_PATH_MAX; index++) {
        info->path[index] = devnode[index];
      }

      info->path[info->path_length] = 0;
    }

    joystickCount++;
  }

  *pCount = joystickCount;

exit:
  udev_enumerate_unref(udev_enumerate);
  udev_unref(udev);
  return joystickCount != 0;
}

int main(void) {
  struct io_uring ring;
  if (io_uring_queue_init(4, &ring, 0))
    return 1;

  struct udev *udev = udev_new();
  if (!udev)
    return 1;

  struct udev_monitor *udev_monitor =
      udev_monitor_new_from_netlink(udev, "udev");
  if (!udev_monitor)
    return 1;

  if (udev_monitor_enable_receiving(udev_monitor) < 0)
    return 1;

  if (udev_monitor_filter_add_match_subsystem_devtype(udev_monitor, "input",
                                                      0) < 0)
    return 1;

  int fd_udev = udev_monitor_get_fd(udev_monitor);
  if (fd_udev < 0)
    return 1;

  struct io_uring_sqe *sqe = io_uring_get_sqe(&ring);
  io_uring_prep_poll_multishot(sqe, fd_udev, POLLIN);
  io_uring_sqe_set_data(sqe,
                        &(struct op){.type = OP_UDEV_MONITOR, .fd = fd_udev});

  io_uring_submit(&ring);

  /* add already connected joysticks to queue */
  static struct JoystickInfo joystickInfos[4] = {};
  u8 joystickCount = 1;

  if (enumarateJoysticks(&joystickCount, 0) == 0)
    return 0;

  if (joystickCount > 4) {
    printf("too many joysticks\n");
    return 2;
  }

  if (enumarateJoysticks(&joystickCount, joystickInfos) == 0)
    return 1;

  printf("count: %d\n", joystickCount);
  for (u8 joystickIndex = 0; joystickIndex < joystickCount; joystickIndex++) {
    printf("joystick #%u %s\n", joystickIndex,
           joystickInfos[joystickIndex].path);
    struct op_joystick_read *op = &(struct op_joystick_read){
        .type = OP_JOYSTICK_READ,
    };

    op->fd = open(joystickInfos[joystickIndex].path, O_RDONLY);
    if (op->fd < 0)
      return 1;

    int flags = fcntl(op->fd, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(op->fd, F_SETFL, flags);

    struct io_uring_sqe *sqe = io_uring_get_sqe(&ring);
    io_uring_prep_read(sqe, op->fd, &op->event, sizeof(op->event), 0);
    io_uring_sqe_set_data(sqe, op);
    io_uring_submit(&ring);
  }

#define MAX_INPUT_EVENT 1024
  struct input_event event[MAX_INPUT_EVENT];
  struct iovec *iovecs = malloc(MAX_INPUT_EVENT * sizeof(*iovecs));
  for (size_t index = 0; index < MAX_INPUT_EVENT; index++) {
    struct iovec *iovec = &iovecs[index];
    iovec->iov_base = &event[index];
    iovec->iov_len = sizeof(struct input_event);
  }

  struct io_uring_cqe *cqe;
  while (1) {
    int error = io_uring_wait_cqe(&ring, &cqe);
    if (error) {
      write(2, "err: io_uring\n", 14);
      break;
    }

    struct op *op = io_uring_cqe_get_data(cqe);
    if (op == 0)
      goto cqe_seen;

    /* on udev monitor error, finish the program */
    if (op->type & OP_UDEV_MONITOR && cqe->res < 0) {
      write(2, "err: udev\n", 10);
      break;
    }

    /* on joystick read error (eg. joystick removed), close the fd */
    if (op->type & OP_JOYSTICK_READ && cqe->res < 0) {
      if (op->fd >= 0)
        close(op->fd);
      op->fd = -1;
      goto cqe_seen;
    }

    /* on udev events */
    if (op->type & OP_UDEV_MONITOR) {
      int revents = cqe->res;

      if (!(revents & POLLIN)) {
        write(2, "err: udev\n", 10);
        break;
      }

      struct udev_device *udev_device =
          udev_monitor_receive_device(udev_monitor);
      const char *devnode = udev_device_get_devnode(udev_device);
      if (!devnode)
        goto cqe_seen;

      struct udev_list_entry *properties =
          udev_device_get_properties_list_entry(udev_device);
      struct udev_list_entry *property;

      u8 isJoystick = 0;
      u8 action = 0;
#define ACTION_ADD (1 << 0)
#define ACTION_REMOVE (1 << 1)
      udev_list_entry_foreach(property, properties) {
        const char *name = udev_list_entry_get_name(property);
        const char *value = udev_list_entry_get_value(property);

        if (strcmp(name, "ACTION") == 0 && strcmp(value, "add") == 0) {
          action = ACTION_ADD;
        }

        if (strcmp(name, "ACTION") == 0 && strcmp(value, "remove") == 0) {
          action = ACTION_REMOVE;
        }

        if (strcmp(name, "ID_INPUT_JOYSTICK") == 0 && strcmp(value, "1") == 0) {
          isJoystick = 1;
        }
      }

      if (!isJoystick)
        goto cqe_seen;

      if (action & ACTION_ADD) {
        struct op_joystick_read *op = &(struct op_joystick_read){
            .type = OP_JOYSTICK_READ,
        };

        op->fd = open(devnode, O_RDONLY);
        if (op->fd < 0)
          goto cqe_seen;

        int flags = fcntl(op->fd, F_GETFL);
        if (flags < 0)
          goto cqe_seen;
        flags |= O_NONBLOCK;
        flags = fcntl(op->fd, F_SETFL, flags);
        if (flags < 0)
          goto cqe_seen;

        sqe = io_uring_get_sqe(&ring);
        io_uring_prep_read(sqe, op->fd, &op->event, sizeof(op->event), 0);
        io_uring_sqe_set_data(sqe, op);
        io_uring_submit(&ring);

        printf("added devnode %s\n", devnode);
      } else if (action & ACTION_REMOVE) {
        printf("removed devnode %s\n", devnode);
      }
    }

    else if (op->type & OP_JOYSTICK_READ) {
      struct op_joystick_read *op = io_uring_cqe_get_data(cqe);

      struct input_event *event = &op->event;
      printf("fd: %d time: %ld.%ld type: %d code: %d value: %d\n", op->fd,
             event->input_event_sec, event->input_event_usec, event->type, event->code,
             event->value);

      struct io_uring_sqe *sqe = io_uring_get_sqe(&ring);
      io_uring_prep_read(sqe, op->fd, &op->event, sizeof(op->event), 0);
      io_uring_sqe_set_data(sqe, op);
      io_uring_submit(&ring);
    }

  cqe_seen:
    io_uring_cqe_seen(&ring, cqe);
  }

  io_uring_queue_exit(&ring);

  return 0;
}
