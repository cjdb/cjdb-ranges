// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/functional/rangecmp/less_equal.hpp"

#include "cjdb/concepts/comparison/totally_ordered.hpp"
#include "cjdb/test/functional/rangecmp/is_partial_order.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/simple_test.hpp"
#include <string_view>


int main()
{
	using cjdb::ranges::less_equal;
	using namespace std::string_view_literals;

	static_assert(less_equal::is_transparent{});

	{ // shows less_equal is a partial order
		CHECK_IS_PARTIAL_ORDER(less_equal{}, 0, 1, 2);    // NOLINT(readability-magic-numbers)
		CHECK_IS_PARTIAL_ORDER(less_equal{}, 0, 1.0, 2);  // NOLINT(readability-magic-numbers)
		CHECK_IS_PARTIAL_ORDER(less_equal{}, 1, 1.5, 2);  // NOLINT(readability-magic-numbers)

		CHECK_IS_PARTIAL_ORDER(less_equal{}, "a"sv, "ab"sv, "c"sv); // NOLINT(readability-magic-numbers)
		CHECK_IS_PARTIAL_ORDER(less_equal{}, "a"sv, "ab"sv, "c"sv); // NOLINT(readability-magic-numbers)
	}

	constexpr auto hello = "hello"sv;
	constexpr auto konnichiwa = "konnichiwa"sv; // it's infuriating that "こんにちは" <= "hello" at
															  // compile-time.

	{ // shows less_equal works for same-type ordering
		CJDB_CONSTEXPR_CHECK(less_equal{}(30, 30));     // NOLINT(readability-magic-numbers)
		CJDB_CONSTEXPR_CHECK(less_equal{}(3, 4));       // NOLINT(readability-magic-numbers)
		CJDB_CONSTEXPR_CHECK(not less_equal{}(40, 3));  // NOLINT(readability-magic-numbers)

		CJDB_CONSTEXPR_CHECK(less_equal{}(hello, hello));
		CJDB_CONSTEXPR_CHECK(less_equal{}(hello, konnichiwa));
		CJDB_CONSTEXPR_CHECK(not less_equal{}(konnichiwa, hello));
	}

	{ // shows less_equal works for cross-type ordering
		CJDB_CONSTEXPR_CHECK(less_equal{}(3, 3.0)); // NOLINT(readability-magic-numbers)
		CJDB_CONSTEXPR_CHECK(less_equal{}(3.0, 4)); // NOLINT(readability-magic-numbers)

		// int promoted to double
		CJDB_CONSTEXPR_CHECK(not less_equal{}(3.9999, 3)); // NOLINT(readability-magic-numbers)

		CJDB_CONSTEXPR_CHECK(less_equal{}(hello, hello.data()));
		CJDB_CONSTEXPR_CHECK(less_equal{}(hello, konnichiwa.data()));
		CJDB_CONSTEXPR_CHECK(not less_equal{}(konnichiwa.data(), hello));
	}

	return ::test_result();
}
