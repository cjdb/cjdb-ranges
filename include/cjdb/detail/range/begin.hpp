// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_RANGE_BEGIN_HPP
#define CJDB_DETAIL_RANGE_BEGIN_HPP

#include "cjdb/detail/concepts/core/reference.hpp"
#include "cjdb/detail/decay_copy.hpp"
#include "cjdb/iterator/concepts/iterator.hpp"
#include <cstddef>
#include <initializer_list>
#include <type_traits>
#include <utility>

#include "cjdb/detail/define.hpp"

namespace cjdb::ranges::detail_begin {
	template<typename T>
	concept member_begin =
		requires(T& t) {
			t.begin();
			{ detail_decay_copy::decay_copy(t.begin()) } -> input_or_output_iterator;
		};

	template<typename T>
	void begin(T&&) = delete;

	template<typename T>
	void begin(std::initializer_list<T>&&) = delete;

	template<typename T>
	concept unqualified_begin =
		not member_begin<T> and
		requires(T&& t) {
			begin(std::forward<T>(t));
			{ detail_decay_copy::decay_copy(begin(std::forward<T>(t))) } -> input_or_output_iterator;
		};

	struct begin_fn {
		template<typename T, std::size_t N>
		[[nodiscard]] constexpr T* operator()(T(& e)[N]) const noexcept // NOLINT(modernize-avoid-c-arrays)
		{
			return e + 0;
		}

		template<typename T>
		requires member_begin<T>
		[[nodiscard]] constexpr auto operator()(T& t) const
		CJDB_NOEXCEPT_RETURN(
			detail_decay_copy::decay_copy(t.begin())
		)

		template<typename T>
		requires unqualified_begin<T>
		[[nodiscard]] constexpr auto operator()(T&& t) const
		CJDB_NOEXCEPT_RETURN(
			detail_decay_copy::decay_copy(begin(std::forward<T>(t)))
		)
	};
} // namespace cjdb::ranges::detail_begin

namespace cjdb::ranges {
	inline constexpr auto begin = detail_begin::begin_fn{};
} // namespace cjdb::ranges

#include "cjdb/detail/undef.hpp"

#endif // CJDB_DETAIL_RANGE_BEGIN_HPP
