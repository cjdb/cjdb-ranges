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
#include "cjdb/concepts/callable/regular_invocable.hpp"

#include "functions.hpp"
#include <memory>
#include <utility>

template<class F, class... Args>
requires cjdb::regular_invocable<F, Args...>
constexpr void models_RegularInvocable(F, Args&&...) noexcept {}

template<class F, class... Args>
requires (not cjdb::regular_invocable<F, Args...>)
constexpr void not_RegularInvocable(F, Args&&...) noexcept {}

int main()
{
   {
      using namespace regular_invocable;

      models_RegularInvocable(f);
      not_RegularInvocable(f, 0);

      models_RegularInvocable(g, 2);
      not_RegularInvocable(g);
      not_RegularInvocable(g, 3, 0);

      not_RegularInvocable(&A::i_);
      not_RegularInvocable(&A::f);

      {
         auto a = A{};
         models_RegularInvocable(&A::i_, a);
         models_RegularInvocable(&A::f, a);
         models_RegularInvocable(&A::g, a, 0);
         not_RegularInvocable(&A::g, a);
         not_RegularInvocable(&A::g, 0);
         not_RegularInvocable(&A::h);

         auto const& c = a;
         models_RegularInvocable(&A::i_, c);
         models_RegularInvocable(&A::f, c);
         not_RegularInvocable(&A::g, c, 0);
         not_RegularInvocable(&A::h, c, 0);
      }

      models_RegularInvocable(&A::i_, A{});
      models_RegularInvocable(&A::f, A{});
      models_RegularInvocable(&A::g, A{}, 0);
      models_RegularInvocable(&A::h, A{}, 0);

      {
         auto up = std::make_unique<A>();
         models_RegularInvocable(&A::i_, up);
         models_RegularInvocable(&A::f, up);
         models_RegularInvocable(&A::g, up, 0);
         not_RegularInvocable(&A::h, up, 0);
      }
      {
         auto sp = std::make_shared<A>();
         models_RegularInvocable(&A::i_, sp);
         models_RegularInvocable(&A::f, sp);
         models_RegularInvocable(&A::g, sp, 0);
         not_RegularInvocable(&A::h, sp, 0);
      }
   }

   models_RegularInvocable(predicate::l2r_sorted{}, 0, 1, 2);
   models_RegularInvocable(predicate::not_a_predicate{});
}
