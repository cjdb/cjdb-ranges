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
build_test("${prefix}" equal_to ${enable_catch2})
# build_test("${prefix}" not_equal_to ${enable_catch2})
build_test("${prefix}" less ${enable_catch2})
# build_test("${prefix}" less_equal ${enable_catch2})
# build_test("${prefix}" greater_equal ${enable_catch2})
# build_test("${prefix}" greater ${enable_catch2})

build_test("${prefix}" partial_equal_to ${enable_catch2})
# build_test("${prefix}" partial_less ${enable_catch2})
# build_test("${prefix}" partial_less_equal ${enable_catch2})
# build_test("${prefix}" partial_greater_equal ${enable_catch2})
# build_test("${prefix}" partial_greater ${enable_catch2})
