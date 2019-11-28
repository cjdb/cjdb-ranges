// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_CONCEPTS_COMPARISON_WEAKLY_EQUALITY_COMPARABLE_WITH_HPP
#define CJDB_DETAIL_CONCEPTS_COMPARISON_WEAKLY_EQUALITY_COMPARABLE_WITH_HPP

#include "cjdb/concepts/core/convertible_to.hpp"
#include <type_traits>

namespace cjdb::detail_weakly_equality_comparable_with {
	/// \brief Minimal checks on whether or not cross-type equality can work.
	/// \internal
	/// \pre Axiom:
	/// For some types `T` and `U`, let `t` and `u` be lvalues of types `remove_­reference_­t<T> const`
	/// and `remove_­reference_­t<U> const` respectively.
	/// `T` and `U` model `weakly_equality_comparable_with<T, U>` only if:
	///    * `t == u`, `u == t`, `t != u`, and `u != t` have the same domain.
	///    * `bool(u == t) == bool(t == u)`.
	///    * `bool(t != u) == !bool(t == u)`.
	///    * `bool(u != t) == bool(t != u)`.
	///
	template<class T, class U>
	concept weakly_equality_comparable_with = // exposition only
		requires(std::remove_reference_t<T> const& t, std::remove_reference_t<U> const& u) {
			{ t == u } -> convertible_to<bool>;
			{ t != u } -> convertible_to<bool>;
			{ u == t } -> convertible_to<bool>;
			{ u != t } -> convertible_to<bool>;
		};
} // namespace cjdb::detail_weakly_equality_comparable_with

#endif // CJDB_DETAIL_CONCEPTS_COMPARISON_WEAKLY_EQUALITY_COMPARABLE_WITH_HPP
