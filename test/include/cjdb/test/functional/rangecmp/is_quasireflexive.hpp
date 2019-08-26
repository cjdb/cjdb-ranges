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
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_QUASIREFLEXIVE_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_QUASIREFLEXIVE_HPP

#include "cjdb/concepts/callable/relation.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/functional/rangecmp/is_reflexive.hpp"
#include <utility>

namespace cjdb_test {
   template<class R>
   class is_quasireflexive : private is_reflexive<R> {
   public:
      constexpr explicit is_quasireflexive(R r)
         : is_reflexive<R>(std::move(r))
      {}

      /// \brief Checks that the relation is reflexive, with respect to type T.
      /// \param a Parameter to check.
      /// \returns invoke(r, a, a)
      ///
      template<class A, class B>
      requires cjdb::relation<R, A, B>
      constexpr bool quasireflexive(A const& a, B const& b) noexcept
      { return quasireflexive_impl(*this, std::move(a), std::move(b)); }

      /// \brief Checks that the relation is reflexive, with respect to type T.
      /// \param a Parameter to check.
      /// \returns invoke(r, a, a)
      ///
      template<class A, class B>
      requires cjdb::relation<R, A, B>
      constexpr bool quasireflexive(A const& a, B const& b) const noexcept
      { return quasireflexive_impl(*this, std::move(a), std::move(b)); }
   private:
      template<class Self, class A, class B>
      constexpr static bool quasireflexive_impl(Self& self, A const& a, B const& b) noexcept
      { return self(a, b) and self.reflexive(a) and self.reflexive(b); }
   };
} // namespace cjdb_test

#define CHECK_IS_QUASIREFLEXIVE(r, a, b)                                    \
   {                                                                        \
      using cjdb_test::is_quasireflexive;                                   \
      CJDB_CONSTEXPR_CHECK(is_quasireflexive{r}.quasi_reflexive(a, b));     \
   }                                                                        \


#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_QUASIREFLEXIVE_HPP
