// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_ITERATOR_ITER_TRAITS_HPP
#define CJDB_DETAIL_ITERATOR_ITER_TRAITS_HPP

#include "cjdb/detail/iterator/iterator_traits.hpp"
#include "cjdb/type_traits/is_primary.hpp"

namespace cjdb::ranges::detail_iter_traits {
	template<typename I>
	struct iter_traits : iterator_traits<I> {};

	template<typename I>
	requires is_primary<iterator_traits<I>>
	struct iter_traits<I> : I {};

	template<typename I>
	struct iter_traits<I* volatile> {};

	template<typename I>
	concept has_iterator_concept_member =
		requires { typename iter_traits<I>::iterator_concept; };

	template<typename I>
	concept has_iterator_category_member =
		not has_iterator_concept_member<I> and
		requires { typename iter_traits<I>::iterator_category; };

	template<typename I>
	concept iter_concept_fallback =
		is_primary<iterator_traits<I>> and
		not has_iterator_concept_member<I> and
		not has_iterator_category_member<I>;

	template<typename I>
	struct iter_concept {};

	template<has_iterator_concept_member I>
	struct iter_concept<I> {
		using type = typename iter_traits<I>::iterator_concept;
	};

	template<has_iterator_category_member I>
	struct iter_concept<I> {
		using type = typename iter_traits<I>::iterator_category;
	};

	template<iter_concept_fallback I>
	struct iter_concept<I> {
		using type = std::random_access_iterator_tag;
	};

	template<typename I>
	using iter_concept_t = _t<iter_concept<I>>;
} // namespace cjdb::ranges::detail_iter_traits

namespace cjdb::detail_iter_traits {
	using namespace cjdb::ranges::detail_iter_traits;
} // namespace cjdb::detail_iter_traits

#endif // CJDB_DETAIL_ITERATOR_ITER_TRAITS_HPP
