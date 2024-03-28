# gamepad

This is simple example for detecting gamepad inputs using `liburing` and `libevdev` libraries in linux.

For more concrete example see [src/handmadehero_linux.c](https://github.com/e2dk4r/handmadehero/blob/0033e92f90ae6297ce1a281694cd39302f47c206/src/handmadehero_linux.c#L303)

# libraries

| library  | used for                            |
|----------|-------------------------------------|
| liburing | event loop and polling              |
| libevdev | detecting whether device is gamepad |

# build

```
meson setup build
ninja -C build
./build/gamepad
```

# references

- see chapter "5. Event interface" in https://www.kernel.org/doc/Documentation/input/input.txt
- see https://www.kernel.org/doc/Documentation/input/gamepad.txt
- see the key codes included in `/usr/include/linux/input-event-codes.h`
- see https://unixism.net/loti/tutorial/index.html for liburing examples
- if you have libinput on your system, see `man libinput-record(1)` for debugging input events
