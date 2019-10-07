// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_ITERATOR_READABLE_TRAITS_HPP
#define CJDB_ITERATOR_READABLE_TRAITS_HPP

#include "cjdb/detail/iterator/readable_traits.hpp"
#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb {
	template<typename> struct readable_traits {};

	template<typename T>
	struct readable_traits<T*> : detail_readable_traits::cond_value_type<T> {};

	template<typename I>
	requires is_array_v<I>
	struct readable_traits<I> {
		using value_type = remove_cv_t<remove_extent_t<I>>;
	};

	template<typename I>
	struct readable_traits<I const> : readable_traits<I> {};

	template<detail_readable_traits::has_value_type T>
	struct readable_traits<T> : detail_readable_traits::cond_value_type<typename T::value_type> {};

	template<detail_readable_traits::has_element_type T>
	struct readable_traits<T> : detail_readable_traits::cond_value_type<typename T::element_type> {};

	template<typename T>
	using iter_value_t = _t<detail_readable_traits::extract_readable_traits<T>>;
} // namespace cjdb

#endif // CJDB_ITERATOR_READABLE_TRAITS_HPP
