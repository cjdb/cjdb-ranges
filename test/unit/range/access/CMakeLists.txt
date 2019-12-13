# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
add_cjdblib_test(FILENAME access.cpp
                 TARGET begin
                 INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
                 COMPILER_DEFINITIONS CPO=begin BASE_CPO=begin IS_CONST=false BEGIN
                 LINK cjdb::constexpr-contracts)
add_cjdblib_test(FILENAME access.cpp
                 TARGET cbegin
                 INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
                 COMPILER_DEFINITIONS CPO=cbegin BASE_CPO=begin IS_CONST=true CBEGIN
                 LINK cjdb::constexpr-contracts)
add_cjdblib_test(FILENAME access.cpp
                 TARGET end
                 INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
                 COMPILER_DEFINITIONS CPO=end BASE_CPO=end IS_CONST=false END
                 LINK cjdb::constexpr-contracts)
add_cjdblib_test(FILENAME access.cpp
                 TARGET cend
                 INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
                 COMPILER_DEFINITIONS CPO=cend BASE_CPO=end IS_CONST=true CEND
                 LINK cjdb::constexpr-contracts)
