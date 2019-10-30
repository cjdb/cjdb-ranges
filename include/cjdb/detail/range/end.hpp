// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_RANGE_END_HPP
#define CJDB_DETAIL_RANGE_END_HPP

#include "cjdb/concepts/callable/invocable.hpp"
#include "cjdb/detail/concepts/core/reference.hpp"
#include "cjdb/detail/decay_copy.hpp"
#include "cjdb/detail/range/begin.hpp"
#include "cjdb/iterator/concepts/iterator.hpp"
#include <cstddef>
#include <initializer_list>
#include <type_traits>
#include <utility>

#include "cjdb/detail/define.hpp"

namespace cjdb::ranges::detail_end {
	template<typename T>
	concept member_end =
		requires(T& t) {
			cjdb::ranges::begin(t);
			t.end();
			{ detail_decay_copy::decay_copy(t.end()) } -> sentinel_for<decltype(begin(t))>;
		};

	template<class T>
	void end(T&&) = delete;
	template<class T>
	void end(std::initializer_list<T>&&) = delete;

	template<typename T>
	concept unqualified_end =
		not member_end<T> and
		requires(T&& t) {
			cjdb::ranges::begin(std::forward<T>(t));
			end(std::forward<T>(t));
			{ detail_decay_copy::decay_copy(end(std::forward<T>(t))) } -> sentinel_for<decltype(end(std::forward<T>(t)))>;
		};

	struct end_fn {
		template<typename T, std::size_t N>
		[[nodiscard]] constexpr auto operator()(T(& t)[N]) const noexcept // NOLINT(modernize-avoid-c-arrays)
		{
			return t + std::extent_v<T[N]>; // NOLINT(modernize-avoid-c-arrays)
		}

		template<typename T>
		requires member_end<T>
		[[nodiscard]] constexpr auto operator()(T& t) const
		CJDB_NOEXCEPT_RETURN(
			detail_decay_copy::decay_copy(t.end())
		)

		template<typename T>
		requires unqualified_end<T>
		[[nodiscard]] constexpr auto operator()(T&& t) const
		CJDB_NOEXCEPT_RETURN(
			detail_decay_copy::decay_copy(end(std::forward<T>(t)))
		)
	};
} // namespace cjdb::ranges::detail_end

#include "cjdb/detail/undef.hpp"

namespace cjdb::ranges {
	inline constexpr auto end = detail_end::end_fn{};
} // namespace cjdb::ranges

#endif // CJDB_DETAIL_RANGE_END_HPP
