// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_CONCEPTS_CORE_REFERENCE_HPP
#define CJDB_DETAIL_CONCEPTS_CORE_REFERENCE_HPP

#include <type_traits>

namespace cjdb::detail_reference_concepts {
	template<typename T>
	concept reference = std::is_reference_v<T>;

	template<typename T>
	concept lvalue_reference = reference<T> and std::is_lvalue_reference_v<T>;

	template<typename T>
	concept rvalue_reference = reference<T> and not lvalue_reference<T>;
} // namespace cjdb::detail_reference_concepts

#endif // CJDB_DETAIL_CONCEPTS_CORE_REFERENCE_HPP
