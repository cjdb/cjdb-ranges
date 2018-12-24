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

#define CJDB_CONSTEXPR_CHECK(...) {                          \
   constexpr auto cjdb_constexpr_check_result = __VA_ARGS__; \
   static_assert(cjdb_constexpr_check_result);               \
}                                                            \

using std::pair;

struct equivalence_result {
   bool x_R_x = false;
   bool x1_R_x2 = false;
   bool y1_R_y2 = false;
   bool x1_R_y1 = false;
   bool x1_R_x2_implies_x1_R_x3 = false;
   bool y1_R_y2_implies_y1_R_y3 = false;
   bool x1_R_y2_implies_x1_R_x3 = false;
   bool x1_R_y2_implies_x1_R_y3 = false;
};

template<cjdb::DefaultConstructible T1, cjdb::DefaultConstructible T2, cjdb::Relation<T1, T2> Comp>
constexpr equivalence_result
check_equivalence(pair<T1, T2> const& a, pair<T1, T2> const& b, pair<T1, T2> const& c, Comp comp)
noexcept(
   noexcept(comp(a.first, a.first)) and
   noexcept(comp(a.first, a.second)) and
   noexcept(comp(a.second, a.first)) and
   noexcept(comp(a.second, a.second)))
{
   auto check_reflexivity = [comp](auto const& x) constexpr noexcept {
      return comp(x, x);
   };
   auto check_symmetry = [comp](auto const& x, auto const& y) constexpr noexcept {
      return comp(x, y) and comp(y, x);
   };
   auto check_transitivity =
      [comp](auto const& x, auto const& y, auto const& z) constexpr noexcept {
         return comp(x, y) and comp(y, z) and comp(x, z);
   };

   return equivalence_result{
      check_reflexivity(a.first),
      check_symmetry(a.first, b.first),
      check_symmetry(a.second, b.second),
      check_symmetry(a.first, b.second),
      check_transitivity(a.first, b.first, c.first),
      check_transitivity(a.second, b.second, c.second),
      check_transitivity(a.first, b.second, c.first),
      check_transitivity(a.first, b.second, c.second)
   };
}

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
check_equal_to(pair<T1, T2> const& a, pair<T1, T2> const& b, pair<T1, T2> const& c) noexcept(
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
