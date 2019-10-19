// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_ITERATOR_CONCEPTS_INDIRECT_CALLABLE_INDIRECT_STRICT_WEAK_ORDER_HPP
#define CJDB_ITERATOR_CONCEPTS_INDIRECT_CALLABLE_INDIRECT_STRICT_WEAK_ORDER_HPP

#include "cjdb/concepts/callable/strict_weak_order.hpp"
#include "cjdb/concepts/core/common_reference_with.hpp"
#include "cjdb/concepts/core/copy_constructible.hpp"
#include "cjdb/detail/iterator/readable_traits.hpp"
#include "cjdb/iterator/concepts/readable.hpp"
#include "cjdb/iterator/reference.hpp"

namespace cjdb {
	template<typename F, typename I1, typename I2 = I1>
	concept indirect_strict_weak_order =
		readable<I1> and
		readable<I2> and
		copy_constructible<F> and
		strict_weak_order<F&, iter_value_t<I1>&, iter_value_t<I2>&> and
		strict_weak_order<F&, iter_value_t<I1>&, iter_reference_t<I2>> and
		strict_weak_order<F&, iter_reference_t<I1>, iter_value_t<I2>&> and
		strict_weak_order<F&, iter_reference_t<I1>, iter_reference_t<I2>> and
		strict_weak_order<F&, iter_common_reference_t<I1>, iter_common_reference_t<I2>>;
} // namespace cjdb

#endif // CJDB_ITERATOR_CONCEPTS_INDIRECT_CALLABLE_INDIRECT_STRICT_WEAK_ORDER_HPP
