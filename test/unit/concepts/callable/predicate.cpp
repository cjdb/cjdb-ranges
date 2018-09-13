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
#include "cjdb/detail/concepts/callable/predicate.hpp"

#include "functions.hpp"

template<class F, class... Args>
requires cjdb::Predicate<F, Args...>
constexpr void models_Predicate(F, Args&&...) noexcept {}

template<class F, class... Args>
requires (not cjdb::Predicate<F, Args...>)
constexpr void not_Predicate(F, Args&&...) noexcept {}

int main()
{
   {
      using namespace regular_invocable;
      A a;
      models_Predicate(&A::f, a);
      models_Predicate(&A::g, a, 0);
      models_Predicate(&A::h, A{}, 0);
   }
   models_Predicate(predicate::l2r_sorted{}, 0, 0, 0);
   not_Predicate(predicate::not_a_predicate{});

   models_Predicate(relation::less{}, 0, 0.0);
   models_Predicate(relation::greater, 0, 0.0);
}
