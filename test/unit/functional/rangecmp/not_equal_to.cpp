//
//  Copyright 2018 Christopher Di Bella
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
#include "cjdb/functional/rangecmp/not_equal_to.hpp"

#include "cjdb/concepts/comparison/equality_comparable.hpp"
#include "cjdb/test/functional/rangecmp/is_irreflexive.hpp"
#include "cjdb/test/functional/rangecmp/is_symmetric.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/simple_test.hpp"
#include <string_view>
#include <utility>

int main()
{
   using cjdb::ranges::not_equal_to;
   using namespace std::string_view_literals;

   static_assert(not_equal_to::is_transparent{});

   constexpr auto hello = "hello"sv;

   { // Checks not_equal_to is irreflexive and symmetric
      CHECK_IS_IRREFLEXIVE(not_equal_to{}, 0);
      CHECK_IS_IRREFLEXIVE(not_equal_to{}, hello);
   }

   { // Checks not_equal_to works for same-type inequality
      CJDB_CONSTEXPR_CHECK(not_equal_to{}(0, 1));

      CJDB_CONSTEXPR_CHECK(not not_equal_to{}(0, 0));
   }

   { // Checks not_equal_to works for cross-type inequality
      // int is promoted to double
      CJDB_CONSTEXPR_CHECK(not_equal_to{}(1, 1.5)); // NOLINT(readability-magic-numbers)
      // just outright not equal
      CJDB_CONSTEXPR_CHECK(not_equal_to{}(1, 2.6)); // NOLINT(readability-magic-numbers)

      CJDB_CONSTEXPR_CHECK(not not_equal_to{}(1, 1.0));
   }

   return ::test_result();
}
