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
#ifndef CJDB_CONCEPTS_COMPARISON_EQUALITYCOMPARABLE_HPP
#define CJDB_CONCEPTS_COMPARISON_EQUALITYCOMPARABLE_HPP

#include "cjdb/concepts/core/common_reference_with.hpp"
#include "cjdb/detail/concepts/core/equality_comparable.hpp"

namespace cjdb {
   template<class T>
   concept equality_comparable =
      detail_weakly_equality_comparable::weakly_equality_comparable_with<T, T>;

   template<class T, class U>
   concept equality_comparable_with =
      equality_comparable<T> and
      equality_comparable<U> and
      common_reference_with<remove_reference_t<T> const&, remove_reference_t<U> const&> and
      equality_comparable<common_reference_t<remove_reference_t<T> const&, remove_reference_t<U> const&>> and
      detail_weakly_equality_comparable::weakly_equality_comparable_with<T, U>;
      // axiom(remove_reference_t<T> const t, remove_reference_t<U> const u) {
      //    using C = common_reference_t<remove_reference_t<T> const&, remove_reference_t<U> const&>;
      //    bool(t == u) == bool(C(t) == C(u));
      // }
} // namespace cjdb

#endif // CJDB_CONCEPTS_COMPARISON_EQUALITYCOMPARABLE_HPP
