// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/functional/rangecmp/equal_to.hpp"

#include "cjdb/concepts/comparison/equality_comparable.hpp"
#include "cjdb/test/functional/rangecmp/is_equivalence.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/simple_test.hpp"
#include <string_view>

using cjdb::ranges::equal_to;
static_assert(equal_to::is_transparent{});

using namespace std::string_view_literals;
constexpr auto hello = "hello"sv;
constexpr auto goodbye = "goodbye"sv;

auto is_equivalence_relation = []{
	CHECK_IS_EQUIVALENCE(equal_to{}, 0, 0, 0);
	CHECK_IS_EQUIVALENCE(equal_to{}, 0, 0.0, 0);
	CHECK_IS_EQUIVALENCE(equal_to{}, 0.0, 0, 0.0);

	CHECK_IS_EQUIVALENCE(equal_to{}, hello, hello, hello);
};

auto same_type_equality = []{
	CJDB_CONSTEXPR_CHECK(equal_to{}(0, 0));
	CJDB_CONSTEXPR_CHECK(not equal_to{}(0, 1));

	CJDB_CONSTEXPR_CHECK(equal_to{}(hello, hello));
	CJDB_CONSTEXPR_CHECK(not equal_to{}(hello, goodbye));
};

auto cross_type_equality = []{
	CJDB_CONSTEXPR_CHECK(equal_to{}(1, 1.0));

	// int is promoted to double
	CJDB_CONSTEXPR_CHECK(not equal_to{}(1, 1.5)); // NOLINT(readability-magic-numbers)

	// outright not equal
	CJDB_CONSTEXPR_CHECK(not equal_to{}(1, 2.6)); // NOLINT(readability-magic-numbers)

	CJDB_CONSTEXPR_CHECK(equal_to{}(hello, hello.data()));
	CJDB_CONSTEXPR_CHECK(not equal_to{}(hello, goodbye.data()));
};

int main()
{
	CJDB_EVALUATE_TEST_CASE(is_equivalence_relation);
	CJDB_EVALUATE_TEST_CASE(same_type_equality);
	CJDB_EVALUATE_TEST_CASE(cross_type_equality);

	return ::test_result();
}
