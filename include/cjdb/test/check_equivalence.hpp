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
#include "cjdb/concepts/callable/relation.hpp"
#include "cjdb/concepts/comparison/equalitycomparable.hpp"
#include "cjdb/concepts/core/defaultconstructible.hpp"
#include <utility>

namespace cjdb_test {
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
   check_equivalence(std::pair<T1, T2> const& a, std::pair<T1, T2> const& b,
      std::pair<T1, T2> const& c, Comp comp)
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
}