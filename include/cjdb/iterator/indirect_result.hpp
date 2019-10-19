// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_ITERATOR_CONCEPTS_INDIRECT_RESULT_HPP
#define CJDB_ITERATOR_CONCEPTS_INDIRECT_RESULT_HPP

#include "cjdb/concepts/callable/invocable.hpp"
#include "cjdb/iterator/concepts/readable.hpp"
#include "cjdb/iterator/reference.hpp"

namespace cjdb {
	template<typename F, typename... Is>
	requires (readable<Is> and ...) and invocable<F, iter_reference_t<Is>...>
	using indirect_result_t = invoke_result_t<F, iter_reference_t<Is>...>;
} // namespace cjdb

#endif // CJDB_ITERATOR_CONCEPTS_INDIRECT_RESULT_HPP
