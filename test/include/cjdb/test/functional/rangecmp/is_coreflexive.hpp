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
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_COREFLEXIVE_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_COREFLEXIVE_HPP

#include "cjdb/concepts/callable/relation.hpp"
#include "cjdb/concepts/comparison/equality_comparable.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/functional/rangecmp/is_reflexive.hpp"
#include <utility>

namespace cjdb_test {
   template<class R>
   class is_coreflexive : private is_reflexive<R> {
   public:
      constexpr explicit is_coreflexive(R r) noexcept
         : is_reflexive<R>(std::move(r))
      {}

      /// \brief Checks that the relation is reflexive, with respect to type T.
      /// \param a Parameter to check.
      /// \returns invoke(r, a, a)
      ///
      template<cjdb::equality_comparable A>
      requires cjdb::relation<R, A, A>
      constexpr bool coreflexive(A const& a) noexcept
      { return coreflexive_impl(*this, std::move(a)); }

      /// \brief Checks that the relation is reflexive, with respect to type T.
      /// \param a Parameter to check.
      /// \returns invoke(r, a, a)
      ///
      template<cjdb::equality_comparable A>
      requires cjdb::relation<R, A, A>
      constexpr bool coreflexive(A const& a) const noexcept
      { return coreflexive_impl(*this, std::move(a)); }
   private:
      template<class Self, class A>
      constexpr static bool coreflexive_impl(Self& self, A const& a)
      { return self.reflexive(a) and a == a; }
   };
} // namespace cjdb_test

#define CHECK_IS_COREFLEXIVE(r, a)                            \
   {                                                          \
      using cjdb_test::is_coreflexive;                        \
      CJDB_CONSTEXPR_CHECK(is_coreflexive{r}.coreflexive(a)); \
   }                                                          \


#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_COREFLEXIVE_HPP
