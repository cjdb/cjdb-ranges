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
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_ANTISYMMETRIC_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_ANTISYMMETRIC_HPP

#include "cjdb/concepts/callable/relation.hpp"
#include "cjdb/concepts/comparison/equality_comparable.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/functional/rangecmp/relation.hpp"
#include <utility>

namespace cjdb_test {
   template<class R>
   class is_antisymmetric : protected relation<R> {
   public:
      constexpr explicit is_antisymmetric(R r)
         : relation<R>(std::move(r))
      {}

      /// \brief Checks that the relation is symmetric, with respect to types T and U.
      /// \param a Parameter to check.
      /// \param b Parameter to check.
      /// \returns invoke(r, a, b) == invoke(r, b, a)
      ///
      template<class A, cjdb::equality_comparable_with<A> B>
      requires cjdb::relation<R, A, B>
      [[nodiscard]] constexpr bool antisymmetric(A const& a, B const& b) noexcept
      { return antisymmetric_impl(*this, a, b); }

      /// \brief Checks that the relation is symmetric, with respect to types T and U.
      /// \param a Parameter to check.
      /// \param b Parameter to check.
      /// \returns invoke(r, a, b) == invoke(r, b, a)
      ///
      template<class A, cjdb::equality_comparable_with<A> B>
      requires cjdb::relation<R, A, B>
      [[nodiscard]] constexpr bool antisymmetric(A const& a, B const& b) const noexcept
      { return antisymmetric_impl(*this, a, b); }
   private:
      template<class Self, class A, class B>
      [[nodiscard]] constexpr static bool antisymmetric_impl(Self& self, A const& a, B const& b) noexcept
      { return (self(a, b) != self(b, a)) or (a == b); }
   };
} // namespace cjdb_test

#define CHECK_IS_ANTISYMMETRIC(r, a, b)                              \
   {                                                                 \
      using cjdb_test::is_antisymmetric;                             \
      CJDB_CONSTEXPR_CHECK(is_antisymmetric{r}.antisymmetric(a, b)); \
   }                                                                 \


#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_ANTISYMMETRIC_HPP
