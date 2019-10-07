// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_ITERATOR_DETAIL_ITERATOR_TRAITS_HPP
#define CJDB_ITERATOR_DETAIL_ITERATOR_TRAITS_HPP

#include "cjdb/detail/iterator/legacy_iterator.hpp"
#include <iterator>

namespace cjdb {
	template<typename> struct incrementable_traits;
	template<typename> struct readable_traits;
} // namespace cjdb

namespace cjdb::detail_iterator_traits {
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
		detail_legacy_iterator::legacy_input_iterator<I> and
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

	template<detail_legacy_iterator::legacy_forward_iterator I>
	struct deduce_iterator_category<I> {
		using type = std::forward_iterator_tag;
	};

	template<detail_legacy_iterator::legacy_bidirectional_iterator I>
	struct deduce_iterator_category<I> {
		using type = std::bidirectional_iterator_tag;
	};

	template<detail_legacy_iterator::legacy_random_access_iterator I>
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
		not detail_legacy_iterator::legacy_iterator<I> and
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
} // namespace cjdb::detail_iterator_traits

#endif // CJDB_ITERATOR_DETAIL_ITERATOR_TRAITS_HPP
