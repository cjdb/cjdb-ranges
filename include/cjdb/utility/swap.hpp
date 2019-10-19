// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_UTILITY_SWAP_HPP
#define CJDB_UTILITY_SWAP_HPP

#include "cjdb/detail/utility/swap.hpp"

namespace cjdb::ranges {
	inline constexpr auto swap = detail_swap::swap_fn{};
} // namespace cjdb::ranges

#endif // CJDB_UTILITY_SWAP_HPP
