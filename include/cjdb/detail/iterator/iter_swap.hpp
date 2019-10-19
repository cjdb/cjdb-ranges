// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_ITERATOR_ITER_SWAP_HPP
#define CJDB_DETAIL_ITERATOR_ITER_SWAP_HPP

#include "cjdb/detail/iterator/iter_move.hpp"
#include "cjdb/detail/iterator/readable_traits.hpp"
#include "cjdb/iterator/concepts/indirectly_movable_storable.hpp"
#include <utility>

#include "cjdb/detail/define.hpp"

namespace cjdb::ranges::detail_iter_swap {
	struct iter_exchange_move_fn {
		template<typename X, typename Y>
		constexpr iter_value_t<std::remove_reference_t<X>> operator()(X&& x, Y&& y) const
		noexcept(noexcept(iter_value_t<std::remove_reference_t<X>>(iter_move(x))) and
		         noexcept(*x = iter_move(y)))
		{
			auto old_value = iter_value_t<std::remove_reference_t<X>>(iter_move(x));
			*x = iter_move(y);
			return old_value;
		}
	};

	inline constexpr auto iter_exchange_move = iter_exchange_move_fn{};

	template<typename I1, typename I2>
	void iter_swap(I1, I2) = delete;

	template<typename I1, typename I2>
	concept unqualified_iter_swap = requires(I1&& i1, I2&& i2) {
		(void)iter_swap(static_cast<I1&&>(i1), static_cast<I2&&>(i2));
	};

	template<typename I1, typename I2>
	concept swappable_references =
		not unqualified_iter_swap<I1, I2> and
		readable<std::remove_reference_t<I1>> and
		readable<std::remove_reference_t<I2>> and
		swappable_with<iter_reference_t<std::remove_reference_t<I1>>,
		               iter_reference_t<std::remove_reference_t<I2>>>;

	template<typename I1, typename I2>
	concept exchangeable_with =
		not unqualified_iter_swap<I1, I2> and
		not swappable_references<I1, I2> and
		indirectly_movable_storable<std::remove_reference_t<I1>, std::remove_reference_t<I2>> and
		indirectly_movable_storable<std::remove_reference_t<I2>, std::remove_reference_t<I1>>;

	struct iter_swap_fn {
		template<typename I1, typename I2>
		requires unqualified_iter_swap<I1, I2>
		constexpr void operator()(I1&& i1, I2&& i2) const
		CJDB_NOEXCEPT_RETURN(
			(void)iter_swap(std::forward<I1>(i1), std::forward<I2>(i2))
		)

		template<typename I1, typename I2>
		requires swappable_references<I1, I2>
		constexpr void operator()(I1&& i1, I2&& i2) const
		CJDB_NOEXCEPT_RETURN(
			ranges::swap(*std::forward<I1>(i1), *std::forward<I2>(i2))
		)

		template<typename I1, exchangeable_with<I1> I2>
		constexpr void operator()(I1 i1, I2 i2) const
		CJDB_NOEXCEPT_RETURN(
			(void)(*i1 = iter_exchange_move(i2, i1))
		)
	};
} // namespace cjdb::ranges::detail_iter_swap

namespace cjdb::ranges {
	inline constexpr auto iter_swap = cjdb::ranges::detail_iter_swap::iter_swap_fn{};
} // namespace cjdb

#include "cjdb/detail/undef.hpp"

#endif // CJDB_DETAIL_ITERATOR_ITER_SWAP_HPP
