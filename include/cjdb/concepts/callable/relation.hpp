// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_CALLABLE_RELATION_HPP
#define CJDB_CONCEPTS_CALLABLE_RELATION_HPP

#include "cjdb/concepts/core/common_reference_with.hpp"
#include "cjdb/concepts/callable/predicate.hpp"
#include "cjdb/type_traits/common_reference.hpp"
#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb {
	/// \see [concept.relation]
	///
	template<class R, class T, class U>
	concept relation =
		predicate<R, T, T> and
		predicate<R, U, U> and
		predicate<R, T, U> and
		predicate<R, U, T>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_CALLABLE_RELATION_HPP
