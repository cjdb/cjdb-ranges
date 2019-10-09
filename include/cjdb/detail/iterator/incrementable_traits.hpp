// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_ITERATOR_INCREMENTABLE_TRAITS_HPP
#define CJDB_DETAIL_ITERATOR_INCREMENTABLE_TRAITS_HPP

#include "cjdb/concepts/core/integral.hpp"
#include "cjdb/detail/iterator/iterator_traits.hpp"
#include "cjdb/type_traits/is_primary.hpp"
#include <type_traits>
#include <utility>

namespace cjdb::detail_iterator_associated_types {
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

	template<typename>
	struct incrementable_traits {};

	template<typename T>
	requires is_object_v<T>
	struct incrementable_traits<T*> {
		using difference_type = std::ptrdiff_t;
	};

	template<typename I>
	struct incrementable_traits<I const> : incrementable_traits<I> {};

	template<has_difference_type T>
	struct incrementable_traits<T> {
		using difference_type = typename T::difference_type;
	};

	template<has_integral_minus T>
	struct incrementable_traits<T> {
		using difference_type = std::make_signed_t<decltype(std::declval<T>() - std::declval<T>())>;
	};

	template<typename T>
	using iter_difference_t = _t<extract_incrementable_traits<T>>;
} // namespace cjdb::detail_iterator_associated_types

namespace cjdb {
	using cjdb::detail_iterator_associated_types::incrementable_traits;
	using cjdb::detail_iterator_associated_types::iter_difference_t;
} // namespace cjdb

#endif // CJDB_DETAIL_ITERATOR_INCREMENTABLE_TRAITS
