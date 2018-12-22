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
#include "cjdb/functional/rangecmp/equal_to.hpp"

#include <catch2/catch.hpp>
#include "cjdb/concepts/comparison/equalitycomparable.hpp"
#include <utility>
#include <vector>

static_assert(cjdb::ranges::equal_to::is_transparent{});

template<class T1, cjdb::EqualityComparableWith<T1> T2>
void check_equal_to(T1 x, T2 y, T1 not_equal)
{
   REQUIRE(x == y);
   REQUIRE(x != not_equal);

   constexpr auto equal_to = cjdb::ranges::equal_to{};
   // reflexivity
   CHECK(equal_to(x, x));
   CHECK(equal_to(y, y));

   // symmetry
   CHECK(equal_to(x, y));
   CHECK(equal_to(y, x));

   // transitivity
   auto check_transitivity = [equal_to](auto const& a, auto const& b) {
      auto const copy = a;
      CHECK(equal_to(a, copy));
      CHECK(equal_to(b, copy));
   };
   check_transitivity(x, y);
   check_transitivity(y, x);

   CHECK(not equal_to(x, not_equal));
   CHECK(not equal_to(not_equal, x));
   CHECK(not equal_to(y, not_equal));
   CHECK(not equal_to(not_equal, y));
}

TEST_CASE("Test ranges::equal_to", "[rangecmp.equal_to]") {
   check_equal_to(0, 0, 1);
   check_equal_to(0.0, 0, 1.0);

   {
      auto const first = std::vector{0};
      auto const second = std::vector{1};
      check_equal_to(first, first, second);
   }
}
