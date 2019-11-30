// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_CORE_INTEGRAL_HPP
#define CJDB_CONCEPTS_CORE_INTEGRAL_HPP

#include <type_traits>

namespace cjdb {
	/// \see [concepts.integral]
	///
	template<class T>
	concept integral = std::is_integral_v<T>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_INTEGRAL_HPP
