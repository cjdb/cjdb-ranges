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
#include "cjdb/functional/rangecmp/less.hpp"

#include "cjdb/concepts/comparison/totally_ordered.hpp"
#include "cjdb/test/functional/rangecmp/is_strict_total_order.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/simple_test.hpp"
#include <string_view>


int main()
{
   using cjdb::ranges::less;
   using namespace std::string_view_literals;

   static_assert(less::is_transparent{});

   constexpr auto hello = "hello"sv;
   constexpr auto konnichiwa = "konnichiwa"sv; // it's infuriating that "こんにちは" <= "hello" at
                                               // compile-time.

   { // shows less is a strict total order
      CHECK_IS_STRICT_TOTAL_ORDER(less{}, 0, 1, 2);  // NOLINT(readability-magic-numbers)
      CHECK_IS_STRICT_TOTAL_ORDER(less{}, 0, 1.0, 2);  // NOLINT(readability-magic-numbers)
      CHECK_IS_STRICT_TOTAL_ORDER(less{}, 1, 1.5, 2);  // NOLINT(readability-magic-numbers)

      CHECK_IS_STRICT_TOTAL_ORDER(less{}, "a"sv, "ab"sv, "c"sv);  // NOLINT(readability-magic-numbers)
      CHECK_IS_STRICT_TOTAL_ORDER(less{}, "a"sv, "ab", "c"sv);  // NOLINT(readability-magic-numbers)
   }

   { // shows less works for same-type ordering
      CJDB_CONSTEXPR_CHECK(less{}(3, 4));  // NOLINT(readability-magic-numbers)
      CJDB_CONSTEXPR_CHECK(not less{}(40, 3));  // NOLINT(readability-magic-numbers)

      CJDB_CONSTEXPR_CHECK(less{}(hello, konnichiwa));
      CJDB_CONSTEXPR_CHECK(not less{}(konnichiwa, hello));
   }

   { // shows less works for cross-type ordering
      CJDB_CONSTEXPR_CHECK(less{}(3.0, 4));  // NOLINT(readability-magic-numbers)

      // int promoted to double
      CJDB_CONSTEXPR_CHECK(not less{}(3.9999, 3));  // NOLINT(readability-magic-numbers)

      CJDB_CONSTEXPR_CHECK(less{}(hello, konnichiwa.data()));
      CJDB_CONSTEXPR_CHECK(not less{}(konnichiwa.data(), hello));
   }

   return ::test_result();
}
