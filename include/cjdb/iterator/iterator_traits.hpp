// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_ITERATOR_ITERATOR_TRAITS_HPP
#define CJDB_ITERATOR_ITERATOR_TRAITS_HPP

#include "cjdb/detail/iterator/iterator_traits.hpp"
#include "cjdb/detail/iterator/legacy_iterator.hpp"
#include "cjdb/detail/type_traits/primary_template.hpp"
#include <iterator>

namespace cjdb {
	template<typename>
	struct iterator_traits : private detail_primary_template::primary_template {};

	template<detail_iterator_traits::specifies_members I>
	struct iterator_traits<I> : private detail_primary_template::primary_template {
		using iterator_category = typename I::iterator_category;
		using value_type        = typename I::value_type;
		using difference_type   = typename I::difference_type;
		using pointer           = _t<detail_iterator_traits::extract_pointer_member<I>>;
		using reference         = typename I::reference;
	};

	template<detail_legacy_iterator::legacy_iterator I>
	struct iterator_traits<I> : private detail_primary_template::primary_template {
		using iterator_category = std::output_iterator_tag;
		using value_type        = void;
		using difference_type   = _t<detail_iterator_traits::extract_difference_type<I>>;
		using pointer           = void;
		using reference         = void;
	};

	template<detail_legacy_iterator::legacy_input_iterator I>
	struct iterator_traits<I> : private detail_primary_template::primary_template {
		using iterator_category = _t<detail_iterator_traits::extract_iterator_category_member<I>>;
		using value_type        = typename readable_traits<I>::value_type;
		using difference_type   = typename incrementable_traits<I>::difference_type;
		using pointer           = _t<detail_iterator_traits::extract_pointer_member<I>>;
		using reference         = _t<detail_iterator_traits::extract_reference_member<I>>;
	};

	struct contiguous_iterator_tag : std::random_access_iterator_tag {};

	template<class T>
	requires is_object_v<T>
	struct iterator_traits<T*> {
		using iterator_concept  = contiguous_iterator_tag;
		using iterator_category = std::random_access_iterator_tag;
		using value_type        = remove_cv_t<T>;
		using difference_type   = std::ptrdiff_t;
		using pointer           = T*;
		using reference         = T&;
	};
} // namespace cjdb

#endif // CJDB_ITERATOR_ITERATOR_TRAITS_HPP
