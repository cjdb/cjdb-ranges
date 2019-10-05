# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
add_subdirectory(core)
add_subdirectory(comparison)
add_subdirectory(callable)
add_subdirectory(object)

add_cjdblib_test(FILENAME concepts.cpp)
