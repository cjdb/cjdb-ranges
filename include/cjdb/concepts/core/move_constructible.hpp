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
#ifndef CJDB_CONCEPTS_CORE_MOVECONSTRUCTIBLE_HPP
#define CJDB_CONCEPTS_CORE_MOVECONSTRUCTIBLE_HPP

#include "cjdb/concepts/core/constructible_from.hpp"
#include "cjdb/concepts/core/convertible_to.hpp"

namespace cjdb {
   /// If `T` is an object type, then let `rv` be an rvalue of type `T` and `u2` a distinct object
   /// of type `T` equal to `rv`. `move_constructible<T>` is satisfied only if
   ///    - After the definition `T u = rv;`, `u` is equal to `u2`.
   ///    - `T(rv)` is equal to `u2`.
   ///    - If `T` is not `const`, `rv`'s resulting state is valid but unspecified; otherwise, it is
   ///      unchanged.
   /// \see [concepts.moveconstructible]
   /// \see [lib.types.movedfrom]
   ///
   template<class T>
   concept move_constructible = constructible_from<T, T> and convertible_to<T, T>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_MOVECONSTRUCTIBLE_HPP
