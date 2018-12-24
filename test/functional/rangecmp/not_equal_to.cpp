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
#include "cjdb/functional/rangecmp/not_equal_to.hpp"

#include <catch2/catch.hpp>
#include "cjdb/concepts/comparison/equalitycomparable.hpp"
#include <utility>
#include <vector>

static_assert(cjdb::ranges::not_equal_to::is_transparent{});

template<class T1, cjdb::EqualityComparableWith<T1> T2>
void check_equal_to(T1 x, T2 y, T1 equal_to_x)
{
   REQUIRE(x != y);
   REQUIRE(x == equal_to_x);

   constexpr auto not_equal_to = cjdb::ranges::not_equal_to{};
   // anti-reflexivity
   CHECK(not not_equal_to(x, x));
   CHECK(not not_equal_to(y, y));

   // symmetry
   CHECK(not_equal_to(x, y));
   CHECK(not_equal_to(y, x));

   // transitivity
   auto check_transitivity = [not_equal_to](auto const& a, auto const& b) {
      auto const copy = a;
      REQUIRE(a == copy);
      CHECK(not_equal_to(b, copy));
   };
   check_transitivity(x, y);
   check_transitivity(y, x);

   CHECK(not not_equal_to(x, equal_to_x));
   CHECK(not not_equal_to(equal_to_x, x));
}

TEST_CASE("Test ranges::equal_to", "[rangecmp.equal_to]") {
   check_equal_to(0, 1, 0);
   check_equal_to(0.0, 1, 0.0);

   {
      auto const first = std::vector{0};
      auto const second = std::vector{1};
      check_equal_to(first, second, first);
   }
}
