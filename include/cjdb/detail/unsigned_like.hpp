// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_UNSIGNED_LIKE_HPP
#define CJDB_DETAIL_UNSIGNED_LIKE_HPP

#include "cjdb/concepts/core/integral.hpp"
#include <type_traits>

namespace cjdb::detail_unsigned_like {
	struct make_unsigned_like {
		template<integral T>
		constexpr auto operator()(T const t) const noexcept
		{
			using make_unsigned_like_t = std::make_unsigned_t<T>;
			return static_cast<make_unsigned_like_t>(t);
		}
	};
} // namespace cjdb::detail_unsigned_like

#endif // CJDB_DETAIL_UNSIGNED_LIKE_HPP
