# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
add_cjdblib_test(FILENAME readable.cpp)
add_cjdblib_test(FILENAME writable.cpp)
add_cjdblib_test(FILENAME incrementable.cpp)

add_cjdblib_test(FILENAME input_iterator.cpp)
add_cjdblib_test(FILENAME forward_iterator.cpp)
add_cjdblib_test(FILENAME bidirectional_iterator.cpp)
add_cjdblib_test(FILENAME random_access_iterator.cpp)
add_cjdblib_test(FILENAME contiguous_iterator1.cpp)
add_cjdblib_test(FILENAME contiguous_iterator2.cpp)

add_cjdblib_test(FILENAME sentinel.cpp)

add_subdirectory(non-iterators)
