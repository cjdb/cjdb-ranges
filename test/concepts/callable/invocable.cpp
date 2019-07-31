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
#include "cjdb/concepts/callable/invocable.hpp"

#include "functions.hpp"
#include <memory>
#include <random>
#include <utility>

template<class F, class... Args>
requires cjdb::invocable<F, Args...>
constexpr void models_Invocable(F, Args&&...) noexcept {}

template<class F, class... Args>
requires (not cjdb::invocable<F, Args...>)
constexpr void not_Invocable(F, Args&&...) noexcept {}

int main()
{
   {
      using namespace regular_invocable;

      models_Invocable(f);
      not_Invocable(f, 0);

      models_Invocable(g, 2);
      not_Invocable(g);
      not_Invocable(g, 3, 0);

      not_Invocable(&A::i);
      not_Invocable(&A::f);

      {
         auto a = A{};
         models_Invocable(&A::i, a);
         models_Invocable(&A::f, a);
         models_Invocable(&A::g, a, 0);
         not_Invocable(&A::g, a);
         not_Invocable(&A::g, 0);
         not_Invocable(&A::h);

         auto const& c = a;
         models_Invocable(&A::i, c);
         models_Invocable(&A::f, c);
         not_Invocable(&A::g, c, 0);
         not_Invocable(&A::h, c, 0);
      }

      models_Invocable(&A::i, A{});
      models_Invocable(&A::f, A{});
      models_Invocable(&A::g, A{}, 0);
      models_Invocable(&A::h, A{}, 0);

      {
         auto up = std::make_unique<A>();
         models_Invocable(&A::i, up);
         models_Invocable(&A::f, up);
         models_Invocable(&A::g, up, 0);
         not_Invocable(&A::h, up, 0);
      }
      {
         auto sp = std::make_shared<A>();
         models_Invocable(&A::i, sp);
         models_Invocable(&A::f, sp);
         models_Invocable(&A::g, sp, 0);
         not_Invocable(&A::h, sp, 0);
      }
   }
   {
      auto generator = std::mt19937_64{std::random_device{}()};
      auto distribution = std::uniform_int_distribution<>();
      models_Invocable(distribution, generator);
   }
}
