// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/functional/rangecmp/greater.hpp"

#include "cjdb/concepts/comparison/totally_ordered.hpp"
#include "cjdb/test/functional/rangecmp/is_strict_total_order.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/simple_test.hpp"
#include <string_view>


int main()
{
	using cjdb::ranges::greater;
	using namespace std::string_view_literals;

	static_assert(greater::is_transparent{});

	{ // shows greater is a strict total order
		CHECK_IS_STRICT_TOTAL_ORDER(greater{}, 2, 1, 0);   // NOLINT(readability-magic-numbers)
		CHECK_IS_STRICT_TOTAL_ORDER(greater{}, 2, 1.0, 0); // NOLINT(readability-magic-numbers)
		CHECK_IS_STRICT_TOTAL_ORDER(greater{}, 2, 1.5, 1); // NOLINT(readability-magic-numbers)

		CHECK_IS_STRICT_TOTAL_ORDER(greater{}, "c"sv, "ab"sv, "a"sv); // NOLINT(readability-magic-numbers)
		CHECK_IS_STRICT_TOTAL_ORDER(greater{}, "c"sv, "ab"sv, "a"sv); // NOLINT(readability-magic-numbers)
	}

	constexpr auto hello = "hello"sv;
	constexpr auto konnichiwa = "konnichiwa"sv; // it's infuriating that "こんにちは" <= "hello" at
	                                            // compile-time.

	{ // shows greater works for same-type ordering
		CJDB_CONSTEXPR_CHECK(greater{}(4, 3));      // NOLINT(readability-magic-numbers)
		CJDB_CONSTEXPR_CHECK(not greater{}(3, 40)); // NOLINT(readability-magic-numbers)

		CJDB_CONSTEXPR_CHECK(greater{}(konnichiwa, hello));
		CJDB_CONSTEXPR_CHECK(not greater{}(hello, konnichiwa));
	}

	{ // shows greater works for cross-type ordering
		CJDB_CONSTEXPR_CHECK(greater{}(4, 3.0)); // NOLINT(readability-magic-numbers)

		// int promoted to double
		CJDB_CONSTEXPR_CHECK(not greater{}(3, 3.9999)); // NOLINT(readability-magic-numbers)

		CJDB_CONSTEXPR_CHECK(greater{}(konnichiwa.data(), hello));
		CJDB_CONSTEXPR_CHECK(not greater{}(hello, konnichiwa.data()));
	}

	return ::test_result();
}
