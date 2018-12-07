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
#include "cjdb/detail/concepts/comparison/equalitycomparable.hpp"

#include "equalitycomparable.hpp"
#include "vector.hpp"

constexpr void check_EqualityComparable() noexcept
{
   using cjdb::EqualityComparable;

   static_assert(EqualityComparable<int>);
   static_assert(EqualityComparable<double>);
   static_assert(EqualityComparable<std::vector<int>>);

   static_assert(EqualityComparable<cjdb_test::equality_comparable1>);
   static_assert(EqualityComparable<cjdb_test::equality_comparable2>);
   static_assert(EqualityComparable<cjdb_test::equality_comparable3>);
   static_assert(EqualityComparable<cjdb_test::equality_comparable4>);

   static_assert(not EqualityComparable<void>);
   static_assert(not EqualityComparable<cjdb_test::not_equality_comparable1>);
   static_assert(not EqualityComparable<cjdb_test::not_equality_comparable2>);
   static_assert(not EqualityComparable<cjdb_test::not_equality_comparable3>);
}

constexpr void check_EqualityComparableWith() noexcept
{
   using cjdb::EqualityComparableWith;

   static_assert(EqualityComparableWith<int, int&>);
   static_assert(EqualityComparableWith<int, long>);
   static_assert(EqualityComparableWith<int, long&>);
   static_assert(EqualityComparableWith<int, double>);
   static_assert(EqualityComparableWith<cjdb_test::equality_comparable1, int>);
   static_assert(EqualityComparableWith<cjdb_test::equality_comparable1&, cjdb_test::equality_comparable3>);
   static_assert(EqualityComparableWith<cjdb_test::equality_comparable1, cjdb_test::equality_comparable4>);

   static_assert(not EqualityComparableWith<void, int>);
   static_assert(not EqualityComparableWith<std::vector<int>, int>);
   static_assert(not EqualityComparableWith<std::vector<int>, std::vector<int>::size_type>);
   static_assert(not EqualityComparableWith<cjdb_test::equality_comparable1, long>);
   static_assert(not EqualityComparableWith<cjdb_test::equality_comparable1, cjdb_test::equality_comparable2>);
   static_assert(not EqualityComparableWith<cjdb_test::equality_comparable2, cjdb_test::equality_comparable3>);
}

int main()
{
   check_EqualityComparable();
   check_EqualityComparableWith();
}
