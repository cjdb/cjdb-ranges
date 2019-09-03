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
#include "cjdb/concepts/comparison/totally_ordered.hpp"

#include "equality_comparable.hpp"
#include "totally_ordered.hpp"
#include "vector.hpp"

constexpr void check_totally_ordered() noexcept
{
   using cjdb::totally_ordered;

   static_assert(totally_ordered<int>);
   static_assert(totally_ordered<double>);
   static_assert(totally_ordered<std::vector<double>>);
   static_assert(totally_ordered<cjdb_test::totally_ordered1>);
   static_assert(totally_ordered<cjdb_test::totally_ordered2>);

   static_assert(not totally_ordered<void>);
   static_assert(not totally_ordered<cjdb_test::not_totally_ordered_no_lt>);
   static_assert(not totally_ordered<cjdb_test::not_totally_ordered_no_gt>);
   static_assert(not totally_ordered<cjdb_test::not_totally_ordered_no_le>);
   static_assert(not totally_ordered<cjdb_test::not_totally_ordered_no_ge>);
   static_assert(not totally_ordered<cjdb_test::not_totally_ordered_no_eq>);
   static_assert(not totally_ordered<cjdb_test::not_totally_ordered_no_ne>);
   static_assert(not totally_ordered<cjdb_test::not_totally_ordered_wrong_return>);
}

constexpr void check_totally_ordered_with() noexcept
{
   using cjdb::totally_ordered_with;

   static_assert(totally_ordered_with<int, long>);
   static_assert(totally_ordered_with<int, double>);
   static_assert(totally_ordered_with<cjdb_test::totally_ordered1, int>);
   static_assert(totally_ordered_with<cjdb_test::totally_ordered1, cjdb_test::totally_ordered2>);

   static_assert(not totally_ordered_with<int, void>);
   static_assert(not totally_ordered_with<std::vector<int>, int>);
   static_assert(not totally_ordered_with<std::vector<int>, std::vector<int>::size_type>);
   static_assert(not totally_ordered_with<cjdb_test::totally_ordered1, long>);
   static_assert(not totally_ordered_with<cjdb_test::totally_ordered1, cjdb_test::totally_ordered3>);
   static_assert(not totally_ordered_with<cjdb_test::totally_ordered2, cjdb_test::totally_ordered3>);
}

int main()
{
   check_totally_ordered();
   check_totally_ordered_with();
}
