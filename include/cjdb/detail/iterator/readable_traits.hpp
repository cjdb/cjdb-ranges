// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_ITERATOR_READABLE_TRAITS_HPP
#define CJDB_DETAIL_ITERATOR_READABLE_TRAITS_HPP

#include "cjdb/iterator/iterator_traits.hpp"
#include "cjdb/type_traits/is_primary.hpp"
#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb {
	template<typename> struct readable_traits;
} // namespace cjdb

namespace cjdb::detail_readable_traits {
	template<typename> struct cond_value_type {};

	template<typename T>
	requires is_object_v<T>
	struct cond_value_type<T> {
		using value_type = remove_cv_t<T>;
	};

	template<typename T>
	concept has_value_type = requires { typename T::value_type; };

	template<typename T>
	concept has_element_type = requires { typename T::element_type; };

	template<typename I>
	struct extract_readable_traits {
		using type = typename iterator_traits<I>::value_type;
	};

	template<typename I>
	requires is_primary<iterator_traits<I>>
	struct extract_readable_traits<I> {
		using type = typename readable_traits<I>::value_type;
	};
} // namespace cjdb::detail_readable_traits

#endif // CJDB_DETAIL_ITERATOR_READABLE_TRAITS_HPP
