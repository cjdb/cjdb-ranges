# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
add_cjdblib_test(FILENAME array.cpp
					  INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
					  LINK cjdb::constexpr-contracts)
add_cjdblib_test(FILENAME member.cpp
					  INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
					  LINK cjdb::constexpr-contracts)
add_cjdblib_test(FILENAME unqualified.cpp
					  INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
					  LINK cjdb::constexpr-contracts)
add_cjdblib_test(FILENAME faulty.cpp
					  INCLUDE "${CMAKE_SOURCE_DIR}/test/include"
					  LINK cjdb::constexpr-contracts)
