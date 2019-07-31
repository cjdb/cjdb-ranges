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
#ifndef CJDB_DETAIL_CONCEPTS_CORE_EQUALITY_COMPARABLE_HPP
#define CJDB_DETAIL_CONCEPTS_CORE_EQUALITY_COMPARABLE_HPP

#include "cjdb/concepts/core/convertible_to.hpp"
#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb::detail_weakly_equality_comparable {
   template<class T, class U>
   concept weakly_equality_comparable_with = // exposition only
      requires(remove_reference_t<T> const& t, remove_reference_t<U> const& u) {
         { t == u } -> convertible_to<bool>;
         { t != u } -> convertible_to<bool>;
         { u == t } -> convertible_to<bool>;
         { u != t } -> convertible_to<bool>;

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

#endif // CJDB_DETAIL_CONCEPTS_CORE_EQUALITY_COMPARABLE_HPP
