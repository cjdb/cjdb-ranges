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

#include <catch2/catch.hpp>
#include "cjdb/concepts/comparison/stricttotallyordered.hpp"
#include <string>
#include <utility>

static_assert(cjdb::ranges::less::is_transparent{});

template<class T1, cjdb::StrictTotallyOrderedWith<T1> T2, cjdb::StrictTotallyOrderedWith<T1> T3>
requires cjdb::StrictTotallyOrderedWith<T2, T3>
void check_less(T1 x, T2 y, T3 z)
{
   REQUIRE(x < y);
   REQUIRE(y < z);

   constexpr auto less = cjdb::ranges::less{};
   // anti-reflexive
   CHECK(not less(x, x));

   // anti-symmetric
   CHECK(less(x, y));
   CHECK(not less(y, x));

   // transitivity
   CHECK(less(y, z));
   REQUIRE(less(x, z));

   // trichotomy law
   auto const copy = x;
   REQUIRE(x == copy);
   CHECK(not less(x, copy));
   CHECK(not less(copy, x));
}

TEST_CASE("Test ranges::equal_to", "[rangecmp.equal_to]") {
   check_less(0, 1, 2);
   check_less(0, 1.0, 2.0f);

   SECTION("Check strings with the same length, different case.") {
      using namespace std::string_literals;
      auto const a = "Hello"s;
      auto const b = "hEllo"s;
      constexpr auto c = "hello";
      check_less(a, b, c);
   }
   SECTION("Check strings with differning length, same case.") {
      using namespace std::string_literals;
      auto a = "Co"; // mutable `char const*` constexpr, nor const
      auto const b = "Cod"s;
      auto const c = "Code"s;
      check_less(a, b, c);
   }
   SECTION("Check strings with differing length and differing case.") {
      using namespace std::string_literals;
      auto const a = "Cod"s;
      auto const b = "co"s;
      auto const c = "code"s;
      check_less(a, b, c);
   }
}
