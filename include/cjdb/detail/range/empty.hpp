// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_RANGE_EMPTY_HPP
#define CJDB_DETAIL_RANGE_EMPTY_HPP

#include "cjdb/concepts/core/convertible_to.hpp"
#include "cjdb/iterator/concepts/iterator.hpp"
#include "cjdb/range/associated_types.hpp"
#include "cjdb/range/access/begin.hpp"
#include "cjdb/range/access/end.hpp"
#include "cjdb/range/access/size.hpp"
#include "cjdb/range/concepts/refinements.hpp"
#include "cjdb/range/concepts/sized_range.hpp"
#include <utility>

namespace cjdb::ranges::detail_empty {
	template<typename T>
	concept member_empty = requires(T&& t) {
		{ (t).empty() } -> convertible_to<bool>;
	};

	template<typename T>
	concept sized_empty = not member_empty<T> and sized_range<T>;

	template<typename T>
	concept unsized_empty =
		not member_empty<T> and
		not sized_range<T> and
		forward_range<T> and
		sized_sentinel_for<sentinel_t<T>, iterator_t<T>>;

	template<typename T>
	inline constexpr auto is_nothrow = false;

	template<typename T>
	requires member_empty<T>
	inline constexpr auto is_nothrow<T> = noexcept(std::declval<T>().empty());

	template<sized_empty T>
	inline constexpr auto is_nothrow<T> = noexcept(ranges::size(std::declval<T>()));

	template<unsized_empty T>
	inline constexpr auto is_nothrow<T> = requires(T&& t) {
		{ ranges::begin(t) == ranges::end(t) } noexcept;
	};

	struct empty_fn {
		template<typename T>
		requires member_empty<T>
		[[nodiscard]] constexpr auto operator()(T&& t) noexcept(is_nothrow<T>) -> bool
		{
			return bool((t).empty());
		}

		template<typename T>
		requires sized_empty<T>
		[[nodiscard]] constexpr auto operator()(T&& t) noexcept(is_nothrow<T>) -> bool
		{
			return ranges::size(std::forward<T>(t)) == 0;
		}

		template<typename T>
		requires unsized_empty<T>
		[[nodiscard]] constexpr auto operator()(T&& t) noexcept(is_nothrow<T>) -> bool
		{
			return ranges::begin(t) == ranges::end(t);
		}

		template<typename T>
		auto operator()(T&& t) -> void = delete;
	};
} // namespace cjdb::ranges::detail_empty

namespace cjdb::ranges {
	inline constexpr auto empty = detail_empty::empty_fn{};
} // namespace cjdb::ranges

#endif // CJDB_DETAIL_RANGE_EMPTY_HPP
