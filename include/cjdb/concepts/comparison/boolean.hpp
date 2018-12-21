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
#ifndef CJDB_CONCEPTS_COMPARISON_BOOLEAN_HPP
#define CJDB_CONCEPTS_COMPARISON_BOOLEAN_HPP

#include "cjdb/concepts/core/convertibleto.hpp"
#include "cjdb/concepts/object/movable.hpp"
#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb {
   /// \brief The `Boolean` concept specifies the requirements on a type that is usable in `Boolean`
   ///        contexts.
   ///
   /// Let `b1` and `b2` be lvalues of type `const remove_­reference_­t<B>`. `Boolean<B>` is satisfied
   /// only if
   ///    - `bool(b1) == not bool(!b1)`.
   ///    - `(b1 and b2)`, `(b1 and bool(b2))`, and `(bool(b1) and b2)` are all equal to
   ///      `(bool(b1) and bool(b2))`, and have the same short-circuit evaluation.
   ///    - `(b1 or b2)`, `(b1 or bool(b2))`, and `(bool(b1) or b2)` are all equal to
   ///      `(bool(b1) or bool(b2))`, and have the same short-circuit evaluation.
   ///    - `bool(b1 == b2)`, `bool(b1 == bool(b2))`, and `bool(bool(b1) == b2)` are all equal to
   ///      `(bool(b1) == bool(b2))`.
   ///    - `bool(b1 != b2)`, `bool(b1 != bool(b2))`, and `bool(bool(b1) != b2)` are all equal to
   ///      `(bool(b1) != bool(b2))`.
   ///
   /// \note The types `bool`, `true_­type`, and `bitset<N>::reference` are `Boolean` types.
   ///       Pointers, smart pointers, and types with only explicit conversions to `bool` are not
   ///       `Boolean` types.
   /// \see [concept.boolean]
   /// \see [meta.type.synop]
   /// \see [template.bitset]
   ///
   template<class B>
   concept Boolean =
      Movable<remove_cvref_t<B>> and
      requires(remove_reference_t<B> const& b1, remove_reference_t<B> const& b2, bool const a) {
         requires ConvertibleTo<remove_reference_t<B> const&, bool>;
         not b1;    requires ConvertibleTo<decltype(not b1), bool>;
         b1 and a;  requires Same<decltype(b1 and a), bool>;
         b1 or a;   requires Same<decltype(b1 or a), bool>;
         b1 and b2; requires Same<decltype(b1 and b2), bool>;
         a and b2;  requires Same<decltype(a and b2), bool>;
         b1 or b2;  requires Same<decltype(b1 or b2), bool>;
         a or b2;   requires Same<decltype(a or b2), bool>;
         b1 == b2;  requires ConvertibleTo<decltype(b1 == b2), bool>;
         b1 == a;   requires ConvertibleTo<decltype(b1 == a), bool>;
         a == b2;   requires ConvertibleTo<decltype( a == b2), bool>;
         b1 != b2;  requires ConvertibleTo<decltype(b1 != b2), bool>;
         b1 != a;   requires ConvertibleTo<decltype(b1 != a), bool>;
         a != b2;   requires ConvertibleTo<decltype( a != b2), bool>;

         // axiom {
         //    bool(b1) == not bool(not b1);
         //
         //    (bool(b1) and bool(b2)) == (b1 and b2);
         //    (bool(b1) and bool(b2)) == (b1 and bool(b2));
         //    (bool(b1) and bool(b2)) == (bool(b1) and b2);
         //
         //    (bool(b1) or bool(b2)) == (b1 or b2);
         //    (bool(b1) or bool(b2)) == (b1 or bool(b2));
         //    (bool(b1) or bool(b2)) == (bool(b1) or b2);
         //
         //    (bool(b1) == bool(b2)) == (b1 == b2);
         //    (bool(b1) == bool(b2)) == (b1 == bool(b2));
         //    (bool(b1) == bool(b2)) == (bool(b1) == b2);
         //
         //    (bool(b1) != bool(b2)) == (b1 != b2);
         //    (bool(b1) != bool(b2)) == (b1 != bool(b2));
         //    (bool(b1) != bool(b2)) == (bool(b1) != b2);
         // }
      };
}

#endif // CJDB_CONCEPTS_COMPARISON_BOOLEAN_HPP
