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
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_TRANSITIVE_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_TRANSITIVE_HPP

#include "cjdb/concepts/callable/relation.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/functional/rangecmp/relation.hpp"
#include <utility>

namespace cjdb_test {
   template<class R>
   class is_transitive : protected relation<R> {
   public:
      constexpr explicit is_transitive(R r)
         : relation<R>(std::move(r))
      {}

      /// \brief Checks that the relation is transitive, with respect to types T and U.
      /// \param a Parameter to check.
      /// \param b Parameter to check.
      /// \returns evaluates as true if, and only if, for some `auto c = a`,
      ///          `invoke(r, a, b) and invoke(r, b, c) and invoke(r, a, c)` evaluates as true;
      ///          false otherwise.
      ///
      template<class A, class B>
      requires cjdb::relation<R, A, B>
      constexpr bool transitive(A const& a, B const& b, A const& c) noexcept
      { return transitive_impl(*this, a, b, c); }

      /// \brief Checks that the relation is transitive, with respect to types T and U.
      /// \param a Parameter to check.
      /// \param b Parameter to check.
      /// \returns evaluates as true if, and only if, for some `auto c = a`,
      ///          `invoke(r, a, b) and invoke(r, b, c) and invoke(r, a, c)` evaluates as true;
      ///          false otherwise.
      ///
      template<class A, class B>
      requires cjdb::relation<R, A, B>
      constexpr bool transitive(A const& a, B const& b, A const& c) const noexcept
      { return transitive_impl(*this, a, b, c); }
   private:
      template<class Self, class A, class B>
      constexpr static bool transitive_impl(Self& self, A const& a, B const& b, A const& c) noexcept
      {
         auto const aRb = self(a, b);
         // [[assert: aRb]];
         if (not aRb) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexceptions"
            throw std::logic_error{"not aRb"};
#pragma clang diagnostic pop
         }

         auto const bRc = self(b, c);
         // [[assert: bRc]];
         if (not bRc) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexceptions"
            throw std::logic_error{"not bRc"};
#pragma clang diagnostic pop
         }

         auto const aRc = self(a, c);
         return aRb and bRc and aRc;
      }
   };
} // namespace cjdb_test

#define CHECK_IS_TRANSITIVE(r, a, b, c)                           \
   {                                                              \
      using cjdb_test::is_transitive;                             \
      CJDB_CONSTEXPR_CHECK(is_transitive{r}.transitive(a, b, c)); \
   }                                                              \



#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_TRANSITIVE_HPP
