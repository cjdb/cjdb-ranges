// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_CALLABLE_INVOCABLE_HPP
#define CJDB_CONCEPTS_CALLABLE_INVOCABLE_HPP

#include "cjdb/functional/invoke.hpp"
#include <utility>

namespace cjdb {
	/// \brief The `invocable` concept specifies a relationship between a callable type `F` and a set
	///        of argument types `Args...` which can be evaluated by the library function `invoke`.
	/// \note  A function that generates random numbers can satisfy `invocable`, since the `invoke`
	///        function call expression is not required to be equality-preserving.
	/// \see [concept.invocable]
	///
	template<class F, class... Args>
	concept invocable = requires(F&& f, Args&&... args) {
		invoke(std::forward<F>(f), std::forward<Args>(args)...); // not required to be equality-preserving
	};
} // namespace cjdb

#endif // CJDB_CONCEPTS_CALLABLE_INVOCABLE_HPP
