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
#include "cjdb/concepts/core/defaultconstructible.hpp"
#include "cjdb/concepts/comparison/equalitycomparable.hpp"
#include "cjdb/concepts/callable/relation.hpp"
#include <utility>
#include <vector>

static_assert(cjdb::ranges::equal_to::is_transparent{});

struct equal_to_result {
      bool a_equals_b = false;
      bool a_equals_c = false;
      bool not_default_constructed = false; // T1{} is used to guarantee that equal_to can return false
      bool can_return_false = false;
      bool rvalues = false;
      equivalence_result lvalues = {};
   };

   template<cjdb::DefaultConstructible T1, cjdb::DefaultConstructible T2>
   requires cjdb::EqualityComparableWith<T1, T2>
   constexpr equal_to_result
   check_equal_to(std::pair<T1, T2> const& a, std::pair<T1, T2> const& b, std::pair<T1, T2> const& c) noexcept(
      noexcept(cjdb::ranges::equal_to{}(a.first,  a.first))  and
      noexcept(cjdb::ranges::equal_to{}(a.first,  a.second)) and
      noexcept(cjdb::ranges::equal_to{}(a.second, a.first))  and
      noexcept(cjdb::ranges::equal_to{}(a.second, a.second)))
   // [[expects: a == b]]
   // [[expects: a == c]]
   // [[expects: a.first != T1{}]]
   {
      constexpr auto equal_to = cjdb::ranges::equal_to{};
      return equal_to_result{
         a == b,
         a == c,
         a.first != T1{},
         not equal_to(a.first, T1{}),
         equal_to(T1{}, T2{}),
         ::check_equivalence(a, b, c, equal_to)
      };
   }

   void check_equal_to_result(equal_to_result const result)
   {
      REQUIRE(result.a_equals_b);
      REQUIRE(result.a_equals_c);
      REQUIRE(result.not_default_constructed);
      REQUIRE(result.can_return_false);
      REQUIRE(result.rvalues);
      REQUIRE(result.lvalues.x_R_x);
      REQUIRE(result.lvalues.x1_R_x2);
      REQUIRE(result.lvalues.y1_R_y2);
      REQUIRE(result.lvalues.x1_R_y1);
      REQUIRE(result.lvalues.x1_R_x2_implies_x1_R_x3);
      REQUIRE(result.lvalues.y1_R_y2_implies_y1_R_y3);
      REQUIRE(result.lvalues.x1_R_y2_implies_x1_R_x3);
      REQUIRE(result.lvalues.x1_R_y2_implies_x1_R_y3);
   }

TEST_CASE("Test ranges::equal_to", "[rangecmp.equal_to]") {
   auto check_with = [](auto const x, auto const y) constexpr noexcept {
      auto a = std::make_pair(x, y);
      auto b = std::make_pair(x, y);
      auto c = std::make_pair(x, y);
      return ::check_equal_to(a, b, c);
   };
   SECTION("equal_to(T, T)") {
      constexpr auto result = check_with(1, 1);
      ::check_equal_to_result(result);
   }
   SECTION("equal_to(T1, T2)") {
      constexpr auto result = check_with(1, 1.0);
      ::check_equal_to_result(result);
   }
   SECTION("equal_to(T2, T1)") {
      constexpr auto result = check_with(1.0, 1);
      ::check_equal_to_result(result);
   }
}
