// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_CONSTEXPR_CHECK
#define CJDB_TEST_CONSTEXPR_CHECK
#include <cjdb/test/simple_test.hpp>
#include <type_traits>

#define CJDB_CONSTEXPR_CHECK(...) {          \
	CHECK(std::bool_constant<__VA_ARGS__>{}); \
	CHECK(__VA_ARGS__);                       \
}

#endif // CJDB_TEST_CONSTEXPR_CHECK
