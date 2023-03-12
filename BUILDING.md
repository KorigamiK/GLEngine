# Building with CMake

## Prerequisites

The OpenGL Engine requires the following libraries and tools
to be installed on your system.

- CMake[1]
- OpenGL
- SDL2

## Build

This project doesn't require any special
command-line flags to build to keep
things simple.

Here are the steps for building in release mode with a single-configuration
generator, like the Unix Makefiles one:

```sh
cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
cmake --build build
```

Here are the steps for building in release mode with a multi-configuration
generator, like the Visual Studio ones:

```sh
cmake -S . -B build
cmake --build build --config Release
```

## Presets

This project makes use of [presets][3] to simplify the process of configuring
the project. As a developer, you are recommended to always have
the [latest CMake version][2] installed to make use of the
latest Quality-of-Life additions.

If you followed the above instructions, then you can configure, build and test
the project respectively with the following commands from the project root on
any operating system with any build system:

```sh
cmake --preset=Web
cmake --build --preset=EngineTest
ctest --preset=EngineTest
```

If you are using a compatible editor (e.g. VSCode) or IDE (e.g. CLion, VS), you
will also be able to select the above created user presets for automatic integration.

[1]: https://cmake.org/download/
[2]: https://cmake.org/cmake/help/latest/manual/cmake.1.html#install-a-project
[3]: https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html
