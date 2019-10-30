// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/detail/range/end.hpp"

#include "cjdb/concepts/core/default_initializable.hpp"
#include "cjdb/concepts/callable/invocable.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/range/bad_lvalue_range.hpp"
#include "cjdb/test/range/bad_rvalue_range.hpp"
#include <utility>

auto faulty_end = []<typename T>(T) {
	static_assert(not cjdb::ranges::detail_end::member_end<T&>);
	static_assert(not cjdb::ranges::detail_end::member_end<T const&>);
	static_assert(not cjdb::ranges::detail_end::member_end<T&&>);
	static_assert(not cjdb::ranges::detail_end::member_end<T const&&>);

	static_assert(not cjdb::ranges::detail_end::unqualified_end<T&>);
	static_assert(not cjdb::ranges::detail_end::unqualified_end<T const&>);
	static_assert(not cjdb::ranges::detail_end::unqualified_end<T&&>);
	static_assert(not cjdb::ranges::detail_end::unqualified_end<T const&&>);

	static_assert(not cjdb::invocable<cjdb::ranges::detail_end::end_fn, T&>);
	static_assert(not cjdb::invocable<cjdb::ranges::detail_end::end_fn, T const&>);
	static_assert(not cjdb::invocable<cjdb::ranges::detail_end::end_fn, T>);
	static_assert(not cjdb::invocable<cjdb::ranges::detail_end::end_fn, T const>);
};

int main()
{
	CJDB_EVALUATE_TEST_CASE_N(faulty_end, cjdb_test::bad_lvalue_range_unqualified{});
	CJDB_EVALUATE_TEST_CASE_N(faulty_end, cjdb_test::bad_lvalue_range_preferred{});
	CJDB_EVALUATE_TEST_CASE_N(faulty_end, cjdb_test::bad_lvalue_range_private_members{});

	CJDB_EVALUATE_TEST_CASE_N(faulty_end, cjdb_test::bad_rvalue_range_members{});
	CJDB_EVALUATE_TEST_CASE_N(faulty_end, cjdb_test::bad_rvalue_range_unqualified{});
	CJDB_EVALUATE_TEST_CASE_N(faulty_end, cjdb_test::bad_rvalue_range_preferred{});
	CJDB_EVALUATE_TEST_CASE_N(faulty_end, cjdb_test::bad_rvalue_range_private_members{});
	return ::test_result();
}
