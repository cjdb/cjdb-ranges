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
#ifndef CJDB_DETAIL_CONCEPTS_CALLABLE_STRICTWEAKORDER_HPP
#define CJDB_DETAIL_CONCEPTS_CALLABLE_STRICTWEAKORDER_HPP

#include "cjdb/detail/concepts/callable/relation.hpp"

namespace cjdb {
   /// \brief A `Relation` satisfies `StrictWeakOrder` only if it imposes a strict weak ordering on
   ///        its arguments.
   ///
   /// The term _strict_ refers to the requirement of an irreflexive relation (`!comp(x, x)` for all
   /// `x`), and the term _weak_ to requirements that are not as strong as those for a total
   /// ordering, but stronger than those for a partial ordering. If we define `equiv(a, b)` as
   /// `!comp(a, b) and !comp(b, a)`, then the requirements are that `comp` and `equiv` both be
   /// transitive relations:
   ///   * `comp(a, b) and comp(b, c)` implies `comp(a, c)`
   ///   * `equiv(a, b) and equiv(b, c)` implies `equiv(a, c)`
   ///
   /// \note Under these conditions, it can be shown that
   ///   * `equiv` is an equivalence relation,
   ///   * `comp` induces a well-defined relation on the equivalence classes determined by `equiv`,
   ///      and
   ///   * the induced relation is a strict total ordering.
   ///
   /// \see [concept.strictweakorder]
   ///
   template<class R, class T, class U>
   concept StrictWeakOrder = Relation<R, T, U>;
   // axiom(R&& r, T&& a, U&& b) {
   //    common_reference_t<remove_reference_t<T> const&, remove_reference_t<U> const&> c;
   //    Relation<T, U> comp;
   //
   //    not comp(a, a);
   //    not comp(b, b);
   //
   //    {
   //       [[assert: comp(a, b)]];
   //       [[assert: comp(b, c)]];
   //       -> comp(a, c);
   //    }
   //    {
   //       auto equiv = [&comp](T&& t, U&& u) { return not comp(a, b) and not comp(b, a); };
   //       [[assert: eqiv(a, b)]];
   //       [[assert: eqiv(b, c)]];
   //       -> eqiv(a, c);
   //    }
   // }
} // namespace cjdb

#endif // CJDB_DETAIL_CONCEPTS_CALLABLE_STRICTWEAKORDER_HPP
