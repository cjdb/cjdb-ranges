# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
add_cjdblib_test(FILENAME same.cpp)
add_cjdblib_test(FILENAME derivedfrom.cpp)
add_cjdblib_test(FILENAME convertibleto.cpp)
add_cjdblib_test(FILENAME commonreference.cpp)
add_cjdblib_test(FILENAME common.cpp)
add_cjdblib_test(FILENAME integral.cpp INCLUDE "${CMAKE_SOURCE_DIR}/test/include")
add_cjdblib_test(FILENAME signed_integral.cpp INCLUDE "${CMAKE_SOURCE_DIR}/test/include")
add_cjdblib_test(FILENAME unsigned_integral.cpp INCLUDE "${CMAKE_SOURCE_DIR}/test/include")
add_cjdblib_test(FILENAME floating_point.cpp INCLUDE "${CMAKE_SOURCE_DIR}/test/include")
add_cjdblib_test(FILENAME assignable.cpp)
add_cjdblib_test(FILENAME swappable.cpp INCLUDE "${CMAKE_SOURCE_DIR}/test/include")
add_cjdblib_test(FILENAME destructible.cpp)
add_cjdblib_test(FILENAME constructible.cpp)
add_cjdblib_test(FILENAME defaultconstructible.cpp)
add_cjdblib_test(FILENAME moveconstructible.cpp)
add_cjdblib_test(FILENAME copyconstructible.cpp)
