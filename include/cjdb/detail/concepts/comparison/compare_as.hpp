// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_CONCEPTS_COMPARISON_COMPARE_AS_HPP
#define CJDB_DETAIL_CONCEPTS_COMPARISON_COMPARE_AS_HPP

#include <version>
#if defined(__cpp_lib_three_way_comparison) and __cpp_lib_three_way_comparison >= 201907

#include "cjdb/concepts/core/same_as.hpp"
#include <compare>

namespace cjdb::detail_compares_as {
	template<class T, class Cat>
	concept compares_as = same_as<std::common_comparison_category_t<T, Cat>, Cat>;
} // namespace cjdb::detail_compare_as

#endif // defined(__cpp_lib_three_way_comparison)
#endif // CJDB_DETAIL_CONCEPTS_COMPARISON_COMPARE_AS_HPP
