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
#include "cjdb/detail/concepts/comparison/stricttotallyordered.hpp"

#include "equalitycomparable.hpp"
#include "strict_totally_ordered.hpp"
#include "vector.hpp"

template<cjdb::StrictTotallyOrdered>
constexpr void models_StrictTotallyOrdered() noexcept {}

template<class T>
requires (not cjdb::StrictTotallyOrdered<T>)
constexpr void not_StrictTotallyOrdered() noexcept {}

constexpr void check_StrictTotallyOrdered() noexcept
{
   models_StrictTotallyOrdered<int>();
   models_StrictTotallyOrdered<double>();
   models_StrictTotallyOrdered<std::vector<double>>();
   models_StrictTotallyOrdered<cjdb_test::strict_totally_ordered1>();
   models_StrictTotallyOrdered<cjdb_test::strict_totally_ordered2>();

   not_StrictTotallyOrdered<void>();
   not_StrictTotallyOrdered<cjdb_test::not_strict_totally_ordered_no_lt>();
   not_StrictTotallyOrdered<cjdb_test::not_strict_totally_ordered_no_gt>();
   not_StrictTotallyOrdered<cjdb_test::not_strict_totally_ordered_no_le>();
   not_StrictTotallyOrdered<cjdb_test::not_strict_totally_ordered_no_ge>();
   not_StrictTotallyOrdered<cjdb_test::not_strict_totally_ordered_no_eq>();
   not_StrictTotallyOrdered<cjdb_test::not_strict_totally_ordered_no_ne>();
   not_StrictTotallyOrdered<cjdb_test::not_strict_totally_ordered_wrong_return>();
}

template<class T1, cjdb::StrictTotallyOrderedWith<T1> T2>
constexpr void models_StrictTotallyOrderedWith() noexcept {}

template<class T1, class T2>
requires (not cjdb::StrictTotallyOrderedWith<T1, T2>)
constexpr void not_StrictTotallyOrderedWith() noexcept {}

constexpr void check_StrictTotallyOrderedWith() noexcept
{
   models_StrictTotallyOrderedWith<int, long>();
   models_StrictTotallyOrderedWith<int, double>();
   models_StrictTotallyOrderedWith<cjdb_test::strict_totally_ordered1, int>();
   models_StrictTotallyOrderedWith<cjdb_test::strict_totally_ordered1, cjdb_test::strict_totally_ordered2>();

   not_StrictTotallyOrderedWith<int, void>();
   not_StrictTotallyOrderedWith<std::vector<int>, int>();
   not_StrictTotallyOrderedWith<std::vector<int>, std::vector<int>::size_type>();
   not_StrictTotallyOrderedWith<cjdb_test::strict_totally_ordered1, long>();
   not_StrictTotallyOrderedWith<cjdb_test::strict_totally_ordered1, cjdb_test::strict_totally_ordered3>();
   not_StrictTotallyOrderedWith<cjdb_test::strict_totally_ordered2, cjdb_test::strict_totally_ordered3>();
}

int main()
{
   check_StrictTotallyOrdered();
   check_StrictTotallyOrderedWith();
}
