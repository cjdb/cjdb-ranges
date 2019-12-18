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

namespace cjdb::ranges {
	/// \brief Retrieves a range's iterator type.
	///
	template<range R>
	using iterator_t = decltype(ranges::begin(std::declval<R&>()));

	/// \brief Retrieves a range's sentinel type for the range's iterator type.
	///
	template<range R>
	using sentinel_t = decltype(ranges::end(std::declval<R&>()));

	/// \brief Retrieves the distance-type for a range's iterator.
	/// \note This could be different to any `difference_type` member-alias that R may have.
	///
	template<range R>
	using range_difference_t = iter_difference_t<iterator_t<R>>;

	/// \brief Retrieves the size-type for a range's iterator.
	/// \note This could be different to any `size_type` member-alias that R may have.
	/// \note This is an extension.
	///
	// template<sized_range R>
	// using range_size_t = decltype(ranges::size(std::declval<R&>()));

	/// \brief Retrieves the value-type for a range's iterator.
	/// \note This could be different to any `value_type` member-alias that R may have.
	///
	template<range R>
	using range_value_t = iter_value_t<iterator_t<R>>;

	/// \brief Retrieves the reference-type for a range's iterator.
	/// \note This could be different to `range_value_t<R>&`.
	/// \note This could be different to any `reference` member-alias that R may have.
	///
	template<range R>
	using range_reference_t = iter_reference_t<iterator_t<R>>;

	/// \brief Retrieves the reference-type for a range's iterator.
	/// \note This could be different to `range_value_t<R>&&`.
	/// \note This could be different to any `rvalue_reference` member-alias that R may have.
	///
	template<range R>
	using range_rvalue_reference_t = iter_rvalue_reference_t<iterator_t<R>>;
} // namespace cjdb::ranges

#endif // CJDB_RANGE_ASSOCIATED_TYPES_HPP
