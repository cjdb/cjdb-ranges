// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_ITERATOR_CONCEPTS_INDIRECTLY_READABLE_IMPL_HPP
#define CJDB_ITERATOR_CONCEPTS_INDIRECTLY_READABLE_IMPL_HPP

#include "cjdb/concepts/core/common_reference_with.hpp"
#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/detail/iterator/indirectly_readable_traits.hpp"
#include "cjdb/detail/iterator/iterator_traits.hpp"
#include "cjdb/detail/iterator/iter_move.hpp"

namespace cjdb::detail_indirectly_readable {
	template<typename In>
	concept indirectly_readable_impl =
		requires(In const in) {
			typename iter_value_t<In>;
			typename iter_reference_t<In>;
			typename iter_rvalue_reference_t<In>;
			{ *in } -> same_as<iter_reference_t<In>>;
			{ ranges::iter_move(in) } -> same_as<iter_rvalue_reference_t<In>>;
		} and
		common_reference_with<iter_reference_t<In>&&, iter_value_t<In>&> and
		common_reference_with<iter_reference_t<In>&&, iter_rvalue_reference_t<In>&&> and
		common_reference_with<iter_rvalue_reference_t<In>&&, iter_value_t<In> const&>;
} // namespace cjdb::detail_indirectly_readable

#endif // CJDB_ITERATOR_CONCEPTS_INDIRECTLY_READABLE_IMPL_HPP
