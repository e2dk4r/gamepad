#include <liburing.h>

#include <dirent.h>
#include <fcntl.h>
#include <libevdev/libevdev.h>
#include <linux/input.h>
#include <stdio.h>
#include <sys/inotify.h>
#include <sys/ioctl.h>
#include <unistd.h>

#ifndef DT_CHR
#define DT_CHR 2
#endif

#define POLLIN 0x001  /* There is data to read.  */
#define POLLPRI 0x002 /* There is urgent data to read.  */
#define POLLOUT 0x004 /* Writing now will not block.  */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#define OP_INOTIFY_WATCH (1 << 0)
#define OP_DEVICE_OPEN (1 << 1)
#define OP_JOYSTICK_POLL (1 << 2)
#define OP_JOYSTICK_READ (1 << 3)
#define OP_JOYSTICK_CLOSE (1 << 4)

#define ACTION_ADD (1 << 0)
#define ACTION_REMOVE (1 << 1)

#define GAMEPAD_ERROR_IO_URING_SETUP 1
#define GAMEPAD_ERROR_IO_URING_WAIT 2

#define GAMEPAD_ERROR_INOTIFY_SETUP 10
#define GAMEPAD_ERROR_INOTIFY_WATCH_SETUP 11
#define GAMEPAD_ERROR_INOTIFY_WATCH 12
#define GAMEPAD_ERROR_INOTIFY_WATCH_POLL 12

#define GAMEPAD_ERROR_DEV_INPUT_DIR_OPEN 20
#define GAMEPAD_ERROR_DEV_INPUT_DIR_READ 21

#define GAMEPAD_ERROR_LIBEVDEV 30
#define GAMEPAD_ERROR_LIBEVDEV_FD 30

#define fatal(str) write(2, "e: " str, 3 + sizeof(str) - 1)
#define warning(str) write(2, "w: " str, 3 + sizeof(str) - 1)

struct op {
  u8 type;
  int fd;
};

struct op_device_open {
  u8 type;
  const char *path;
};

struct op_joystick_read {
  u8 type;
  u8 initialized : 1;
  u16 connectedAt;
  int fd;
  struct input_event event;
};

static inline u8 libevdev_is_joystick(struct libevdev *evdev) {
  return libevdev_has_event_type(evdev, EV_ABS) &&
         libevdev_has_event_code(evdev, EV_ABS, ABS_HAT0X);
}

