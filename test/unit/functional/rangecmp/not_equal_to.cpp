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
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "cjdb/functional/rangecmp/not_equal_to.hpp"

#include "cjdb/concepts/comparison/equalitycomparable.hpp"
#include "cjdb/test/functional/rangecmp/is_irreflexive.hpp"
#include "cjdb/test/functional/rangecmp/is_symmetric.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include <doctest.h>
#include <string_view>
#include <utility>

TEST_CASE("Test [rangecmp.not_equal_to]") {
   using cjdb::ranges::not_equal_to;
   using namespace std::string_view_literals;

   REQUIRE(not_equal_to::is_transparent{});

   constexpr auto hello = "hello"sv;

   SUBCASE("Checks not_equal_to is irreflexive and symmetric") {
      CHECK_IS_IRREFLEXIVE(not_equal_to{}, 0);
      CHECK_IS_IRREFLEXIVE(not_equal_to{}, hello);
   }

   SUBCASE("Checks not_equal_to works for same-type inequality") {
      CJDB_CONSTEXPR_CHECK(not_equal_to{}(0, 1));

      CJDB_CONSTEXPR_CHECK(not not_equal_to{}(0, 0));
   }

   SUBCASE("Checks not_equal_to works for cross-type inequality") {
      CJDB_CONSTEXPR_CHECK(not_equal_to{}(1, 1.5)); // int is promoted to double
      CJDB_CONSTEXPR_CHECK(not_equal_to{}(1, 2.6)); // just outright not equal

      CJDB_CONSTEXPR_CHECK(not not_equal_to{}(1, 1.0));
   }
}
