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
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_ASYMMETRIC_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_ASYMMETRIC_HPP

#include "cjdb/concepts/callable/relation.hpp"
#include "cjdb/concepts/comparison/equalitycomparable.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/functional/rangecmp/is_antisymmetric.hpp"
#include "cjdb/test/functional/rangecmp/is_irreflexive.hpp"
#include <utility>

namespace cjdb_test {
   template<class R>
   class is_asymmetric
   : private is_irreflexive<R>
   , private is_antisymmetric<R> {
   public:
      constexpr explicit is_asymmetric(R r) noexcept
         : is_irreflexive<R>(r)
         , is_antisymmetric<R>(r)
      {}

      template<class A, cjdb::EqualityComparableWith<A> B>
      requires cjdb::Relation<R, A, B>
      constexpr bool asymmetric(A const& a, B const& b) noexcept
      { return asymmetric_impl(*this, a, b); }

      template<class A, cjdb::EqualityComparableWith<A> B>
      requires cjdb::Relation<R, A, B>
      constexpr bool asymmetric(A const& a, B const& b) const noexcept
      { return asymmetric_impl(*this, a, b); }
   private:
      template<class Self, class A, class B>
      constexpr bool asymmetric_impl(Self& self, A const& a, B const& b) noexcept
      { return self.irreflexive(a) and self.irreflexive(b) and self.antisymmetric(a, b); }
   };
} // namespace cjdb_test

#define CHECK_IS_ASYMMETRIC(r, a, b)                           \
   {                                                           \
      using cjdb_test::is_asymmetric;                          \
      CJDB_CONSTEXPR_CHECK(is_asymmetric{r}.asymmetric(a, b)); \
   }                                                           \


#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_ASYMMETRIC_HPP
