#
#  Copyright 2018 Christopher Di Bella
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
include(basic_project-add-targets-impl)

# Tests for checks that are disabled
add_basic_project_test_impl(
   FILENAME -cert-dcl21-cpp.cpp)

add_basic_project_test_impl(
   FILENAME -cert-dcl59-cpp.cpp)

add_basic_project_test_impl(
   FILENAME -google-build-namespaces.cpp)

add_basic_project_test_impl(
   FILENAME -google-build-using-namespace.cpp)

add_basic_project_test_impl(
   FILENAME -google-runtime-int.cpp)

add_basic_project_test_impl(
   FILENAME -google-runtime-references.cpp)

add_basic_project_test_impl(
   FILENAME -readability-named-parameter.cpp)

add_basic_project_test_impl(
   FILENAME -readability-uppercase-literal-suffix.cpp)
