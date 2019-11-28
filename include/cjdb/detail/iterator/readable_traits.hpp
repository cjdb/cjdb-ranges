// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_ITERATOR_READABLE_TRAITS_HPP
#define CJDB_DETAIL_ITERATOR_READABLE_TRAITS_HPP

#include "cjdb/detail/iterator/iterator_traits.hpp"
#include "cjdb/type_traits/is_primary.hpp"
#include <type_traits>

namespace cjdb::detail_iterator_associated_types {
	template<typename> struct cond_value_type {};

	template<typename T>
	requires is_object_v<T>
	struct cond_value_type<T> {
		using value_type = std::remove_cv_t<T>;
	};

	template<typename T>
	concept has_value_type = requires { typename T::value_type; };

	template<typename T>
	concept has_element_type = requires { typename T::element_type; };

	template<typename I>
	struct extract_readable_traits {};

	template<typename I>
	requires (has_value_type<iterator_traits<I>> and not is_primary<iterator_traits<I>>)
	struct extract_readable_traits<I> {
		using type = typename iterator_traits<I>::value_type;
	};

	template<typename I>
	requires is_primary<iterator_traits<I>> and has_value_type<readable_traits<I>>
	struct extract_readable_traits<I> {
		using type = typename readable_traits<I>::value_type;
	};

	template<typename> struct readable_traits {};

	template<typename T>
	struct readable_traits<T*> : cond_value_type<T> {};

	template<typename I>
	requires std::is_array_v<I>
	struct readable_traits<I> {
		using value_type = std::remove_cv_t<std::remove_extent_t<I>>;
	};

	template<typename I>
	struct readable_traits<I const> : readable_traits<I> {};

	template<has_value_type T>
	struct readable_traits<T> : cond_value_type<typename T::value_type> {};

	template<has_element_type T>
	struct readable_traits<T> : cond_value_type<typename T::element_type> {};

	template<has_value_type T>
	requires has_element_type<T>
	struct readable_traits<T> {};

	template<typename T>
	using iter_value_t = _t<extract_readable_traits<T>>;
} // namespace cjdb::detail_iterator_associated_types

namespace cjdb {
	using cjdb::detail_iterator_associated_types::readable_traits;
	using cjdb::detail_iterator_associated_types::iter_value_t;
} // namespace cjdb

#endif // CJDB_DETAIL_ITERATOR_READABLE_TRAITS_HPP
