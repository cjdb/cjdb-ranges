# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
cmake_minimum_required(VERSION 3.13)
project(PackageTest CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(example example.cpp)
target_link_libraries(example ${CONAN_LIBS})

enable_testing()
include(CTest)
add_test(test.example example)
