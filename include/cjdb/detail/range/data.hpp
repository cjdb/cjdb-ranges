// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_RANGE_DATA_HPP
#define CJDB_DETAIL_RANGE_DATA_HPP

#include "cjdb/detail/decay_copy.hpp"
#include "cjdb/iterator/concepts/iterator.hpp"
#include "cjdb/range/access/begin.hpp"
#include <memory>
#include <type_traits>

#include "cjdb/detail/define.hpp"

namespace cjdb::ranges::detail_data {
	template<typename T>
	concept pointer = std::is_pointer_v<T>;

	template<typename T>
	concept object_pointer = pointer<T> and std::is_object_v<std::remove_pointer_t<T>>;

	template<typename T>
	concept member_data =
		requires(T& t) {
			t.data();
			{ detail_decay_copy::decay_copy(t.data()) } -> object_pointer;
		};

	template<typename T>
	concept unqualified_data =
		not member_data<std::remove_reference_t<T>> and
		requires(T&& t) {
			{ ranges::begin(std::forward<T>(t)) } -> contiguous_iterator;
		};

	struct data_fn {
		template<typename T>
		requires member_data<T>
		[[nodiscard]] constexpr auto operator()(T& t) const
		CJDB_NOEXCEPT_RETURN(
			detail_decay_copy::decay_copy(t.data())
		)

		template<typename T>
		requires unqualified_data<T>
		[[nodiscard]] constexpr auto operator()(T&& t) const
		CJDB_NOEXCEPT_RETURN(
			std::to_address(ranges::begin(std::forward<T>(t)))
		)

		template<typename T>
		constexpr void operator()(T&&) const = delete;
	};
} // namespace cjdb::ranges::detail_data

namespace cjdb::ranges {
	inline constexpr auto data = detail_data::data_fn{};
} // namespace cjdb::ranges

#include "cjdb/detail/undef.hpp"

#endif // CJDB_DETAIL_RANGE_DATA_HPP
