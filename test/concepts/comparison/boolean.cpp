//
//  Copyright Christopher Di Bella
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "cjdb/detail/concepts/comparison/boolean.hpp"

#include "boolean.hpp"
#include <memory>
#include <vector>

template<cjdb::Boolean>
constexpr void models_Boolean() noexcept {}

template<class B>
requires (not cjdb::Boolean<B>)
constexpr void not_Boolean() noexcept {}

int main()
{
   models_Boolean<bool>();
   models_Boolean<int>();
   models_Boolean<cjdb_test::boolean>();
   models_Boolean<cjdb_test::explicitly_constructible_boolean>();

   not_Boolean<std::vector<int>>();
   not_Boolean<int*>();
   not_Boolean<std::unique_ptr<int>>();
   not_Boolean<cjdb_test::explicitly_convertible_boolean>();
   not_Boolean<cjdb_test::bad_not_boolean>();
   not_Boolean<cjdb_test::bad_and_boolean1>();
   not_Boolean<cjdb_test::bad_and_boolean2>();
   not_Boolean<cjdb_test::bad_and_boolean3>();
   not_Boolean<cjdb_test::bad_or_boolean1>();
   not_Boolean<cjdb_test::bad_or_boolean2>();
   not_Boolean<cjdb_test::bad_or_boolean3>();
   not_Boolean<cjdb_test::bad_equality_boolean>();
}
