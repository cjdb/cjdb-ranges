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
#include "cjdb/concepts/comparison/stricttotallyordered.hpp"

#include "equalitycomparable.hpp"
#include "strict_totally_ordered.hpp"
#include "vector.hpp"

constexpr void check_StrictTotallyOrdered() noexcept
{
   using cjdb::StrictTotallyOrdered;

   static_assert(StrictTotallyOrdered<int>);
   static_assert(StrictTotallyOrdered<double>);
   static_assert(StrictTotallyOrdered<std::vector<double>>);
   static_assert(StrictTotallyOrdered<cjdb_test::strict_totally_ordered1>);
   static_assert(StrictTotallyOrdered<cjdb_test::strict_totally_ordered2>);

   static_assert(not StrictTotallyOrdered<void>);
   static_assert(not StrictTotallyOrdered<cjdb_test::not_strict_totally_ordered_no_lt>);
   static_assert(not StrictTotallyOrdered<cjdb_test::not_strict_totally_ordered_no_gt>);
   static_assert(not StrictTotallyOrdered<cjdb_test::not_strict_totally_ordered_no_le>);
   static_assert(not StrictTotallyOrdered<cjdb_test::not_strict_totally_ordered_no_ge>);
   static_assert(not StrictTotallyOrdered<cjdb_test::not_strict_totally_ordered_no_eq>);
   static_assert(not StrictTotallyOrdered<cjdb_test::not_strict_totally_ordered_no_ne>);
   static_assert(not StrictTotallyOrdered<cjdb_test::not_strict_totally_ordered_wrong_return>);
}

constexpr void check_StrictTotallyOrderedWith() noexcept
{
   using cjdb::StrictTotallyOrderedWith;

   static_assert(StrictTotallyOrderedWith<int, long>);
   static_assert(StrictTotallyOrderedWith<int, double>);
   static_assert(StrictTotallyOrderedWith<cjdb_test::strict_totally_ordered1, int>);
   static_assert(StrictTotallyOrderedWith<cjdb_test::strict_totally_ordered1, cjdb_test::strict_totally_ordered2>);

   static_assert(not StrictTotallyOrderedWith<int, void>);
   static_assert(not StrictTotallyOrderedWith<std::vector<int>, int>);
   static_assert(not StrictTotallyOrderedWith<std::vector<int>, std::vector<int>::size_type>);
   static_assert(not StrictTotallyOrderedWith<cjdb_test::strict_totally_ordered1, long>);
   static_assert(not StrictTotallyOrderedWith<cjdb_test::strict_totally_ordered1, cjdb_test::strict_totally_ordered3>);
   static_assert(not StrictTotallyOrderedWith<cjdb_test::strict_totally_ordered2, cjdb_test::strict_totally_ordered3>);
}

int main()
{
   check_StrictTotallyOrdered();
   check_StrictTotallyOrderedWith();
}
