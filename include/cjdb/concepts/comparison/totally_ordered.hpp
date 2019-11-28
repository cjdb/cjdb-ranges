// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_COMPARISON_STRICTTOTALLYORDERED_HPP
#define CJDB_CONCEPTS_COMPARISON_STRICTTOTALLYORDERED_HPP

#include "cjdb/concepts/core/convertible_to.hpp"
#include "cjdb/concepts/comparison/equality_comparable.hpp"
#include "cjdb/detail/concepts/comparison/partially_ordered_with.hpp"
#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb {
	/// \brief Expresses the requirement that objects of a type can be totally ordered.
	/// \pre Axiom:
	/// For some type `T`, let `a`, `b`, and `c` be lvalues of type `remove_reference_t<T> const`. `T`
	/// models `totally_ordered` only if:
	///    * Exactly one of `bool(a < b)`, `bool(a > b)`, or `bool(a == b)` is `true`.
	///    * If `bool(a < b) and bool(b < c)`, then `bool(a < c)`.
	///    * `bool(a <= b) == !bool(b < a)`.
	///    * `bool(a >= b) == !bool(a < b)`.
	///
	template<class T>
	concept totally_ordered =
		equality_comparable<T> and
		detail_partially_ordered_with::partially_ordered_with<T, T>;

	/// \brief Expresses the requirement that objects of two different types can be totally ordered
	///        with respect to one another.
	/// \pre Axiom:
	/// For some types `T` and `U`, let `t` be an lvalue of type `remove_­reference_­t<T> const`, `u` be
	/// an lvalue of type `remove_­reference_­t<U> const`, and `C` be:
	/// ```
	/// common_reference_t<const remove_reference_t<T>&, const remove_reference_t<U>&>
	/// ```
	/// `T` and `U` model totally_­ordered_­with<T, U> only if:
	///    * `bool(t < u) == bool(C(t) < C(u))`.
	///    * `bool(t > u) == bool(C(t) > C(u))`.
	///    * `bool(t <= u) == bool(C(t) <= C(u))`.
	///    * `bool(t >= u) == bool(C(t) >= C(u))`.
	///    * `bool(u < t) == bool(C(u) < C(t))`.
	///    * `bool(u > t) == bool(C(u) > C(t))`.
	///    * `bool(u <= t) == bool(C(u) <= C(t))`.
	///    * `bool(u >= t) == bool(C(u) >= C(t))`.
	///
	template<class T, class U>
	concept totally_ordered_with =
		totally_ordered<T> and
		totally_ordered<U> and
		common_reference_with<remove_reference_t<T> const&, remove_reference_t<U> const&> and
		totally_ordered<
			common_reference_t<remove_reference_t<T> const&, remove_reference_t<U> const&>> and
		equality_comparable_with<T, U> and
		detail_partially_ordered_with::partially_ordered_with<T, U>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_COMPARISON_STRICTTOTALLYORDERED_HPP
