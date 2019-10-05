// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_CORE_SAME_HPP
#define CJDB_CONCEPTS_CORE_SAME_HPP

#include "cjdb/detail/concepts/core/is_same.hpp"

namespace cjdb {
	/// \brief Checks if two types are exactly the same (including cv-qualifiers and ref-qualifiers).
	/// \note `same_as<T, U>` subsumes `same_as<U, T>` and vice versa.
	/// \see [concept.same]
	///
	template<class T, class U>
	concept same_as = detail_same::is_same<T, U> and detail_same::is_same<U, T>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_SAME_HPP
