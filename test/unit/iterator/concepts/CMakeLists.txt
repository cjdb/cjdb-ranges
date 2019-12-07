# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
add_cjdblib_test(FILENAME indirectly_readable.cpp INCLUDE "${CMAKE_SOURCE_DIR}/test/include")
add_cjdblib_test(FILENAME indirectly_writable.cpp INCLUDE "${CMAKE_SOURCE_DIR}/test/include")
add_cjdblib_test(FILENAME incrementable.cpp)

add_cjdblib_test(FILENAME input_iterator.cpp)
add_cjdblib_test(FILENAME forward_iterator.cpp)
add_cjdblib_test(FILENAME bidirectional_iterator.cpp)
add_cjdblib_test(FILENAME random_access_iterator.cpp)
add_cjdblib_test(FILENAME contiguous_iterator1.cpp)
add_cjdblib_test(FILENAME contiguous_iterator2.cpp)

add_cjdblib_test(FILENAME sentinel.cpp)

add_cjdblib_test(FILENAME indirectly_movable.cpp INCLUDE "${CMAKE_SOURCE_DIR}/test/include")
add_cjdblib_test(FILENAME indirectly_movable_storable.cpp INCLUDE "${CMAKE_SOURCE_DIR}/test/include")

add_subdirectory(non-iterators)
