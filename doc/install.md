# Installing cjdb-ranges

## Pre-requisites

This project currently only supports [clang-concepts-monorepo][1], with a GCC 10-compatible
libstdc++ or a tip-of-trunk libc++. You will also require recent versions of Conan and CMake for
effective usage.

### What about MSVC 2019 and GCC?

It is currently unclear whether the compile-time failures in MSVC are due to errors in the library
or missing parts of their concepts implementation: as soon as MSVC is concepts feature-complete,
this library will immediately adopt support for MSVC 2019.

Although GCC has had support for the Concepts TS since GCC 6, no attempt is being made to support
GCC 6–9, as the Concepts TS has been superseded and incompatible with C++20 concepts. GCC 10 support
is currently stalled by [GCC Bug 92040][2], which prevents some valid tests from passing. Support
for GCC 10 will resume once Bug 92040 has been closed.

## Installing with Conan

Installing `cjdb-ranges` is fairly straightforward.

```
conan remote add https://api.bintray.com/conan/cjdb/cjdb
conan install cjdb-ranges/head@cjdb/development --profile=<your-profile>
```

## CMake integration

### Finding the package

To direct CMake to cjdb-ranges, you'll need to add this to the list of CMake dependencies that you
import.

```cmake
find_package(cjdb-ranges REQUIRED)
```

### Building with cjdb-ranges

To use with CMake, add this for each target that includes a header from `cjdb-ranges`.

```cmake
target_link_libraries(target.name PRIVATE cjdb::ranges)
```

Notice that we change from a hyphen in `find_package` to a namespace scope operator in
`target_link_libraries`.

[1]: https://github.com/saarraz/clang-concepts-monorepo
[2]: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=92040
