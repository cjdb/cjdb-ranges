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
#include "cjdb/detail/concepts/callable/relation.hpp"
#include "cjdb/detail/concepts/callable/strictweakorder.hpp"

#include "functions.hpp"

template<class F, class T1, class T2>
requires cjdb::Relation<F, T1, T2>
constexpr void models_Relation(F&&, T1&&, T2&&) noexcept {}

template<class F, class T1, class T2>
requires (not cjdb::Relation<F, T1, T2>)
constexpr void not_Relation(F&&, T1&&, T2&&) noexcept {}

// Tests also: StrictWeakOrder [concept.strictweakorder]
template<class F, class T1, class T2>
requires cjdb::Relation<F, T1, T2>
constexpr void models_StrictWeakOrder(F&&, T1&&, T2&&) noexcept {}

// Tests also: StrictWeakOrder [concept.strictweakorder]
template<class F, class T1, class T2>
requires (not cjdb::Relation<F, T1, T2>)
constexpr void not_StrictWeakOrder(F&&, T1&&, T2&&) noexcept {}

int main()
{
   {
      using namespace regular_invocable;

      auto a = A{};
      not_Relation(&A::g, a, 0);
      not_Relation(&A::h, A{}, 0);

      // Tests also: StrictWeakOrder [concept.strictweakorder]
      not_StrictWeakOrder(&A::g, a, 0);
      not_StrictWeakOrder(&A::h, A{}, 0);
   }
   {
      using namespace relation;

      models_Relation(less{}, 0, 1);
      models_Relation(greater, 0, 1);

      // Tests also: StrictWeakOrder [concept.strictweakorder]
      models_StrictWeakOrder(less{}, 0, 1);
      models_StrictWeakOrder(greater, 0, 1);
   }
}
