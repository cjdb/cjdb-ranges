// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-.0 WITH LLVM-exception
//
#ifndef CJDB_RANGE_CONCEPTS_REFINEMENTS_HPP
#define CJDB_RANGE_CONCEPTS_REFINEMENTS_HPP

#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/iterator/concepts/iterator.hpp"
#include "cjdb/range/access/data.hpp"
#include "cjdb/range/associated_types.hpp"
#include "cjdb/range/concepts/range.hpp"

namespace cjdb::ranges {
	template<typename R, typename T>
	concept output_range = range<R> and output_iterator<iterator_t<R>, T>;

	template<typename T>
	concept input_range = range<T> and input_iterator<iterator_t<T>>;

	template<typename T>
	concept forward_range = input_range<T> and forward_iterator<iterator_t<T>>;

	template<typename T>
	concept bidirectional_range = forward_range<T> and bidirectional_iterator<iterator_t<T>>;

	template<typename T>
	concept random_access_range = bidirectional_range<T> and random_access_iterator<iterator_t<T>>;

	template<typename T>
	concept contiguous_range =
		random_access_range<T> and
		contiguous_iterator<iterator_t<T>> and
		requires(T& t) {
			{ ranges::data(t) } -> same_as<std::add_pointer_t<range_reference_t<T>>>;
		};

	template<typename T>
	concept common_range = range<T> and same_as<iterator_t<T>, sentinel_t<T>>;
} // namespace cjdb::ranges

#endif // CJDB_RANGE_CONCEPTS_REFINEMENTS_HPP
