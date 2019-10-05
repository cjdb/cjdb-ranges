// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_CORE_SWAPPABLE_HPP
#define CJDB_CONCEPTS_CORE_SWAPPABLE_HPP

#include "cjdb/detail/concepts/core/swappable.hpp"

namespace cjdb {
	namespace ranges {
		inline constexpr auto swap = detail_swap::swap_fn{};
	} // namespace ranges

	/// \see [concept.swappable]
	///
	template<class T>
	concept swappable = requires(T& a, T& b) { ranges::swap(a, b); };

	/// \see [concept.swappable]
	///
	template<class T, class U>
	concept swappable_with =
		common_reference_with<T, U> and
		requires(T&& t, U&& u) {
			ranges::swap(std::forward<T>(t), std::forward<T>(t));
			ranges::swap(std::forward<U>(u), std::forward<U>(u));
			ranges::swap(std::forward<T>(t), std::forward<U>(u));
			ranges::swap(std::forward<U>(u), std::forward<T>(t));
		};
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_SWAPPABLE_HPP
