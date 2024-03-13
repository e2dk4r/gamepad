project(
  'gamepad',
  'c',
  default_options: 'c_std=c99'
)

add_project_arguments([
  '-march=x86-64-v3',
  '-funroll-loops',
  '-fomit-frame-pointer',
  ],
  language: 'c'
)

libevdev = dependency('libevdev')
liburing = dependency('liburing')

sources = files([
  'src/main.c'
])

executable(
  'gamepad',
  sources: sources,
  dependencies: [
    libevdev,
    liburing,
  ],
)
