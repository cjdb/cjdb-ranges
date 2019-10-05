// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_CALLABLE_PREDICATE_HPP
#define CJDB_CONCEPTS_CALLABLE_PREDICATE_HPP

#include "cjdb/concepts/core/convertible_to.hpp"
#include "cjdb/concepts/callable/regular_invocable.hpp"
#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb {
	/// \see [concept.predicate]
	///
	template<class F, class... Args>
	concept predicate =
		regular_invocable<F, Args...> and
		convertible_to<invoke_result_t<F, Args...>, bool>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_CALLABLE_PREDICATE_HPP
