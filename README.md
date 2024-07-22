# Science C++ Utils

## Usage

To use this library in your project, vcpkg is recommended.

Add this package (`science-scipp`) to your project's dependencies in `vcpkg.json`

Then, in your `CMakeLists.txt`:

```cmake
find_package(science-scipp REQUIRED CONFIG)

target_link_libraries(
  <target>
  PRIVATE
  science::scipp
)
```

## Contents

```
- Classes
  - Status
  - Threaded
- Utils
  - uuid()
```

## Development

To build:

```sh
# set up microsoft/vcpkg in a directory of your choice

export VCPKG_ROOT=/path/to/vcpkg

make all

# or
make clean
make configure
make build
```
