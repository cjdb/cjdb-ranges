// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_ITERATOR_INCREMENTABLE_TRAITS_HPP
#define CJDB_ITERATOR_INCREMENTABLE_TRAITS_HPP

#include "cjdb/concepts/core/integral.hpp"
#include "cjdb/detail/iterator/incrementable_traits.hpp"
#include "cjdb/type_traits/type_traits.hpp"
#include <utility>

namespace cjdb {
	// [incrementable.traits]
	template<typename>
	struct incrementable_traits {};

	template<typename T>
	requires is_object_v<T>
	struct incrementable_traits<T*> {
		using difference_type = std::ptrdiff_t;
	};

	template<typename I>
	struct incrementable_traits<I const> : incrementable_traits<I> {};

	template<detail_incrementable_traits::has_difference_type T>
	struct incrementable_traits<T> {
		using difference_type = typename T::difference_type;
	};

	template<detail_incrementable_traits::has_integral_minus T>
	struct incrementable_traits<T> {
		using difference_type = make_signed_t<decltype(std::declval<T>() - std::declval<T>())>;
	};

	template<typename T>
	using iter_difference_t = _t<detail_incrementable_traits::extract_incrementable_traits<T>>;
} // namespace cjdb

#endif // CJDB_ITERATOR_INCREMENTABLE_TRAITS_HPP
