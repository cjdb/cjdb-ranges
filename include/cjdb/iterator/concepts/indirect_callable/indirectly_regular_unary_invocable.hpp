// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_ITERATOR_CONCEPTS_INDIRECT_CALLABLE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_HPP
#define CJDB_ITERATOR_CONCEPTS_INDIRECT_CALLABLE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_HPP

#include "cjdb/concepts/core/common_reference_with.hpp"
#include "cjdb/concepts/core/copy_constructible.hpp"
#include "cjdb/concepts/callable/regular_invocable.hpp"
#include "cjdb/detail/iterator/readable_traits.hpp"
#include "cjdb/iterator/concepts/readable.hpp"
#include "cjdb/iterator/reference.hpp"

namespace cjdb {
	template<typename F, typename I>
	concept indirectly_regular_unary_invocable =
		readable<I> and
		copy_constructible<F> and
		regular_invocable<F&, iter_value_t<I>&> and
		regular_invocable<F&, iter_reference_t<I>> and
		regular_invocable<F&, iter_common_reference_t<I>> and
		common_reference_with<
			invoke_result_t<F&, iter_value_t<I>&>,
			invoke_result_t<F&, iter_reference_t<I>>
		>;
} // namespace cjdb

#endif // CJDB_ITERATOR_CONCEPTS_INDIRECT_CALLABLE_INDIRECTLY_REGULAR_UNARY_INVOCABLE_HPP
