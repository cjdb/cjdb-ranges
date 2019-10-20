# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
add_cjdblib_test(FILENAME invoke.cpp INCLUDE "${CMAKE_SOURCE_DIR}/test/include")
add_cjdblib_test(FILENAME identity.cpp
                 INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
                 LINK contracts_consolation)
add_subdirectory(rangecmp)
