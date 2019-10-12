# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
add_cjdblib_test(FILENAME bad_left_plus.cpp)
add_cjdblib_test(FILENAME missing_left_plus.cpp)

add_cjdblib_test(FILENAME bad_minus_distance.cpp)
add_cjdblib_test(FILENAME missing_minus_distance.cpp)

add_cjdblib_test(FILENAME bad_minus.cpp)
add_cjdblib_test(FILENAME missing_minus.cpp)

add_cjdblib_test(FILENAME bad_right_plus.cpp)
add_cjdblib_test(FILENAME missing_right_plus.cpp)

add_cjdblib_test(FILENAME bad_subscript.cpp)
add_cjdblib_test(FILENAME missing_subscript.cpp)

add_cjdblib_test(FILENAME bad_less.cpp)
add_cjdblib_test(FILENAME missing_less.cpp)

add_cjdblib_test(FILENAME bad_minus_eq.cpp)
add_cjdblib_test(FILENAME missing_minus_eq.cpp)

add_cjdblib_test(FILENAME bad_plus_eq.cpp)
add_cjdblib_test(FILENAME missing_plus_eq.cpp)

add_cjdblib_test(FILENAME dictated_iterator_category.cpp)
add_cjdblib_test(FILENAME dictated_iterator_concept.cpp)

add_cjdblib_test(FILENAME disabled_sized_sentinel.cpp)
