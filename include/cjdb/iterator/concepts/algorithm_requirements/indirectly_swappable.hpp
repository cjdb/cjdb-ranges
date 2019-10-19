// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_ITERATOR_CONCEPTS_ALGORITHM_INDIRECTLY_SWAPPABLE_HPP
#define CJDB_ITERATOR_CONCEPTS_ALGORITHM_INDIRECTLY_SWAPPABLE_HPP

#include "cjdb/detail/iterator/iter_swap.hpp"
#include "cjdb/iterator/concepts/readable.hpp"

namespace cjdb {
	/// \brief The `indirectly_­swappable` concept specifies a swappable relationship between the
	///        values referenced by two `readable` types.
	///
	template<typename I1, typename I2 = I1>
	concept indirectly_swappable =
		readable<I1> and
		readable<I2> and
		requires(I1& i1, I2& i2) {
			ranges::iter_swap(i1, i1);
			ranges::iter_swap(i2, i2);
			ranges::iter_swap(i1, i2);
			ranges::iter_swap(i2, i1);
		};
} // namespace cjdb

#endif // CJDB_ITERATOR_CONCEPTS_ALGORITHM_INDIRECTLY_SWAPPABLE_HPP
