// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_PSEUDOALGORITHM_HPP
#define CJDB_TEST_PSEUDOALGORITHM_HPP

#include "cjdb/detail/iterator/iter_swap.hpp"
#include "cjdb/iterator/concepts/indirectly_swappable.hpp"

namespace cjdb_test {
	/// \brief A quick-and-dirty implementation of swap_ranges to facilitate the testing of
	///       iter_swap.
	/// \note Because ranges::swap_ranges is implemented using iter_swap, we can't replace this with
	///       the actual swap_ranges implementation.
	///
	auto swap_ranges = [](auto&& r1, auto&& r2) {
		auto first1 = begin(r1);
		auto first2 = begin(r2);
		for (; first1 != begin(r1) and first2 != end(r2); (void)++first1, (void)++first2) {
			cjdb::ranges::iter_swap(first1, first2);
		}
	};
} // namespace cjdb_test

#endif // CJDB_TEST_PSEUDOALGORITHM_HPP
