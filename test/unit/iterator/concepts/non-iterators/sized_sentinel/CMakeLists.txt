# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
add_cjdblib_test(FILENAME bad_left_minus.cpp)
add_cjdblib_test(FILENAME missing_left_minus.cpp)

add_cjdblib_test(FILENAME bad_right_minus.cpp)
add_cjdblib_test(FILENAME missing_right_minus.cpp)

add_cjdblib_test(FILENAME disabled_sized_sentinel.cpp)
