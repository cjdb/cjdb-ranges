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
#include "cjdb/functional/rangecmp/equal_to.hpp"

#include "cjdb/concepts/comparison/equalitycomparable.hpp"
#include "cjdb/test/functional/rangecmp/is_equivalence.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include <doctest.h>
#include <string_view>

TEST_CASE("Test [rangecmp.equal_to]") {
   using cjdb::ranges::equal_to;
   using namespace std::string_view_literals;

   REQUIRE(equal_to::is_transparent{});

   constexpr auto hello = "hello"sv;
   constexpr auto goodbye = "goodbye"sv;

   SUBCASE("shows equal_to is an equivalence relation") {
      CHECK_IS_EQUIVALENCE(equal_to{}, 0, 0, 0);
      CHECK_IS_EQUIVALENCE(equal_to{}, 0, 0.0, 0);
      CHECK_IS_EQUIVALENCE(equal_to{}, 0.0, 0, 0.0);

      CHECK_IS_EQUIVALENCE(equal_to{}, hello, hello, hello);
   }

   SUBCASE("shows equal_to works for same-type equality") {
      CJDB_CONSTEXPR_CHECK(equal_to{}(0, 0));
      CJDB_CONSTEXPR_CHECK(not equal_to{}(0, 1));

      CJDB_CONSTEXPR_CHECK(equal_to{}(hello, hello));
      CJDB_CONSTEXPR_CHECK(not equal_to{}(hello, goodbye));
   }

   SUBCASE("shows equal_to works for cross-type equality") {
      CJDB_CONSTEXPR_CHECK(equal_to{}(1, 1.0));
      CJDB_CONSTEXPR_CHECK(not equal_to{}(1, 1.5)); // int is promoted to double
      CJDB_CONSTEXPR_CHECK(not equal_to{}(1, 2.6)); // outright not equal

      CJDB_CONSTEXPR_CHECK(equal_to{}(hello, hello.data()));
      CJDB_CONSTEXPR_CHECK(not equal_to{}(hello, goodbye.data()));
   }
}
