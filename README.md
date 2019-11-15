# Kaleidoscope-host_keymap

A untility that enables the generation of host_keymap header files for the Kaleidoscope firmware.

## Prerequisites

This project requires the following libraries (and dev-packages) to be
installed on a GNU/linux system.

* boost_filesystem
* boost_program_options
* libxkbcommon
* cmake

## Build process

Generate a build directory
```
cd <repo_root>
mkdir build
cd build
```

Configure the build system
```
cmake ..
```

Build
```
make
```

## Generate keymap files

```
cd <repo_root>/build
./host_keymap -b <base_dir>
```
`base_dir` could e.g. be `$PWD/linux` to generate the host_keymap files
in a subdirectory of the build tree.

## Install the keymap files

Manually copy the base directory, e.g. the `linux` directory to
the appropriate location in the Kaleidoscope repo.
