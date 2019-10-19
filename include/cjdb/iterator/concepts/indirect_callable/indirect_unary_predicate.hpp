// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_ITERATOR_CONCEPTS_INDIRECT_CALLABLE_INDIRECT_UNARY_PREDICATE_HPP
#define CJDB_ITERATOR_CONCEPTS_INDIRECT_CALLABLE_INDIRECT_UNARY_PREDICATE_HPP

#include "cjdb/concepts/callable/predicate.hpp"
#include "cjdb/concepts/core/copy_constructible.hpp"
#include "cjdb/detail/iterator/readable_traits.hpp"
#include "cjdb/iterator/concepts/readable.hpp"
#include "cjdb/iterator/reference.hpp"

namespace cjdb {
	template<typename F, typename I>
	concept indirect_unary_predicate =
		readable<I> and
		copy_constructible<F> and
		predicate<F&, iter_value_t<I>&> and
		predicate<F&, iter_reference_t<I>> and
		predicate<F&, iter_common_reference_t<I>>;
} // namespace cjdb

#endif // CJDB_ITERATOR_CONCEPTS_INDIRECT_CALLABLE_INDIRECT_UNARY_PREDICATE_HPP
