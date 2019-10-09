// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_ITERATOR_DETAIL_ITERATOR_TRAITS_HPP
#define CJDB_ITERATOR_DETAIL_ITERATOR_TRAITS_HPP

#include "cjdb/detail/iterator/legacy_iterator.hpp"
#include "cjdb/detail/type_traits/primary_template.hpp"
#include <iterator>

namespace cjdb::detail_iterator_associated_types {
	template<typename I>
	struct extract_pointer_member {
		using type = void;
	};

	template<typename I>
	concept has_pointer_member = requires { typename I::pointer; };

	template<has_pointer_member I>
	struct extract_pointer_member<I> {
		using type = typename I::pointer;
	};

	template<typename I>
	concept has_arrow =
		detail_iterator_associated_types::legacy_input_iterator<I> and
		(not has_pointer_member<I>) and
		requires(I& i) {
			i.operator->();
		};

	template<has_arrow I>
	struct extract_pointer_member<I> {
		using type = decltype(std::declval<I&>().operator->());
	};

	template<typename I>
	concept has_reference_member = requires { typename I::reference; };

	template<typename I>
	struct extract_reference_member {
		using type = iter_reference_t<I>;
	};

	template<has_reference_member I>
	struct extract_reference_member<I> {
		using type = typename I::reference;
	};

	template<typename I>
	struct deduce_iterator_category {
		using type = std::input_iterator_tag;
	};

	template<detail_iterator_associated_types::legacy_forward_iterator I>
	struct deduce_iterator_category<I> {
		using type = std::forward_iterator_tag;
	};

	template<detail_iterator_associated_types::legacy_bidirectional_iterator I>
	struct deduce_iterator_category<I> {
		using type = std::bidirectional_iterator_tag;
	};

	template<detail_iterator_associated_types::legacy_random_access_iterator I>
	struct deduce_iterator_category<I> {
		using type = std::random_access_iterator_tag;
	};

	template<typename I>
	struct extract_iterator_category_member : deduce_iterator_category<I> {};

	template<typename I>
	concept has_iterator_category_member = requires { typename I::iterator_category; };

	template<has_iterator_category_member I>
	struct extract_iterator_category_member<I> {
		using type = typename I::iterator_category;
	};

	template<typename I>
	concept specifies_members =
		not cjdb::detail_iterator_associated_types::legacy_iterator<I> and
		has_reference_member<I> and
		has_iterator_category_member<I> and
		requires {
			typename I::difference_type;
			typename I::value_type;
		};

	template<typename I>
	inline constexpr auto valid_incrementable_traits = requires {
		typename incrementable_traits<I>::difference_type;
	};

	template<typename>
	struct extract_difference_type {
		using type = void;
	};

	template<typename I>
	requires valid_incrementable_traits<I>
	struct extract_difference_type<I> {
		using type = typename incrementable_traits<I>::difference_type;
	};

	template<typename>
	struct iterator_traits : private detail_primary_template::primary_template {};

	template<specifies_members I>
	struct iterator_traits<I> : private detail_primary_template::primary_template {
		using iterator_category = typename I::iterator_category;
		using value_type        = typename I::value_type;
		using difference_type   = typename I::difference_type;
		using pointer           = _t<extract_pointer_member<I>>;
		using reference         = typename I::reference;
	};

	template<detail_iterator_associated_types::legacy_iterator I>
	struct iterator_traits<I> : private detail_primary_template::primary_template {
		using iterator_category = std::output_iterator_tag;
		using value_type        = void;
		using difference_type   = _t<extract_difference_type<I>>;
		using pointer           = void;
		using reference         = void;
	};

	template<detail_iterator_associated_types::legacy_input_iterator I>
	struct iterator_traits<I> : private detail_primary_template::primary_template {
		using iterator_category = _t<extract_iterator_category_member<I>>;
		using value_type        = typename readable_traits<I>::value_type;
		using difference_type   = typename incrementable_traits<I>::difference_type;
		using pointer           = _t<extract_pointer_member<I>>;
		using reference         = _t<extract_reference_member<I>>;
	};

	struct contiguous_iterator_tag : std::random_access_iterator_tag {};

	template<class T>
	requires is_object_v<T>
	struct iterator_traits<T*> {
		using iterator_concept  = contiguous_iterator_tag;
		using iterator_category = std::random_access_iterator_tag;
		using value_type        = std::remove_cv_t<T>;
		using difference_type   = std::ptrdiff_t;
		using pointer           = T*;
		using reference         = T&;
	};
} // namespace cjdb::detail_iterator_associated_types

namespace cjdb {
	using cjdb::detail_iterator_associated_types::contiguous_iterator_tag;
	using cjdb::detail_iterator_associated_types::iterator_traits;
} // namespace cjdb

#endif // CJDB_ITERATOR_DETAIL_ITERATOR_TRAITS_HPP
