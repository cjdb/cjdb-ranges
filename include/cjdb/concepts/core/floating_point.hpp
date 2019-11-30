// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_CORE_FLOATING_POINT_HPP
#define CJDB_CONCEPTS_CORE_FLOATING_POINT_HPP

#include <type_traits>

namespace cjdb {
	template<typename T>
	concept floating_point = std::is_floating_point_v<T>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_FLOATING_POINT_HPP
