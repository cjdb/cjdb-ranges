// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/functional/rangecmp/less.hpp"

#include "cjdb/concepts/comparison/totally_ordered.hpp"
#include "cjdb/test/functional/rangecmp/is_strict_total_order.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/simple_test.hpp"
#include <string_view>


using cjdb::ranges::less;
static_assert(less::is_transparent{});

using namespace std::string_view_literals;
constexpr auto hello = "hello"sv;
constexpr auto konnichiwa = "konnichiwa"sv; // it's infuriating that "こんにちは" <= "hello" at
                                            // compile-time.

auto is_total_order = []{
	CHECK_IS_STRICT_TOTAL_ORDER(less{}, 0, 1, 2);  // NOLINT(readability-magic-numbers)
	CHECK_IS_STRICT_TOTAL_ORDER(less{}, 0, 1.0, 2);  // NOLINT(readability-magic-numbers)
	CHECK_IS_STRICT_TOTAL_ORDER(less{}, 1, 1.5, 2);  // NOLINT(readability-magic-numbers)

	CHECK_IS_STRICT_TOTAL_ORDER(less{}, "a"sv, "ab"sv, "c"sv); // NOLINT(readability-magic-numbers)
	CHECK_IS_STRICT_TOTAL_ORDER(less{}, "a"sv, "ab", "c"sv);  // NOLINT(readability-magic-numbers)
};

auto same_type_ordering = []{
	CJDB_CONSTEXPR_CHECK(less{}(3, 4));  // NOLINT(readability-magic-numbers)
	CJDB_CONSTEXPR_CHECK(not less{}(40, 3));  // NOLINT(readability-magic-numbers)

	CJDB_CONSTEXPR_CHECK(less{}(hello, konnichiwa));
	CJDB_CONSTEXPR_CHECK(not less{}(konnichiwa, hello));
};

auto cross_type_ordering = []{
	CJDB_CONSTEXPR_CHECK(less{}(3.0, 4));  // NOLINT(readability-magic-numbers)

	// int promoted to double
	CJDB_CONSTEXPR_CHECK(not less{}(3.9999, 3));  // NOLINT(readability-magic-numbers)

	CJDB_CONSTEXPR_CHECK(less{}(hello, konnichiwa.data()));
	CJDB_CONSTEXPR_CHECK(not less{}(konnichiwa.data(), hello));
};

int main()
{
	CJDB_EVALUATE_TEST_CASE(is_total_order);
	CJDB_EVALUATE_TEST_CASE(same_type_ordering);
	CJDB_EVALUATE_TEST_CASE(cross_type_ordering);
	return ::test_result();
}
