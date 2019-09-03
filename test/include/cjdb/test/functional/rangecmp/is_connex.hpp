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
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_CONNEX_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_CONNEX_HPP

#include "cjdb/concepts/callable/relation.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/functional/rangecmp/relation.hpp"
#include <utility>

namespace cjdb_test {
   template<class R>
   class is_connex : protected relation<R> {
   public:
      constexpr explicit is_connex(R r) noexcept
         : relation<R>(std::move(r))
      {}

      template<class A, class B>
      [[nodiscard]] constexpr bool connex(A const& a, B const& b) noexcept
      { return connex_impl(*this, a, b); }

      template<class A, class B>
      [[nodiscard]] constexpr bool connex(A const& a, B const& b) const noexcept
      { return connex_impl(*this, a, b); }
   private:
      template<class Self, class A, class B>
      [[nodiscard]] constexpr static bool connex_impl(Self& self, A const& a, B const& b) noexcept
      { return self(a, b) or self(b, a); }
   };
} // namespace cjdb_test

#define CHECK_IS_CONNEX(r, a, b)                       \
   {                                                   \
      using cjdb_test::is_connex;                      \
      CJDB_CONSTEXPR_CHECK(is_connex{r}.connex(a, b)); \
   }                                                   \


#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_CONNEX_HPP
