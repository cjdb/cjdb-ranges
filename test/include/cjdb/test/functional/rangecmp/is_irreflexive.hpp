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
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_IRREFLEXIVE_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_IRREFLEXIVE_HPP

#include "cjdb/concepts/callable/relation.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/functional/rangecmp/is_reflexive.hpp"
#include <utility>

namespace cjdb_test {
   template<class R>
   class is_irreflexive : private is_reflexive<R> {
   public:
      constexpr explicit is_irreflexive(R r) noexcept
         : is_reflexive<R>(r)
      {}

      /// \brief Checks that the relation is reflexive, with respect to type T.
      /// \param a Parameter to check.
      /// \returns invoke(r, a, a)
      ///
      template<class A>
      requires cjdb::Relation<R, A, A>
      constexpr bool irreflexive(A const& a) noexcept
      { return irreflexive_impl(*this, a); }

      /// \brief Checks that the relation is reflexive, with respect to type T.
      /// \param a Parameter to check.
      /// \returns invoke(r, a, a)
      ///
      template<class A>
      requires cjdb::Relation<R, A, A>
      constexpr bool irreflexive(A const& a) const noexcept
      { return irreflexive_impl(*this, a); }
   private:
      template<class Self, class A>
      constexpr static bool irreflexive_impl(Self& self, A const& a)
      { return not self.reflexive(a); }
   };
} // namespace cjdb_test

#define CHECK_IS_IRREFLEXIVE(r, a)                            \
   {                                                          \
      using cjdb_test::is_irreflexive;                        \
      CJDB_CONSTEXPR_CHECK(is_irreflexive{r}.irreflexive(a)); \
   }                                                          \


#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_IRREFLEXIVE_HPP
