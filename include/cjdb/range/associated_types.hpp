// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-.0 WITH LLVM-exception
//
#ifndef CJDB_RANGE_ASSOCIATED_TYPES_HPP
#define CJDB_RANGE_ASSOCIATED_TYPES_HPP

#include "cjdb/iterator/associated_types.hpp"
#include "cjdb/iterator/reference.hpp"
#include "cjdb/range/access/begin.hpp"
#include "cjdb/range/access/end.hpp"
#include "cjdb/range/concepts/range.hpp"
#include <utility>

namespace cjdb {
	template<range R>
	using iterator_t = decltype(ranges::begin(std::declval<R&>()));

	template<range R>
	using sentinel_t = decltype(ranges::end(std::declval<R&>()));

	template<range R>
	using range_difference_t = iter_difference_t<iterator_t<R>>;

	template<range R>
	using range_value_t = iter_value_t<iterator_t<R>>;

	template<range R>
	using range_reference_t = iter_reference_t<iterator_t<R>>;

	template<range R>
	using range_rvalue_reference_t = iter_rvalue_reference_t<iterator_t<R>>;
} // namespace cjdb

#endif // CJDB_RANGE_ASSOCIATED_TYPES_HPP
