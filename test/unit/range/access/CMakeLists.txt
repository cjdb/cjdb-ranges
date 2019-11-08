# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
add_cjdblib_test(FILENAME begin.cpp
                 INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
                 LINK cjdb::constexpr-contracts)
add_cjdblib_test(FILENAME cbegin.cpp
                 INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
                 LINK cjdb::constexpr-contracts)
add_cjdblib_test(FILENAME end.cpp
                 INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
                 LINK cjdb::constexpr-contracts)
add_cjdblib_test(FILENAME cend.cpp
                 INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
                 LINK cjdb::constexpr-contracts)
