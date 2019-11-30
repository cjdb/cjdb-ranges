// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_CORE_SIGNED_INTEGRAL_HPP
#define CJDB_CONCEPTS_CORE_SIGNED_INTEGRAL_HPP

#include "cjdb/concepts/core/integral.hpp"
#include <type_traits>

namespace cjdb {
	/// \see [concepts.integral]
	/// \note signed_integral<T> can be satisfied even by types that are not signed integral types
	///       (6.7.1); for example, char.
	///
	template<class T>
	concept signed_integral = integral<T> and std::is_signed_v<T>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_SIGNED_INTEGRAL_HPP
