# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
add_cjdblib_test(FILENAME incrementable_traits.cpp)
add_cjdblib_test(FILENAME indirectly_readable_traits.cpp)
target_compile_options(test.unit.iterator.indirectly_readable_traits PRIVATE -Wno-unused-local-typedefs)

add_cjdblib_test(FILENAME existence.cpp)
add_cjdblib_test(FILENAME legacy_iterator.cpp)
add_cjdblib_test(FILENAME iterator_traits.cpp INCLUDE "${CMAKE_SOURCE_DIR}/test/include")
add_cjdblib_test(FILENAME iter_move.cpp INCLUDE "${CMAKE_SOURCE_DIR}/test/include")
add_cjdblib_test(FILENAME iter_traits.cpp)

add_subdirectory(concepts)
