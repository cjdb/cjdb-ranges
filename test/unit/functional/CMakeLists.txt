# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
add_cjdblib_test(FILENAME invoke.cpp INCLUDE "${CMAKE_SOURCE_DIR}/test/include")
add_subdirectory(rangecmp)