int main(void) {
  int error_code = 0;

  struct io_uring ring;
  if (io_uring_queue_init(4, &ring, 0)) {
    error_code = GAMEPAD_ERROR_IO_URING_SETUP;
    goto exit;
  }

  /* notify when a new input added */
  int fd_inotify = inotify_init1(IN_NONBLOCK);
  if (fd_inotify < 0) {
    error_code = GAMEPAD_ERROR_INOTIFY_SETUP;
    goto io_uring_exit;
  }

  int fd_watch =
      inotify_add_watch(fd_inotify, "/dev/input", IN_CREATE | IN_DELETE);
  if (fd_watch < 0) {
    error_code = GAMEPAD_ERROR_INOTIFY_WATCH_SETUP;
    goto inotify_exit;
  }

  struct io_uring_sqe *sqe = io_uring_get_sqe(&ring);
  struct op *op = &(struct op){.type = OP_INOTIFY_WATCH, .fd = fd_inotify};
  io_uring_prep_poll_multishot(sqe, op->fd, POLLIN);
  io_uring_sqe_set_data(sqe, op);

  /* add already connected joysticks to queue */

  DIR *dir = opendir("/dev/input");
  if (dir == 0) {
    error_code = GAMEPAD_ERROR_DEV_INPUT_DIR_OPEN;
    goto inotify_watch_exit;
  }

  struct dirent *dirent;
  u32 dirent_max = 1024;
  while (dirent_max--) {
    errno = 0;
    dirent = readdir(dir);

    /* error occured */
    if (errno != 0) {
      error_code = GAMEPAD_ERROR_DEV_INPUT_DIR_READ;
      closedir(dir);
      goto inotify_watch_exit;
    }

    /* end of directory stream is reached */
    if (dirent == 0)
      break;

    if (dirent->d_type != DT_CHR)
      continue;

    /* get full path */
    char path[32] = "/dev/input/";
    for (char *dest = path + 11, *src = dirent->d_name; *src; src++, dest++) {
      *dest = *src;
    }

    struct op_joystick_read *op = &(struct op_joystick_read){
        .type = OP_JOYSTICK_READ,
    };

    op->fd = open(path, O_RDONLY | O_NONBLOCK);
    if (op->fd < 0)
      continue;

    struct libevdev *evdev;
    int rc = libevdev_new_from_fd(op->fd, &evdev);
    if (rc < 0) {
      warning("libevdev failed\n");
      close(op->fd);
      if (evdev)
        libevdev_free(evdev);
      continue;
    }

    /* detect joystick */
    if (!libevdev_is_joystick(evdev)) {
      close(op->fd);
      libevdev_free(evdev);
      continue;
    }

    printf("Input device name: \"%s\"\n", libevdev_get_name(evdev));
    printf("Input device ID: bus %#x vendor %#x product %#x\n",
           libevdev_get_id_bustype(evdev), libevdev_get_id_vendor(evdev),
           libevdev_get_id_product(evdev));

    struct io_uring_sqe *sqe = io_uring_get_sqe(&ring);
    io_uring_prep_read(sqe, op->fd, &op->event, sizeof(op->event), 0);
    io_uring_sqe_set_data(sqe, op);

    libevdev_free(evdev);
  }
  closedir(dir);

  /* submit any work */
  io_uring_submit(&ring);

  /* event loop */
  struct io_uring_cqe *cqe;
  while (1) {
    int error;

  wait:
    error = io_uring_wait_cqe(&ring, &cqe);
    if (error) {
      if (errno == EAGAIN)
        goto wait;
      fatal("io_uring\n");
      error_code = GAMEPAD_ERROR_IO_URING_WAIT;
      break;
    }

    struct op *op = io_uring_cqe_get_data(cqe);
    if (op == 0)
      goto cqe_seen;

    /* on inotify events */
    if (op->type & OP_INOTIFY_WATCH) {
      /* on error, finish the program */
      if (cqe->res < 0) {
        fatal("inotify watch\n");
        error_code = GAMEPAD_ERROR_INOTIFY_WATCH;
        break;
      }

      int revents = cqe->res;
      if (!(revents & POLLIN)) {
        fatal("inotify\n");
        error_code = GAMEPAD_ERROR_INOTIFY_WATCH_POLL;
        break;
      }

      /*
       * get the number of bytes available to read from an
       * inotify file descriptor.
       * see: inotify(7)
       */
      u32 bufsz;
      ioctl(op->fd, FIONREAD, &bufsz);

      u8 buf[bufsz];
      ssize_t readBytes = read(op->fd, buf, sizeof(buf));
      if (readBytes < 0) {
        goto cqe_seen;
      }

      struct inotify_event *event = (struct inotify_event *)buf;
      if (event->len <= 0)
        goto cqe_seen;

      if (event->mask & IN_ISDIR)
        goto cqe_seen;

      /* get full path */
      char path[32] = "/dev/input/";
      for (char *dest = path + 11, *src = event->name; *src; src++, dest++) {
        *dest = *src;
      }

      printf("--> %d %s %s\n", event->mask, event->name, path);

      if (event->mask & IN_DELETE)
        goto cqe_seen;

      struct op_device_open *op = &(struct op_device_open){
          .type = OP_DEVICE_OPEN,
          .path = path,
      };

      /* wait for device initialization */
      sqe = io_uring_get_sqe(&ring);
      struct __kernel_timespec *ts = &(struct __kernel_timespec){
          .tv_nsec = 75000000, /* 750ms */
      };
      io_uring_prep_timeout(sqe, ts, 1, 0);
      io_uring_sqe_set_data(sqe, op);
      io_uring_submit(&ring);
    }

    else if (op->type & OP_DEVICE_OPEN) {
      if (cqe->res < 0 && cqe->res != -ETIME) {
        warning("waiting for device initialiation failed\n");
        goto cqe_seen;
      }
      struct op_device_open *currentOp = (struct op_device_open *)op;

      struct op_joystick_read *op = &(struct op_joystick_read){
          .type = OP_JOYSTICK_READ,
      };

      op->fd = open(currentOp->path, O_RDONLY | O_NONBLOCK);
      if (op->fd < 0) {
        warning("opening device failed\n");
        goto cqe_seen;
      }

      struct libevdev *evdev;
      int rc = libevdev_new_from_fd(op->fd, &evdev);
      if (rc < 0) {
        warning("libevdev failed\n");
        goto error;
      }

      /* detect joystick */
      if (!libevdev_is_joystick(evdev)) {
        warning("This device does not look like a joystick\n");
        goto error;
      }

      printf("Input device name: \"%s\"\n", libevdev_get_name(evdev));
      printf("Input device ID: bus %#x vendor %#x product %#x\n",
             libevdev_get_id_bustype(evdev), libevdev_get_id_vendor(evdev),
             libevdev_get_id_product(evdev));

      sqe = io_uring_get_sqe(&ring);
      io_uring_prep_read(sqe, op->fd, &op->event, sizeof(op->event), 0);
      io_uring_sqe_set_data(sqe, op);
      io_uring_submit(&ring);

      libevdev_free(evdev);
      goto cqe_seen;

    error:
      if (evdev)
        libevdev_free(evdev);
      sqe = io_uring_get_sqe(&ring);
      io_uring_prep_close(sqe, op->fd);
      io_uring_sqe_set_data(sqe, 0);
      io_uring_submit(&ring);
    }

    else if (op->type & OP_JOYSTICK_READ) {
      struct op_joystick_read *op = io_uring_cqe_get_data(cqe);
      struct input_event *event = &op->event;

      /* on joystick read error (eg. joystick removed), close the fd */
      if (cqe->res < 0) {
        warning("cannot read events from device. maybe disconnected?\n");
        sqe = io_uring_get_sqe(&ring);
        io_uring_prep_close(sqe, op->fd);
        io_uring_sqe_set_data(sqe, 0);
        io_uring_submit(&ring);
        goto cqe_seen;
      }

      printf("fd: %d time: %ld.%ld type: %d code: %d value: %d\n", op->fd,
             event->input_event_sec, event->input_event_usec, event->type,
             event->code, event->value);

      /* read event again from gamepad device */
      sqe = io_uring_get_sqe(&ring);
      io_uring_prep_read(sqe, op->fd, &op->event, sizeof(op->event), 0);
      io_uring_sqe_set_data(sqe, op);
      io_uring_submit(&ring);
    }

  cqe_seen:
    io_uring_cqe_seen(&ring, cqe);
  }

inotify_watch_exit:
  close(fd_watch);

inotify_exit:
  close(fd_inotify);

io_uring_exit:
  io_uring_queue_exit(&ring);

exit:
  return error_code;
}
