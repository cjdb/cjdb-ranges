// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_CORE_INTEGRAL_HPP
#define CJDB_CONCEPTS_CORE_INTEGRAL_HPP

#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb {
	/// \see [concepts.integral]
	///
	template<class T>
	concept integral = is_integral_v<T>;

	/// \see [concepts.integral]
	/// \note signed_integral<T> can be satisfied even by types that are not signed integral types
	///       (6.7.1); for example, char.
	///
	template<class T>
	concept signed_integral = integral<T> and is_signed_v<T>;

	/// \see [concepts.integral]
	/// \note unsigned_integral<T> can be satisfied even by types that are not unsigned integral types
	///       (6.7.1); for example, bool.
	///
	template<class T>
	concept unsigned_integral = integral<T> and !signed_integral<T>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_INTEGRAL_HPP
