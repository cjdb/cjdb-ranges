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
#include "cjdb/concepts/comparison/boolean.hpp"

#include "boolean.hpp"
#include <memory>
#include <vector>

using cjdb::boolean;

int main()
{
   static_assert(boolean<bool>);
   static_assert(boolean<int>);
   static_assert(boolean<cjdb_test::boolean>);
   static_assert(boolean<cjdb_test::explicitly_constructible_boolean>);

   static_assert(not boolean<std::vector<int>>);
   static_assert(not boolean<int*>);
   static_assert(not boolean<std::unique_ptr<int>>);
   static_assert(not boolean<cjdb_test::explicitly_convertible_boolean>);
   static_assert(not boolean<cjdb_test::bad_not_boolean>);
   static_assert(not boolean<cjdb_test::bad_and_boolean1>);
   static_assert(not boolean<cjdb_test::bad_and_boolean2>);
   static_assert(not boolean<cjdb_test::bad_and_boolean3>);
   static_assert(not boolean<cjdb_test::bad_or_boolean1>);
   static_assert(not boolean<cjdb_test::bad_or_boolean2>);
   static_assert(not boolean<cjdb_test::bad_or_boolean3>);
   static_assert(not boolean<cjdb_test::bad_equality_boolean>);
}
