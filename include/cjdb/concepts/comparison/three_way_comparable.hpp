// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_THREE_WAY_COMPARABLE_HPP
#define CJDB_CONCEPTS_THREE_WAY_COMPARABLE_HPP

#include <version>
#if defined(__cpp_lib_three_way_comparison) and __cpp_lib_three_way_comparison >= 201907

#include "cjdb/concepts/core/common_reference_with.hpp"
#include "cjdb/concepts/core/convertible_to.hpp"
#include "cjdb/detail/concepts/comparison/compare_as.hpp"
#include "cjdb/detail/concepts/comparison/partially_ordered_with.hpp"
#include "cjdb/detail/concepts/comparison/weakly_equality_comparable_with.hpp"
#include <compare>
#include <type_traits>

namespace cjdb {
	/// \brief Expresses the requirement that a type can be ordered with respect to some ordering
	///        `Cat` using the spaceship operator.
	/// \pre Axiom:
	/// Let `a` and `b` be lvalues of type `remove_­reference_­t<T> const`. `T` and `Cat` model
	/// `three_­way_­comparable<T, Cat>` only if:
	///    * `(a <=> b == 0) == bool(a == b)` is `true`;
	///    * `(a <=> b != 0) == bool(a != b)` is `true`;
	///    * `((a <=> b) <=> 0)` and `(0 <=> (b <=> a))` are equal;
	///    * `(a <=> b < 0) == bool(a < b)` is `true`,
	///    * `(a <=> b > 0) == bool(a > b)` is `true`,
	///    * `(a <=> b <= 0) == bool(a <= b)` is `true`, and
	///    * `(a <=> b >= 0) == bool(a >= b)` is `true`; and
	///    * If `Cat` is convertible to `std::strong_­ordering`, `T` models `totally_­ordered`.
	///
	template<class T, class Cat = std::partial_ordering>
	concept three_way_comparable =
		detail_weakly_equality_comparable_with::weakly_equality_comparable_with<T, T> and
		detail_partially_ordered_with::partially_ordered_with<T, T> and
		requires(std::remove_reference_t<T> const& a, std::remove_reference_t<T> const& b) {
			{ a <=> b } -> detail_compares_as::compares_as<Cat>;
		};

	/// \brief Expresses the requirement that two types can be ordered with respect to one another,
	///        according to some ordering `Cat` using the spaceship operator.
	/// \pre Axiom:
	/// Let `t` and `u` be lvalues of types `remove_­reference_­t<T> const` and
	/// `remove_­reference_­t<U> const`, respectively. Let `C` be
	/// ```
	/// common_­reference_­t<const remove_­reference_­t<T>&, const remove_­reference_­t<U>&>
	/// ```
	/// `T`, `U`, and `Cat` model `three_­way_­comparable_­with` only if:
	///    * `t <=> u` and `u <=> t` have the same domain;
	///    * `((t <=> u) <=> 0)` and `(0 <=> (u <=> t))` are equal;
	///    * `(t <=> u == 0) == bool(t == u)` is `true`;
	///    * `(t <=> u != 0) == bool(t != u)` is `true`;
	///    * `Cat(t <=> u) == Cat(C(t) <=> C(u))` is `true`;
	///    * `(t <=> u < 0) == bool(t < u)` is `true`,
	///    * `(t <=> u > 0) == bool(t > u)` is `true`,
	///    * `(t <=> u <= 0) == bool(t <= u)` is `true`,
	///    * `(t <=> u >= 0) == bool(t >= u)` is `true`; and
	///    * if `Cat` is convertible to `std::strong_­ordering`, `T` and `U` model
	///      `totally_­ordered_­with`.
	///
	template<class T, class U, class Cat = std::partial_ordering>
	concept three_way_comparable_with =
		detail_weakly_equality_comparable_with::weakly_equality_comparable_with<T, U> and
		detail_partially_ordered_with::partially_ordered_with<T, U> and
		three_way_comparable<T, Cat> and
		three_way_comparable<U, Cat> and
		common_reference_with<std::remove_reference_t<T> const&, std::remove_reference_t<U> const&> and
		three_way_comparable<
			common_reference_t<std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>, Cat> and
		requires(std::remove_reference_t<T> const& t, std::remove_reference_t<U> const& u) {
			{ t <=> u } -> detail_compares_as::compares_as<Cat>;
			{ u <=> t } -> detail_compares_as::compares_as<Cat>;
		};
} // namespace cjdb

#endif // __cpp_lib_three_way_comparison
#endif // CJDB_CONCEPTS_THREE_WAY_COMPARABLE_HPP
