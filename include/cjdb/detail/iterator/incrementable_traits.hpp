// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_ITERATOR_INCREMENTABLE_TRAITS_HPP
#define CJDB_DETAIL_ITERATOR_INCREMENTABLE_TRAITS_HPP

#include "cjdb/concepts/core/integral.hpp"
#include "cjdb/iterator/iterator_traits.hpp"
#include "cjdb/type_traits/is_primary.hpp"

namespace cjdb {
	template<typename> struct incrementable_traits;
} // namespace cjdb

namespace cjdb::detail_incrementable_traits {
	template<typename T>
	concept has_difference_type = requires { typename T::difference_type; };

	template<typename T>
	concept has_integral_minus =
		(not has_difference_type<T>) and
		requires(T const& a, T const& b) {
			{ a - b } -> integral;
		};

	template<typename I>
	struct extract_incrementable_traits {
		using type = typename iterator_traits<I>::difference_type;
	};

	template<typename I>
	requires is_primary<iterator_traits<I>>
	struct extract_incrementable_traits<I> {
		using type = typename incrementable_traits<I>::difference_type;
	};
} // namespace cjdb::detail_incrementable_traits

#endif // CJDB_DETAIL_ITERATOR_INCREMENTABLE_TRAITS
