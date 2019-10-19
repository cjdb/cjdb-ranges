# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
add_cjdblib_test(FILENAME lvalue_lvalue.cpp
                 INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
                 LINK contracts_consolation)
add_cjdblib_test(FILENAME rvalue_lvalue.cpp
                 INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
                 LINK contracts_consolation)

add_cjdblib_test(FILENAME lvalue_rvalue.cpp
                 INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
                 LINK contracts_consolation)
add_cjdblib_test(FILENAME rvalue_rvalue.cpp
                 INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
                 LINK contracts_consolation)
add_cjdblib_test(FILENAME has_swap.cpp
                 INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
                 LINK contracts_consolation)
