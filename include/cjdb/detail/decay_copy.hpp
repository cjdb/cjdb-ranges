// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_DECAY_COPY_HPP
#define CJDB_DETAIL_DECAY_COPY_HPP

#include <type_traits>

namespace cjdb::detail_decay_copy {
	struct decay_copy_fn {
		template<typename T>
		constexpr std::decay_t<T> operator()(T&& v) const
		noexcept(std::is_nothrow_convertible_v<T, std::decay_t<T>>)
		{ return std::forward<T>(v); }
	};

	inline constexpr auto decay_copy = decay_copy_fn{};
} // namespace cjdb::detail_decay_copy

#endif // CJDB_DETAIL_DECAY_COPY_HPP
