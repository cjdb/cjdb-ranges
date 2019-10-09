// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_ITERATOR_CONCEPTS_INTEGER_LIKE_HPP
#define CJDB_DETAIL_ITERATOR_CONCEPTS_INTEGER_LIKE_HPP

#include "cjdb/concepts/comparison/totally_ordered.hpp"
#include "cjdb/concepts/core/convertible_to.hpp"
#include "cjdb/concepts/core/constructible_from.hpp"
#include "cjdb/concepts/core/integral.hpp"
#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/concepts/object/regular.hpp"
#include <numeric>

namespace cjdb::detail_integer_like {
	template<typename T>
	inline constexpr bool is_integer_like = integral<T>;

	template<typename T>
	inline constexpr bool is_signed_integer_like = signed_integral<T>;

	template<typename T>
	inline constexpr bool is_unsigned_integer_like = unsigned_integral<T>;
} // namespace cjdb::detail_integer_like

#endif // CJDB_DETAIL_ITERATOR_CONCEPTS_INTEGER_LIKE_HPP
