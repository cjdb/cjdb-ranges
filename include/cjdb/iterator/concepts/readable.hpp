// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_ITERATOR_CONCEPTS_READABLE_HPP
#define CJDB_ITERATOR_CONCEPTS_READABLE_HPP

#include "cjdb/concepts/core/common_reference_with.hpp"
#include "cjdb/detail/iterator/readable_traits.hpp"
#include "cjdb/detail/iterator/iterator_traits.hpp"
#include "cjdb/type_traits/common_reference.hpp"

namespace cjdb {
	template<typename In>
	concept readable =
		requires {
			typename iter_value_t<In>;
			typename iter_reference_t<In>;
			typename iter_rvalue_reference_t<In>;
		} and
		common_reference_with<iter_reference_t<In>&&, iter_value_t<In>&> and
		common_reference_with<iter_reference_t<In>&&, iter_rvalue_reference_t<In>&&> and
		common_reference_with<iter_rvalue_reference_t<In>&&, iter_value_t<In> const&>;
		// axiom(In const& ci) {
		//    {  *i } -> equality_preserving;
		//    { *ci } -> equality_preserving;
		// }

	template<readable T>
	using iter_common_reference_t = common_reference_t<iter_reference_t<T>, iter_value_t<T>&>;
} // namespace cjdb

#endif // CJDB_ITERATOR_CONCEPTS_READABLE_HPP
