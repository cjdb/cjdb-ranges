// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_COMPARISON_BOOLEAN_HPP
#define CJDB_CONCEPTS_COMPARISON_BOOLEAN_HPP

#include "cjdb/concepts/core/convertible_to.hpp"
#include "cjdb/concepts/object/movable.hpp"
#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb {
	/// \brief The `boolean` concept specifies the requirements on a type that is usable in `boolean`
	///        contexts.
	///
	/// Let `b1` and `b2` be lvalues of type `const remove_­reference_­t<B>`. `boolean<B>` is satisfied
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
	/// \note The types `bool`, `true_­type`, and `bitset<N>::reference` are `boolean` types.
	///       Pointers, smart pointers, and types with only explicit conversions to `bool` are not
	///       `boolean` types.
	/// \see [concept.boolean]
	/// \see [meta.type.synop]
	/// \see [template.bitset]
	///
	template<class B>
	concept boolean =
		movable<remove_cvref_t<B>> and
		requires(remove_reference_t<B> const& b1, remove_reference_t<B> const& b2, bool const a) {
			requires convertible_to<remove_reference_t<B> const&, bool>;
			not b1;    requires convertible_to<decltype(not b1), bool>;
			b1 and a;  requires same_as<decltype(b1 and a), bool>;
			b1 or a;   requires same_as<decltype(b1 or a), bool>;
			b1 and b2; requires same_as<decltype(b1 and b2), bool>;
			a and b2;  requires same_as<decltype(a and b2), bool>;
			b1 or b2;  requires same_as<decltype(b1 or b2), bool>;
			a or b2;   requires same_as<decltype(a or b2), bool>;
			b1 == b2;  requires convertible_to<decltype(b1 == b2), bool>;
			b1 == a;   requires convertible_to<decltype(b1 == a), bool>;
			a == b2;   requires convertible_to<decltype( a == b2), bool>;
			b1 != b2;  requires convertible_to<decltype(b1 != b2), bool>;
			b1 != a;   requires convertible_to<decltype(b1 != a), bool>;
			a != b2;   requires convertible_to<decltype( a != b2), bool>;

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
} // namespace cjdb

#endif // CJDB_CONCEPTS_COMPARISON_BOOLEAN_HPP
