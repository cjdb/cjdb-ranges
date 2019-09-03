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
#ifndef CJDB_CONCEPTS_CORE_CONVERTIBLE_TO_HPP
#define CJDB_CONCEPTS_CORE_CONVERTIBLE_TO_HPP

#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb {
   /// \brief The `convertible_to` concept requires an expression of a particular type and value
   ///        category to be both implicitly and explicitly convertible to some other type.
   ///
   /// The implicit and explicit conversions are required to produce equal results.
   ///
   /// Let `test` be the invented function:
   ///
   /// ```cpp
   /// To test(From (&f)()) {
   ///    return f();
   /// }
   /// ```
   /// and let `f` be a function with no arguments and return type `From` such that `f()` is
   /// equality-preserving.
   /// `convertible_to<From, To>` is satisfied only if:
   ///     - `To` is not an object or reference-to-object type, or `static_­cast<To>(f())` is equal
   ///       to `test(f)`.
   ///     - `From` is not a reference-to-object type, or
   ///        - If `From` is an rvalue reference to a non const-qualified type, the resulting state
   ///          of the object referenced by `f()` after either above expression is valid but
   ///          unspecified.
   ///        - Otherwise, the object referred to by `f()` is not modified by either above
   ///          expression.
   /// \see [concept.convertibleto]
   /// \see [lib.types.movedfrom]
   ///
   template<class From, class To>
   concept convertible_to =
      is_convertible_v<From, To> and
      requires(From (&f)()) {
         static_cast<To>(f());
      };
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_CONVERTIBLE_TO_HPP
