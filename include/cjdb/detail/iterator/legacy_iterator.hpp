// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_ITERATOR_LEGACY_ITERATOR_HPP
#define CJDB_DETAIL_ITERATOR_LEGACY_ITERATOR_HPP

#include "cjdb/concepts/comparison/equality_comparable.hpp"
#include "cjdb/concepts/comparison/totally_ordered.hpp"
#include "cjdb/concepts/core/constructible_from.hpp"
#include "cjdb/concepts/core/convertible_to.hpp"
#include "cjdb/concepts/core/integral.hpp"
#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/concepts/object/copyable.hpp"
#include "cjdb/detail/iterator/reference.hpp"
#include "cjdb/iterator/reference.hpp"
#include "cjdb/type_traits/common_reference.hpp"

namespace cjdb::detail_iterator_associated_types {
	template<typename> struct incrementable_traits;
	template<typename> struct readable_traits;

	template<class I>
	concept legacy_iterator =
		copyable<I> and
		requires(I i) {
			{   *i } -> detail_iterator_reference::can_reference;
			{  ++i } -> same_as<I&>;
			{ *i++ } -> detail_iterator_reference::can_reference;
		};

	template<class I>
	concept legacy_input_iterator =
		legacy_iterator<I>
		and equality_comparable<I>
		and requires(I i) {
			typename incrementable_traits<I>::difference_type;
			typename readable_traits<I>::value_type;
			typename common_reference_t<iter_reference_t<I>&&,
			                            typename readable_traits<I>::value_type&>;
			typename common_reference_t<decltype(*i++)&&,
			                            typename readable_traits<I>::value_type&>;
			requires signed_integral<typename incrementable_traits<I>::difference_type>;
		};

	template<class I>
	concept legacy_forward_iterator =
		legacy_input_iterator<I> and
		constructible_from<I> and
		is_lvalue_reference_v<iter_reference_t<I>> and
		same_as<remove_cvref_t<iter_reference_t<I>>, typename readable_traits<I>::value_type> and
		requires(I i) {
			{  i++ } -> convertible_to<I const&>;
			{ *i++ } -> same_as<iter_reference_t<I>>;
		};

	template<class I>
	concept legacy_bidirectional_iterator =
		legacy_forward_iterator<I> and
		requires(I i) {
			{  --i } -> same_as<I&>;
			{  i-- } -> convertible_to<I const&>;
			{ *i-- } -> same_as<iter_reference_t<I>>;
		};

	template<class I>
	concept legacy_random_access_iterator =
		legacy_bidirectional_iterator<I> and
		totally_ordered<I> and
		requires(I i, I j, typename incrementable_traits<I>::difference_type n) {
			{ i += n } -> same_as<I&>;
			{ i -= n } -> same_as<I&>;
			{ i +  n } -> same_as<I>;
			{ n +  i } -> same_as<I>;
			{ i -  n } -> same_as<I>;
			{ i -  j } -> same_as<decltype(n)>;
			{  i[n]  } -> convertible_to<iter_reference_t<I>>;
		};
} // namespace cjdb::detail_iterator_associated_types

#endif // CJDB_DETAIL_ITERATOR_LEGACY_ITERATOR_HPP
