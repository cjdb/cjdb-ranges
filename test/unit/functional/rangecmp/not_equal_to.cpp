// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/functional/rangecmp/not_equal_to.hpp"

#include "cjdb/concepts/comparison/equality_comparable.hpp"
#include "cjdb/test/functional/rangecmp/is_irreflexive.hpp"
#include "cjdb/test/functional/rangecmp/is_symmetric.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/simple_test.hpp"
#include <string_view>
#include <utility>

int main()
{
	using cjdb::ranges::not_equal_to;
	using namespace std::string_view_literals;

	static_assert(not_equal_to::is_transparent{});

	constexpr auto hello = "hello"sv;

	{ // Checks not_equal_to is irreflexive and symmetric
		CHECK_IS_IRREFLEXIVE(not_equal_to{}, 0);
		CHECK_IS_IRREFLEXIVE(not_equal_to{}, hello);
	}

	{ // Checks not_equal_to works for same-type inequality
		CJDB_CONSTEXPR_CHECK(not_equal_to{}(0, 1));

		CJDB_CONSTEXPR_CHECK(not not_equal_to{}(0, 0));
	}

	{ // Checks not_equal_to works for cross-type inequality
		// int is promoted to double
		CJDB_CONSTEXPR_CHECK(not_equal_to{}(1, 1.5)); // NOLINT(readability-magic-numbers)
		// just outright not equal
		CJDB_CONSTEXPR_CHECK(not_equal_to{}(1, 2.6)); // NOLINT(readability-magic-numbers)

		CJDB_CONSTEXPR_CHECK(not not_equal_to{}(1, 1.0));
	}

	return ::test_result();
}
