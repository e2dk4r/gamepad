#include <liburing.h>

#include <fcntl.h>
#include <libudev.h>
#include <linux/input.h>
#include <stdio.h>
#include <string.h>

#define POLLIN 0x001  /* There is data to read.  */
#define POLLPRI 0x002 /* There is urgent data to read.  */
#define POLLOUT 0x004 /* Writing now will not block.  */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#define OP_UDEV_MONITOR (1 << 0)
#define OP_JOYSTICK_POLL (1 << 1)
#define OP_JOYSTICK_READ (1 << 2)
#define OP_JOYSTICK_CLOSE (1 << 3)

#define GAMEPAD_ERROR_IO_URING_SETUP 1
#define GAMEPAD_ERROR_IO_URING_WAIT 2
#define GAMEPAD_ERROR_UDEV_SETUP 3
#define GAMEPAD_ERROR_UDEV_MONITOR 4
#define GAMEPAD_ERROR_UDEV_POLL 5

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
  u8 initialized : 1;
  u16 connectedAt;
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
  int error_code = 0;

  struct io_uring ring;
  if (io_uring_queue_init(4, &ring, 0)) {
    error_code = GAMEPAD_ERROR_IO_URING_SETUP;
    goto exit;
  }

  struct udev *udev = udev_new();
  if (!udev) {
    error_code = GAMEPAD_ERROR_UDEV_SETUP;
    goto io_uring_exit;
  }

  struct udev_monitor *udev_monitor =
      udev_monitor_new_from_netlink(udev, "udev");
  if (!udev_monitor) {
    error_code = GAMEPAD_ERROR_UDEV_SETUP;
    goto udev_exit;
  }

  if (udev_monitor_enable_receiving(udev_monitor) < 0) {
    error_code = GAMEPAD_ERROR_UDEV_SETUP;
    goto udev_monitor_exit;
  }

  if (udev_monitor_filter_add_match_subsystem_devtype(udev_monitor, "input",
                                                      0) < 0) {
    error_code = GAMEPAD_ERROR_UDEV_SETUP;
    goto udev_monitor_exit;
  }

  int fd_udev = udev_monitor_get_fd(udev_monitor);
  if (fd_udev < 0) {
    error_code = GAMEPAD_ERROR_UDEV_SETUP;
    goto udev_monitor_exit;
  }

  struct io_uring_sqe *sqe = io_uring_get_sqe(&ring);
  io_uring_prep_poll_multishot(sqe, fd_udev, POLLIN);
  io_uring_sqe_set_data(sqe,
                        &(struct op){.type = OP_UDEV_MONITOR, .fd = fd_udev});

  /* add already connected joysticks to queue */
  struct udev_enumerate *udev_enumerate = udev_enumerate_new(udev);
  udev_enumerate_add_match_subsystem(udev_enumerate, "input");
  udev_enumerate_add_match_property(udev_enumerate, "ID_INPUT_JOYSTICK", "1");

  if (udev_enumerate_scan_devices(udev_enumerate) >= 0) {
    struct udev_list_entry *devices =
        udev_enumerate_get_list_entry(udev_enumerate);
    struct udev_list_entry *entry;

    for (entry = devices; entry; entry = udev_list_entry_get_next(entry)) {
      const char *syspath = udev_list_entry_get_name(entry);
      struct udev_device *udev_device =
          udev_device_new_from_syspath(udev, syspath);
      if (!udev_device)
        continue;
      const char *devnode = udev_device_get_devnode(udev_device);

      /* /dev/input/eventXX not found */
      if (!devnode) {
        udev_device_unref(udev_device);
        continue;
      }

      struct op_joystick_read *op = &(struct op_joystick_read){
          .type = OP_JOYSTICK_READ,
          /* already initialized */
          .initialized = 1,
      };

      op->fd = open(devnode, O_RDONLY);
      if (op->fd < 0)
        return 1;

      int flags = fcntl(op->fd, F_GETFL);
      flags |= O_NONBLOCK;
      fcntl(op->fd, F_SETFL, flags);

      struct io_uring_sqe *sqe = io_uring_get_sqe(&ring);
      io_uring_prep_read(sqe, op->fd, &op->event, sizeof(op->event), 0);
      io_uring_sqe_set_data(sqe, op);

      udev_device_unref(udev_device);
    }
  }
  udev_enumerate_unref(udev_enumerate);
  udev_enumerate = 0;

  /* submit any work */
  io_uring_submit(&ring);

  /* event loop */
  struct io_uring_cqe *cqe;
  while (1) {
    int error = io_uring_wait_cqe(&ring, &cqe);
    if (error) {
      write(2, "err: io_uring\n", 14);
      error_code = GAMEPAD_ERROR_IO_URING_WAIT;
      break;
    }

    struct op *op = io_uring_cqe_get_data(cqe);
    if (op == 0)
      goto cqe_seen;

    /* on udev monitor error, finish the program */
    if (op->type & OP_UDEV_MONITOR && cqe->res < 0) {
      write(2, "err: udev\n", 10);
      error_code = GAMEPAD_ERROR_UDEV_MONITOR;
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
      if (!udev_device)
        goto cqe_seen;

      const char *devnode = udev_device_get_devnode(udev_device);
      if (!devnode)
        goto op_monitor_exit;

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
        goto op_monitor_exit;

      if (action & ACTION_ADD) {
        struct op_joystick_read *op = &(struct op_joystick_read){
            .type = OP_JOYSTICK_READ,
        };

        op->fd = open(devnode, O_RDONLY);
        if (op->fd < 0) {
          goto op_monitor_exit;
        }

        int flags = fcntl(op->fd, F_GETFL);
        if (flags < 0) {
          close(op->fd);
          goto op_monitor_exit;
        }
        flags |= O_NONBLOCK;
        flags = fcntl(op->fd, F_SETFL, flags);
        if (flags < 0) {
          close(op->fd);
          goto op_monitor_exit;
        }

        sqe = io_uring_get_sqe(&ring);
        io_uring_prep_read(sqe, op->fd, &op->event, sizeof(op->event), 0);
        io_uring_sqe_set_data(sqe, op);
        io_uring_submit(&ring);

        printf("added devnode %s\n", devnode);
      } else if (action & ACTION_REMOVE) {
        printf("removed devnode %s\n", devnode);
      }

    op_monitor_exit:
      udev_device_unref(udev_device);
    }

    else if (op->type & OP_JOYSTICK_READ) {
      struct op_joystick_read *op = io_uring_cqe_get_data(cqe);
      struct input_event *event = &op->event;

      /* wait 1 second for joystick to become ready */
      if (!op->initialized) {
        if (op->connectedAt == 0)
          op->connectedAt = (u16)event->input_event_sec;
        if ((u16)event->input_event_sec - op->connectedAt == 0)
          goto readAgain;
        op->initialized = 1;
      }

      printf("fd: %d time: %ld.%ld type: %d code: %d value: %d\n", op->fd,
             event->input_event_sec, event->input_event_usec, event->type,
             event->code, event->value);

      struct io_uring_sqe *sqe;
    readAgain:
      sqe = io_uring_get_sqe(&ring);
      io_uring_prep_read(sqe, op->fd, &op->event, sizeof(op->event), 0);
      io_uring_sqe_set_data(sqe, op);
      io_uring_submit(&ring);
    }

  cqe_seen:
    io_uring_cqe_seen(&ring, cqe);
  }

udev_monitor_exit:
  udev_monitor_unref(udev_monitor);

udev_exit:
  udev_unref(udev);

io_uring_exit:
  io_uring_queue_exit(&ring);

exit:
  return error_code;
}
