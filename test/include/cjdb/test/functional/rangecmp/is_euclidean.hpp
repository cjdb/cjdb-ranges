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
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_EUCLIDEAN_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_EUCLIDEAN_HPP

#include "cjdb/concepts/callable/relation.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/functional/rangecmp/relation.hpp"
#include <utility>

namespace cjdb_test {
   template<class R>
   class is_euclidean_relation : protected relation<R> {
   public:
      constexpr explicit is_euclidean_relation(R r) noexcept
         : relation<R>(std::move(r))
      {}

      template<class A, class B>
      requires cjdb::relation<R, A, B>
      constexpr bool euclidean(A const& a, B const& b, A const& c) noexcept
      { return euclidean_impl(*this, a, b, c); }

      template<class A, class B>
      requires cjdb::relation<R, A, B>
      constexpr bool euclidean(A const& a, B const& b, A const& c) const noexcept
      { return euclidean_impl(*this, a, b, c); }
   private:
      template<class Self, class A, class B>
      constexpr static bool euclidean_impl(Self& self, A const& a, B const& b, A const& c) noexcept
      { return self(a, b) and self(a, c) and self(b, c); }
   };
} // namespace cjdb_test

#define CHECK_IS_EUCLIDEAN_RELATION(r, a, b, c)                          \
   {                                                                     \
      using cjdb_test::is_euclidean_relation;                            \
      CJDB_CONSTEXPR_CHECK(is_euclidean_relation{r}.euclidean(a, b, c)); \
   }                                                                     \


#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_EUCLIDEAN_HPP
