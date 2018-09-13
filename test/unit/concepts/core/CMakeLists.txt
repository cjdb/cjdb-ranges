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
add_cjdblib_test(FILENAME same.cpp)
add_cjdblib_test(FILENAME derivedfrom.cpp)
add_cjdblib_test(FILENAME convertibleto.cpp)
add_cjdblib_test(FILENAME commonreference.cpp)
add_cjdblib_test(FILENAME common.cpp)
add_cjdblib_test(FILENAME integral.cpp)
add_cjdblib_test(FILENAME assignable.cpp)
add_cjdblib_test(FILENAME swappable.cpp PRIVATE_LINKAGE doctest::doctest)
add_cjdblib_test(FILENAME destructible.cpp)
add_cjdblib_test(FILENAME constructible.cpp)
add_cjdblib_test(FILENAME defaultconstructible.cpp)
add_cjdblib_test(FILENAME moveconstructible.cpp)
add_cjdblib_test(FILENAME copyconstructible.cpp)
