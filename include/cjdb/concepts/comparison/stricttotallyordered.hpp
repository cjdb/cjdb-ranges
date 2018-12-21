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
#ifndef CJDB_CONCEPTS_COMPARISON_STRICTTOTALLYORDERED_HPP
#define CJDB_CONCEPTS_COMPARISON_STRICTTOTALLYORDERED_HPP

#include "cjdb/concepts/comparison/boolean.hpp"
#include "cjdb/concepts/comparison/equalitycomparable.hpp"
#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb {
   template<class T>
   concept StrictTotallyOrdered =
      EqualityComparable<T> and
      requires(remove_reference_t<T> const& a, remove_reference_t<T> const& b) {
         a < b;   requires Boolean<decltype(a < b)>;
         a > b;   requires Boolean<decltype(a > b)>;
         a <= b;  requires Boolean<decltype(a <= b)>;
         a >= b;  requires Boolean<decltype(a >= b)>;

         // axiom(remove_reference_t<T> const c) {
         //    {bool(a < b)}   -> not bool(a > b)
         //                   -> not bool(a == b);
         //    {bool(a > b)}   -> not bool(a == b);
         //
         //    {
         //       [[assert: a < b]];
         //       [[assert: b < c]];
         //       bool(a < c);
         //    }
         //
         //    {bool(a > b)}   -> bool(b < a);
         //    {bool(a <= b)}   -> not bool(b < a);
         //    {bool(a >= b)} -> not bool(a < b);
         // }
      };

   template<class T, class U>
   concept StrictTotallyOrderedWith =
      StrictTotallyOrdered<T> and
      StrictTotallyOrdered<U> and
      CommonReference<remove_reference_t<T> const&, remove_reference_t<U> const&> and
      StrictTotallyOrdered<
         common_reference_t<
            remove_reference_t<T> const&,
            remove_reference_t<U> const&>
         > and
      EqualityComparableWith<T, U> and
      requires(remove_reference_t<T> const& t, remove_reference_t<U> const& u) {
         t < u;   requires Boolean<decltype(t < u)>;
         t > u;   requires Boolean<decltype(t > u)>;
         t <= u;  requires Boolean<decltype(t <= u)>;
         t >= u;  requires Boolean<decltype(t >= u)>;
         u < t;   requires Boolean<decltype(u < t)>;
         u > t;   requires Boolean<decltype(u > t)>;
         u <= t;  requires Boolean<decltype(u <= t)>;
         u >= t;  requires Boolean<decltype(u >= t)>;

         // axiom {
         //    using C = common_reference_t<remove_reference_t<T> const&, remove_reference_t<U> const&>>;
         //    bool(t < u) == bool(C(t) < C(u));
         //    bool(t > u) == bool(C(t) > C(u));
         //    bool(t <= u) == bool(C(t) <= C(u));
         //    bool(t >= u) == bool(C(t) >= C(u));
         //    bool(u < t) == bool(C(u) < C(t));
         //    bool(u > t) == bool(C(u) > C(t));
         //    bool(u <= t) == bool(C(u) <= C(t));
         //    bool(u >= t) == bool(C(u) >= C(t));
         // }
      };
} // namespace cjdb

#endif // CJDB_CONCEPTS_COMPARISON_STRICTTOTALLYORDERED_HPP
