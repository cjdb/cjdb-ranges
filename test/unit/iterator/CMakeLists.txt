# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
add_cjdblib_test(FILENAME incrementable_traits.cpp)
add_cjdblib_test(FILENAME readable_traits.cpp)
add_cjdblib_test(FILENAME legacy_iterator.cpp)
add_cjdblib_test(FILENAME iterator_traits.cpp INCLUDE "${CMAKE_SOURCE_DIR}/test/include")
