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
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_TRICHOTOMY_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_TRICHOTOMY_HPP

#include "cjdb/concepts/callable/relation.hpp"
#include "cjdb/concepts/comparison/equality_comparable.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/functional/rangecmp/relation.hpp"
#include <utility>

namespace cjdb_test {
   template<class R>
   class is_trichotomy : protected relation<R> {
   public:
      constexpr explicit is_trichotomy(R r)
         : relation<R>(std::move(r))
      {}

      template<class A, cjdb::equality_comparable_with<A> B>
      constexpr bool trichotomy(A const& a, B const& b) noexcept
      { return trichotomy_impl(*this, a, b); }

      template<class A, cjdb::equality_comparable_with<A> B>
      constexpr bool trichotomy(A const& a, B const& b) const noexcept
      { return trichotomy_impl(*this, a, b); }
   private:
      template<class Self, class A, class B>
      constexpr static bool trichotomy_impl(Self& self, A const& a, B const& b) noexcept
      {
         auto const aRb = static_cast<bool>(self(a, b));
         auto const bRa = static_cast<bool>(self(b, a));
         auto const a_eq_b = static_cast<bool>(a == b);
         return ((not (aRb and bRa)) xor a_eq_b);
      }
   };
} // namespace cjdb_test

#define CHECK_IS_TRICHOTOMY(r, a, b)                           \
   {                                                           \
      using cjdb_test::is_trichotomy;                          \
      CJDB_CONSTEXPR_CHECK(is_trichotomy{r}.trichotomy(a, b)); \
   }                                                           \


#endif CJDB_TEST_FUNCTIONAL_RANGECMP_IS_TRICHOTOMY_HPP
