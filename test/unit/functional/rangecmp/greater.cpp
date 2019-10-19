// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/functional/rangecmp/greater.hpp"

#include "cjdb/concepts/comparison/totally_ordered.hpp"
#include "cjdb/test/functional/rangecmp/is_strict_total_order.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/simple_test.hpp"
#include <string_view>

using cjdb::ranges::greater;
static_assert(greater::is_transparent{});

using namespace std::string_view_literals;
constexpr auto hello = "hello"sv;
constexpr auto konnichiwa = "konnichiwa"sv; // it's infuriating that "こんにちは" <= "hello" at
                                            // compile-time.

auto is_total_order = []{ // shows greater is a strict total order
	CHECK_IS_STRICT_TOTAL_ORDER(greater{}, 2, 1, 0);   // NOLINT(readability-magic-numbers)
	CHECK_IS_STRICT_TOTAL_ORDER(greater{}, 2, 1.0, 0); // NOLINT(readability-magic-numbers)
	CHECK_IS_STRICT_TOTAL_ORDER(greater{}, 2, 1.5, 1); // NOLINT(readability-magic-numbers)

	CHECK_IS_STRICT_TOTAL_ORDER(greater{}, "c"sv, "ab"sv, "a"sv);
	CHECK_IS_STRICT_TOTAL_ORDER(greater{}, "c"sv, "ab"sv, "a"sv);
};

auto same_type_ordering = []{
	CJDB_CONSTEXPR_CHECK(greater{}(4, 3));      // NOLINT(readability-magic-numbers)
	CJDB_CONSTEXPR_CHECK(not greater{}(3, 40)); // NOLINT(readability-magic-numbers)

	CJDB_CONSTEXPR_CHECK(greater{}(konnichiwa, hello));
	CJDB_CONSTEXPR_CHECK(not greater{}(hello, konnichiwa));
};

auto cross_type_ordering = []{
	CJDB_CONSTEXPR_CHECK(greater{}(4, 3.0)); // NOLINT(readability-magic-numbers)

	// int promoted to double
	CJDB_CONSTEXPR_CHECK(not greater{}(3, 3.9999)); // NOLINT(readability-magic-numbers)

	CJDB_CONSTEXPR_CHECK(greater{}(konnichiwa.data(), hello));
	CJDB_CONSTEXPR_CHECK(not greater{}(hello, konnichiwa.data()));
};

int main()
{
	CJDB_EVALUATE_TEST_CASE(is_total_order);
	CJDB_EVALUATE_TEST_CASE(same_type_ordering);
	CJDB_EVALUATE_TEST_CASE(cross_type_ordering);
	return ::test_result();
}
