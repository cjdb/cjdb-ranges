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
#ifndef CJDB_CONCEPTS_CALLABLE_RELATION_HPP
#define CJDB_CONCEPTS_CALLABLE_RELATION_HPP

#include "cjdb/concepts/core/commonreference.hpp"
#include "cjdb/concepts/callable/predicate.hpp"
#include "cjdb/type_traits/common_reference.hpp"
#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb {
   /// \see [concept.relation]
   ///
   template<class R, class T, class U>
   concept Relation =
      Predicate<R, T, T> and
      Predicate<R, U, U> and
      CommonReference<remove_reference_t<T> const&, remove_reference_t<U> const&> and
      Predicate<R,
         common_reference_t<remove_reference_t<T> const&, remove_reference_t<U> const&>,
         common_reference_t<remove_reference_t<T> const&, remove_reference_t<U> const&>> and
      Predicate<R, T, U> and
      Predicate<R, U, T>;
      // axiom(R&& r, T&& t, U&& u) {
      //    using C = common_reference_t<remove_reference_t<T> const&, remove_reference_t<U> const&>;
      //    bool(r(t, u)) == bool(r(C(t), C(u)));
      //    bool(r(u, t)) == bool(r(C(u), C(t)));
      // }
} // namespace cjdb

#endif // CJDB_CONCEPTS_CALLABLE_RELATION_HPP
