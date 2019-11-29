# Installing cjdb-ranges

## Pre-requisites

This project supports the following compilers:

* [clang-concepts-monorepo][1] (Git hash 327743ab29bb0e458cfc4a0eab3bea946b72c938)
* GCC trunk (Git hash 1dae669e3c506d8c3b8768cefe5ce7fbe385b45c)

Due to bugs at the tip-of-trunk, you'll need to checkout the corresponding Git hashes that are listed.
The project also supports libc++ (for Clang) and libstdc++ (for GCC only). You will also require
recent versions of Conan and CMake for effective usage.

### What about MSVC 2019?

Part of the test framework for this library depends upon `std::is_constant_evaluated`, which currently
is not supported by MSVC.

### Why doesn't Clang support libstdc++?

Clang currently generates an internal compiler error (ICE) when compiling with libstdc++.

### Will vcpkg be supported?

Yes, in time. Developer bandwidth is limited, and due to a lack of experience with both CMake
toolchains and vcpkg workflow. You can track the [issue on GitHub][2].

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
[2]: https://github.com/cjdb/cjdb-ranges/issues/20
