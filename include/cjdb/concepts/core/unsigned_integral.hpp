// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_CORE_UNSIGNED_INTEGRAL_HPP
#define CJDB_CONCEPTS_CORE_UNSIGNED_INTEGRAL_HPP

#include "cjdb/concepts/core/integral.hpp"
#include "cjdb/concepts/core/signed_integral.hpp"

namespace cjdb {
	/// \see [concepts.integral]
	/// \note unsigned_integral<T> can be satisfied even by types that are not unsigned integral types
	///       (6.7.1); for example, bool.
	///
	template<class T>
	concept unsigned_integral = integral<T> and not signed_integral<T>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_UNSIGNED_INTEGRAL_HPP
