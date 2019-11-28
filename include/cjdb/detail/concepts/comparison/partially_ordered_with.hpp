// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_CONCEPTS_COMPARISON_PARTIALLY_ORDERED_WITH_HPP
#define CJDB_DETAIL_CONCEPTS_COMPARISON_PARTIALLY_ORDERED_WITH_HPP

#include "cjdb/concepts/core/convertible_to.hpp"
#include <type_traits>

namespace cjdb::detail_partially_ordered_with {
	/// \pre Axiom:
	/// Let `t` and `u` be lvalues of types `remove_­reference_­t<T> const` and
	/// `remove_­reference_­t<U> const`, respectively. `T` and `U` model partially_ordered_with only if:
	///   * `t < u`, `t <= u`, `t > u`, `t >= u`, `u < t`, `u <= t`, `u > t`, and `u >= t` have the
	///     same domain.
	///   * `bool(t < u) == bool(u > t)` is `true`,
	///   * `bool(u < t) == bool(t > u)` is `true`,
	///   * `bool(t <= u) == bool(u >= t)` is `true`, and
	///   * `bool(u <= t) == bool(t >= u)` is `true`.
	///
	template<class T, class U>
	concept partially_ordered_with =
	requires(std::remove_reference_t<T> const& t, std::remove_reference_t<U> const& u) {
		{ t <  u } -> convertible_to<bool>;
		{ t >  u } -> convertible_to<bool>;
		{ t <= u } -> convertible_to<bool>;
		{ t >= u } -> convertible_to<bool>;
		{ u <  t } -> convertible_to<bool>;
		{ u >  t } -> convertible_to<bool>;
		{ u <= t } -> convertible_to<bool>;
		{ u >= t } -> convertible_to<bool>;
	};
} // namespace cjdb::detail_partially_ordered_with

#endif // CJDB_DETAIL_CONCEPTS_COMPARISON_PARTIALLY_ORDERED_WITH_HPP
