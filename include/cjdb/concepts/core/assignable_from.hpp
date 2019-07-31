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
#ifndef CJDB_CONCEPTS_CORE_ASSIGNABLE_HPP
#define CJDB_CONCEPTS_CORE_ASSIGNABLE_HPP

#include "cjdb/concepts/core/common_reference_with.hpp"
#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb {
   /// Let:
   ///    - `lhs` be an lvalue that refers to an object `lcopy` such that `decltype((lhs))` is
   ///      `LHS`,
   ///    - `rhs` be an expression such that `decltype((rhs))` is `RHS`, and
   ///    - `rcopy` be a distinct object that is equal to `rhs`.
   /// `assignable_from<LHS, RHS>` is satisfied only if
   ///    - `addressof(lhs = rhs) == addressof(lcopy)`.
   ///    - After evaluating `lhs = rhs`:
   ///       - `lhs` is equal to `rcopy`, unless `rhs` is a non-`const` xvalue that refers to
   ///         `lcopy`.
   ///       - If `rhs` is a non-`const` xvalue, the resulting state of the object to which it
   ///         refers is valid but unspecified.
   ///       - Otherwise, if `rhs` is a glvalue, the object to which it refers is not modified.
   /// \note Assignment need not be a total function; in particular, if assignment to an object `x`
   ///       can result in a modification of some other object `y`, then `x = y` is likely not in
   ///       the domain of =.
   /// \see [concepts.assignable]
   /// \see [structure.requirements]
   /// \see [lib.types.movedfrom]
   ///
   template<class LHS, class RHS>
   concept assignable_from =
      is_lvalue_reference_v<LHS> and
      common_reference_with<const remove_reference_t<LHS>&, const remove_reference_t<RHS>&> and
      requires(LHS lhs, RHS&& rhs) {
         lhs = std::forward<RHS>(rhs);
         requires same_as<decltype(lhs = std::forward<RHS>(rhs)), LHS>;
      };
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_ASSIGNABLE_HPP
