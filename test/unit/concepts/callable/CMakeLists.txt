# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
add_cjdblib_test(FILENAME invocable.cpp)
add_cjdblib_test(FILENAME regularinvocable.cpp)
add_cjdblib_test(FILENAME predicate.cpp)
target_compile_options(test.unit.concepts.callable.predicate PRIVATE
                       $<$<CXX_COMPILER_ID:GNU>:
                        -Wno-float-conversion
                       >)

add_cjdblib_test(FILENAME relation.cpp)
