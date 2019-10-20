// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_CONSTEXPR_CHECK
#define CJDB_TEST_CONSTEXPR_CHECK

#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/contracts.hpp"
#include "cjdb/test/simple_test.hpp"
#include <type_traits>

#define CJDB_CONSTEXPR_CHECK(...) {                            \
	static_assert(cjdb::same_as<decltype(__VA_ARGS__), bool>);  \
	if (std::is_constant_evaluated()) {                         \
		CJDB_ASSERT(__VA_ARGS__);                                \
	}                                                           \
	else {                                                      \
		CHECK(__VA_ARGS__);                                      \
	}                                                           \
}

#define CJDB_EVALUATE_TEST_CASE(CJDB_RUN_TEST) do {               \
	auto test_case = [](auto& test) {                              \
		test();                                                     \
		return 0;                                                   \
	};                                                             \
	[[maybe_unused]] constexpr auto x = test_case(CJDB_RUN_TEST);  \
	auto y = test_case(CJDB_RUN_TEST);                             \
	[[maybe_unused]] auto volatile* z = &y;                        \
} while (false)

#define CJDB_EVALUATE_TEST_CASE_N(CJDB_RUN_TEST, ...) do {                    \
	auto test_case = []<typename... Args>(auto& test, Args... args) {          \
		test(std::move(args)...);                                               \
		return 0;                                                               \
	};                                                                         \
	[[maybe_unused]] constexpr auto x = test_case(CJDB_RUN_TEST, __VA_ARGS__); \
	auto y = test_case(CJDB_RUN_TEST, __VA_ARGS__);                            \
	[[maybe_unused]] auto volatile* z = &y;                                    \
} while (false)

#endif // CJDB_TEST_CONSTEXPR_CHECK
