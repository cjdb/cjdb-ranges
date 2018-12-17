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
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "cjdb/functional/rangecmp/greater.hpp"

#include "cjdb/concepts/comparison/stricttotallyordered.hpp"
#include "cjdb/test/functional/rangecmp/is_strict_total_order.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include <doctest.h>
#include <string_view>


TEST_CASE("Test [rangecmp.greater]") {
   using cjdb::ranges::greater;
   using namespace std::string_view_literals;

   REQUIRE(greater::is_transparent{});

   constexpr auto hello = "hello"sv;
   constexpr auto konnichiwa = "konnichiwa"sv; // it's infuriating that "こんにちは" <= "hello" at
                                               // compile-time.

   SUBCASE("shows greater is a strict total order") {
      CHECK_IS_STRICT_TOTAL_ORDER(greater{}, 2, 1, 0);
      CHECK_IS_STRICT_TOTAL_ORDER(greater{}, 2, 1.0, 0);
      CHECK_IS_STRICT_TOTAL_ORDER(greater{}, 2, 1.5, 1);

      CHECK_IS_STRICT_TOTAL_ORDER(greater{}, "c"sv, "ab"sv, "a"sv);
      CHECK_IS_STRICT_TOTAL_ORDER(greater{}, "c"sv, "ab"sv, "a"sv);
   }

   SUBCASE("shows greater works for same-type ordering") {
      CJDB_CONSTEXPR_CHECK(greater{}(4, 3));
      CJDB_CONSTEXPR_CHECK(not greater{}(3, 40));

      CJDB_CONSTEXPR_CHECK(greater{}(konnichiwa, hello));
      CJDB_CONSTEXPR_CHECK(not greater{}(hello, konnichiwa));
   }

   SUBCASE("shows greater works for cross-type ordering") {
      CJDB_CONSTEXPR_CHECK(greater{}(4, 3.0));
      CJDB_CONSTEXPR_CHECK(not greater{}(3, 3.9999)); // int promoted to double

      CJDB_CONSTEXPR_CHECK(greater{}(konnichiwa.data(), hello));
      CJDB_CONSTEXPR_CHECK(not greater{}(hello, konnichiwa.data()));
   }
}
