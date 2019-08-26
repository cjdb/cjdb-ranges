#
#  Copyright Christopher Di Bella
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
add_cjdblib_test(FILENAME equal_to.cpp
   PRIVATE_INCLUDE
      "${CMAKE_SOURCE_DIR}/test/include"
   PRIVATE_LINKAGE
      doctest::doctest)
add_cjdblib_test(FILENAME not_equal_to.cpp
   PRIVATE_INCLUDE
      "${CMAKE_SOURCE_DIR}/test/include"
   PRIVATE_LINKAGE
      doctest::doctest)

add_cjdblib_test(FILENAME less.cpp
   PRIVATE_INCLUDE
      "${CMAKE_SOURCE_DIR}/test/include"
   PRIVATE_LINKAGE
      doctest::doctest
   PRIVATE_COMPILER_OPTIONS
      -Wno-double-promotion
      -Wno-conversion)

add_cjdblib_test(FILENAME greater.cpp
   PRIVATE_INCLUDE
      "${CMAKE_SOURCE_DIR}/test/include"
   PRIVATE_LINKAGE
      doctest::doctest
   PRIVATE_COMPILER_OPTIONS
      -Wno-double-promotion
      -Wno-conversion)

add_cjdblib_test(FILENAME less_equal.cpp
   PRIVATE_INCLUDE
      "${CMAKE_SOURCE_DIR}/test/include"
   PRIVATE_LINKAGE
      doctest::doctest
   PRIVATE_COMPILER_OPTIONS
      -Wno-double-promotion
      -Wno-conversion)

add_cjdblib_test(FILENAME greater_equal.cpp
   PRIVATE_INCLUDE
      "${CMAKE_SOURCE_DIR}/test/include"
   PRIVATE_LINKAGE
      doctest::doctest
   PRIVATE_COMPILER_OPTIONS
      -Wno-double-promotion
      -Wno-conversion)

add_cjdblib_test(FILENAME partial_equal_to.cpp PRIVATE_LINKAGE doctest::doctest)
# add_cjdblib_test(FILENAME partial_not_equal_to.cpp PRIVATE_LINKAGE doctest::doctest)
add_cjdblib_test(FILENAME partial_less.cpp PRIVATE_LINKAGE doctest::doctest)
# add_cjdblib_test(FILENAME partial_greater.cpp PRIVATE_LINKAGE doctest::doctest)
# add_cjdblib_test(FILENAME partial_less_equal.cpp PRIVATE_LINKAGE doctest::doctest)
# add_cjdblib_test(FILENAME partial_greater_equal.cpp PRIVATE_LINKAGE doctest::doctest)
