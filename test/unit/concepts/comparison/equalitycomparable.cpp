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

template<cjdb::EqualityComparable>
constexpr void models_EqualityComparable() noexcept {}

template<class T>
requires (not cjdb::EqualityComparable<T>)
constexpr void not_EqualityComparable() noexcept {}

constexpr void check_EqualityComparable() noexcept
{
   models_EqualityComparable<int>();
   models_EqualityComparable<double>();
   models_EqualityComparable<std::vector<int>>();

   models_EqualityComparable<cjdb_test::equality_comparable1>();
   models_EqualityComparable<cjdb_test::equality_comparable2>();
   models_EqualityComparable<cjdb_test::equality_comparable3>();
   models_EqualityComparable<cjdb_test::equality_comparable4>();

   not_EqualityComparable<void>();
   not_EqualityComparable<cjdb_test::not_equality_comparable1>();
   not_EqualityComparable<cjdb_test::not_equality_comparable2>();
   not_EqualityComparable<cjdb_test::not_equality_comparable3>();
}

template<class T1, cjdb::EqualityComparableWith<T1> T2>
constexpr void models_EqualityComparableWith() noexcept {}

template<class T1, class T2>
requires (not cjdb::EqualityComparableWith<T1, T2>)
constexpr void not_EqualityComparableWith() noexcept {}

constexpr void check_EqualityComparableWith() noexcept
{
   models_EqualityComparableWith<int, int&>();
   models_EqualityComparableWith<int, long>();
   models_EqualityComparableWith<int, long&>();
   models_EqualityComparableWith<int, double>();
   models_EqualityComparableWith<cjdb_test::equality_comparable1, int>();
   models_EqualityComparableWith<cjdb_test::equality_comparable1&, cjdb_test::equality_comparable3>();
   models_EqualityComparableWith<cjdb_test::equality_comparable1, cjdb_test::equality_comparable4>();

   not_EqualityComparableWith<void, int>();
   not_EqualityComparableWith<std::vector<int>, int>();
   not_EqualityComparableWith<std::vector<int>, std::vector<int>::size_type>();
   not_EqualityComparableWith<cjdb_test::equality_comparable1, long>();
   not_EqualityComparableWith<cjdb_test::equality_comparable1, cjdb_test::equality_comparable2>();
   not_EqualityComparableWith<cjdb_test::equality_comparable2, cjdb_test::equality_comparable3>();
}

int main()
{
   check_EqualityComparable();
   check_EqualityComparableWith();
}
