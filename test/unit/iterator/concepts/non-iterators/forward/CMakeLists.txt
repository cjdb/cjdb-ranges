# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
add_cjdblib_test(FILENAME bad_postinc.cpp)
# There is no missing_postinc, because that fails to satisfy weakly_incrementable.

add_cjdblib_test(FILENAME bad_equality.cpp)
add_cjdblib_test(FILENAME missing_equality.cpp)
