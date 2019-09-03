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
#include "cjdb/functional/rangecmp/greater_equal.hpp"

#include "cjdb/concepts/comparison/totally_ordered.hpp"
#include "cjdb/test/functional/rangecmp/is_partial_order.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/simple_test.hpp"
#include <string_view>


int main()
{
   using cjdb::ranges::greater_equal;
   using namespace std::string_view_literals;

   static_assert(greater_equal::is_transparent{});

   constexpr auto hello = "hello"sv;
   constexpr auto konnichiwa = "konnichiwa"sv; // it's infuriating that "こんにちは" <= "hello" at
                                               // compile-time.

   { // shows greater_equal is a partial order
      CHECK_IS_PARTIAL_ORDER(greater_equal{}, 2, 1, 0);   // NOLINT(readability-magic-numbers)
      CHECK_IS_PARTIAL_ORDER(greater_equal{}, 2, 1.0, 0); // NOLINT(readability-magic-numbers)
      CHECK_IS_PARTIAL_ORDER(greater_equal{}, 2, 1.5, 1); // NOLINT(readability-magic-numbers)

      CHECK_IS_PARTIAL_ORDER(greater_equal{}, "c"sv, "ab"sv, "a"sv);
      CHECK_IS_PARTIAL_ORDER(greater_equal{}, "c"sv, "ab"sv, "a"sv);
   }

   { // shows greater_equal works for same-type ordering
      CJDB_CONSTEXPR_CHECK(greater_equal{}(30, 30));     // NOLINT(readability-magic-numbers)
      CJDB_CONSTEXPR_CHECK(greater_equal{}(4, 3));       // NOLINT(readability-magic-numbers)
      CJDB_CONSTEXPR_CHECK(not greater_equal{}(3, 40));  // NOLINT(readability-magic-numbers)

      CJDB_CONSTEXPR_CHECK(greater_equal{}(hello, hello));
      CJDB_CONSTEXPR_CHECK(greater_equal{}(konnichiwa, hello));
      CJDB_CONSTEXPR_CHECK(not greater_equal{}(hello, konnichiwa));
   }

   { // shows greater_equal works for cross-type ordering
      CJDB_CONSTEXPR_CHECK(greater_equal{}(3.0, 3)); // NOLINT(readability-magic-numbers)
      CJDB_CONSTEXPR_CHECK(greater_equal{}(4, 3.0)); // NOLINT(readability-magic-numbers)

      // int promoted to double
      CJDB_CONSTEXPR_CHECK(not greater_equal{}(3, 3.9999)); // NOLINT(readability-magic-numbers)

      CJDB_CONSTEXPR_CHECK(greater_equal{}(hello, hello.data()));
      CJDB_CONSTEXPR_CHECK(greater_equal{}(konnichiwa.data(), hello));
      CJDB_CONSTEXPR_CHECK(not greater_equal{}(hello, konnichiwa.data()));
   }

   return ::test_result();
}
