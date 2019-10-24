# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
add_cjdblib_test(FILENAME equal_to.cpp
   INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
   LINK cjdb::constexpr-contracts)
add_cjdblib_test(FILENAME not_equal_to.cpp
   INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
   LINK cjdb::constexpr-contracts)

add_cjdblib_test(FILENAME less.cpp
   INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
   LINK cjdb::constexpr-contracts)
target_compile_options(test.unit.functional.rangecmp.less PRIVATE
                       $<$<CXX_COMPILER_ID:GNU>:
                        -Wno-conversion
                       >)

add_cjdblib_test(FILENAME greater.cpp
   INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
   LINK cjdb::constexpr-contracts)

add_cjdblib_test(FILENAME less_equal.cpp
   INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
   LINK cjdb::constexpr-contracts)

add_cjdblib_test(FILENAME greater_equal.cpp
   INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
   LINK cjdb::constexpr-contracts)

# add_cjdblib_test(FILENAME partial_equal_to.cpp INCLUDE "${CMAKE_SOURCE_DIR}/test/include")
# add_cjdblib_test(FILENAME partial_not_equal_to.cpp INCLUDE "${CMAKE_SOURCE_DIR}/test/include")
# add_cjdblib_test(FILENAME partial_less.cpp INCLUDE "${CMAKE_SOURCE_DIR}/test/include")
# add_cjdblib_test(FILENAME partial_greater.cpp INCLUDE "${CMAKE_SOURCE_DIR}/test/include")
# add_cjdblib_test(FILENAME partial_less_equal.cpp INCLUDE "${CMAKE_SOURCE_DIR}/test/include")
# add_cjdblib_test(FILENAME partial_greater_equal.cpp INCLUDE "${CMAKE_SOURCE_DIR}/test/include")
