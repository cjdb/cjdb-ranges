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
#include "cjdb/concepts/comparison/equality_comparable.hpp"

#include "equality_comparable.hpp"
#include "vector.hpp"

constexpr void check_equality_comparable() noexcept
{
   using cjdb::equality_comparable;

   static_assert(equality_comparable<int>);
   static_assert(equality_comparable<double>);
   static_assert(equality_comparable<std::vector<int>>);

   static_assert(equality_comparable<cjdb_test::equality_comparable1>);
   static_assert(equality_comparable<cjdb_test::equality_comparable2>);
   static_assert(equality_comparable<cjdb_test::equality_comparable3>);
   static_assert(equality_comparable<cjdb_test::equality_comparable4>);

   static_assert(not equality_comparable<void>);
   static_assert(not equality_comparable<cjdb_test::not_equality_comparable1>);
   static_assert(not equality_comparable<cjdb_test::not_equality_comparable2>);
   static_assert(not equality_comparable<cjdb_test::not_equality_comparable3>);
}

constexpr void check_equality_comparable_with() noexcept
{
   using cjdb::equality_comparable_with;

   static_assert(equality_comparable_with<int, int&>);
   static_assert(equality_comparable_with<int, long>);
   static_assert(equality_comparable_with<int, long&>);
   static_assert(equality_comparable_with<int, double>);
   static_assert(equality_comparable_with<cjdb_test::equality_comparable1, int>);
   static_assert(equality_comparable_with<cjdb_test::equality_comparable1&, cjdb_test::equality_comparable3>);
   static_assert(equality_comparable_with<cjdb_test::equality_comparable1, cjdb_test::equality_comparable4>);

   static_assert(not equality_comparable_with<void, int>);
   static_assert(not equality_comparable_with<std::vector<int>, int>);
   static_assert(not equality_comparable_with<std::vector<int>, std::vector<int>::size_type>);
   static_assert(not equality_comparable_with<cjdb_test::equality_comparable1, long>);
   static_assert(not equality_comparable_with<cjdb_test::equality_comparable1, cjdb_test::equality_comparable2>);
   static_assert(not equality_comparable_with<cjdb_test::equality_comparable2, cjdb_test::equality_comparable3>);
}

int main()
{
   check_equality_comparable();
   check_equality_comparable_with();
}
