//
//  Copyright 2019 Christopher Di Bella
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
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_RELATION_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_RELATION_HPP

#include "cjdb/functional/invoke.hpp"
#include <utility>

namespace cjdb_test {
   template<class R>
   class relation {
   protected:
      constexpr explicit relation(R r) noexcept
         : r_(std::move(r))
      {}

      ~relation() = default;

      template<class A, class B>
      constexpr auto operator()(A&& a, B&& b) noexcept
      { return cjdb::invoke(r_, std::forward<A>(a), std::forward<B>(b)); }

      template<class A, class B>
      constexpr auto operator()(A&& a, B&& b) const noexcept
      { return cjdb::invoke(r_, std::forward<A>(a), std::forward<B>(b)); }
   private:
      R r_;
   };
} // namespace cjdb_test

#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_RELATION_HPP
