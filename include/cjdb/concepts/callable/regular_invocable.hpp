// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_CALLABLE_REGULARINVOCABLE_HPP
#define CJDB_CONCEPTS_CALLABLE_REGULARINVOCABLE_HPP

#include "cjdb/concepts/callable/invocable.hpp"

namespace cjdb {
	/// \brief The `invoke` function call expression shall be equality-preserving and shall not
	///        modify the function object or the arguments.
	/// \note This requirement supersedes the annotation in the definition of `invocable`.
	/// \note A random number generator does not satisfy `regular_invocable`.
	/// \note The distinction between `invocable` and `regular_invocable` is purely semantic.
	/// \see [concept.regularinvocable]
	///
	template<class F, class... Args>
	concept regular_invocable = invocable<F, Args...>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_CALLABLE_REGULARINVOCABLE_HPP
