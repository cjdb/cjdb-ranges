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
#ifndef CJDB_DETAIL_CONCEPTS_CORE_DERIVEDFROM_HPP
#define CJDB_DETAIL_CONCEPTS_CORE_DERIVEDFROM_HPP

#include "cjdb/detail/type_traits/type_traits.hpp"

namespace cjdb {
   /// \brief `DerivedFrom<Derived, Base>` is satisfied if and only if `Derived` is publicly and
   ///        unambiguously derived from `Base`, or `Derived` and `Base` are the same class type
   ///        ignoring cv-qualifiers
   /// \see [concept.derivedfrom]
   ///
   template<class Derived, class Base>
   concept DerivedFrom =
      is_base_of_v<Base, Derived> and
      is_convertible_v<const volatile Derived*, const volatile Base*>;
} // namespace cjdb

#endif // CJDB_DETAIL_CONCEPTS_CORE_DERIVEDFROM_HPP
