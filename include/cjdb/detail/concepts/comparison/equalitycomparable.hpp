//
//  Copyright Christopher Di Bella
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
#ifndef CJDB_DETAIL_CONCEPTS_COMPARISON_EQUALITYCOMPARABLE_HPP
#define CJDB_DETAIL_CONCEPTS_COMPARISON_EQUALITYCOMPARABLE_HPP

#include "cjdb/detail/concepts/comparison/boolean.hpp"
#include "cjdb/detail/type_traits/type_traits.hpp"

namespace cjdb {
   namespace detail_weakly_equality_comparable {
      template<class T, class U>
      concept weakly_equality_comparable_with = // exposition only
         requires(std::remove_reference_t<T> const& t, remove_reference_t<U> const& u) {
            t == u; requires Boolean<decltype(t == u)>;
            t != u; requires Boolean<decltype(t != u)>;
            u == t; requires Boolean<decltype(u == t)>;
            u != t; requires Boolean<decltype(u != t)>;

            // axiom {
            //    domain(t == u) == domain(u == t);
            //    domain(t == u) == domain(t != u);
            //    domain(t != u) == domain(u != t);
            //
            //    bool(u == t) == bool(t == u);
            //    bool(t != u) == not bool(t == u);
            //    bool(u != t) == bool(t != u);
            // }
         };
   } // namespace detail_weakly_equality_comparable

   template<class T>
   concept EqualityComparable =
      detail_weakly_equality_comparable::weakly_equality_comparable_with<T, T>;

   template<class T, class U>
   concept EqualityComparableWith =
      EqualityComparable<T> and
      EqualityComparable<U> and
      CommonReference<remove_reference_t<T> const&, remove_reference_t<U> const&> and
      EqualityComparable<
         common_reference_t<
            remove_reference_t<T> const&,
            remove_reference_t<U> const&
         >
      > and
      detail_weakly_equality_comparable::weakly_equality_comparable_with<T, U>;
      // axiom(remove_reference_t<T> const t, remove_reference_t<U> const u) {
      //    using C = common_reference_t<remove_reference_t<T> const&, remove_reference_t<U> const&>;
      //    bool(t == u) == bool(C(t) == C(u));
      // }
} // namespace cjdb

#endif // CJDB_DETAIL_CONCEPTS_COMPARISON_EQUALITYCOMPARABLE_HPP
