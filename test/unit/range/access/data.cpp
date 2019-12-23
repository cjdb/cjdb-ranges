// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#if not defined(CPO)
	#error "DATA_PRIMITIVE must be defined as data or cdata."
#elif not defined(IS_CONST)
	#error "IS_CONST must be defined as true or false."
#endif // DATA_PRIMITIVE

#if defined(DATA) and not defined(CDATA)
	#include "cjdb/detail/range/data.hpp"
#elif defined(CDATA) and not defined(DATA)
	#include "cjdb/detail/range/cdata.hpp"
#else
	#error "Must define exactly one of DATA or CDATA"
#endif

#include "cjdb/test/range/access.hpp"
#include <functional>

constexpr auto data = []<typename T>(T&& t){
	return std::to_address(cjdb::ranges::begin(std::forward<T>(t)));
};

namespace cjdb_test {
	DEFINE_CHECK_FOR_FAULTY_ACCESS(CPO, data);
	DEFINE_CHECK_FOR_C_ARRAY_ACCESS(CPO, data);
	DEFINE_CHECK_FOR_MEMBER_ACCESS(CPO, data);
	DEFINE_CHECK_FOR_UNQUALIFIED_ACCESS(CPO, data, IS_CONST);
} // namespace cjdb_test

int main()
{
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::CJDB_TEST_CONCAT(faulty_, CPO), cjdb_test::bad_lvalue_range_unqualified{});
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::CJDB_TEST_CONCAT(faulty_, CPO), cjdb_test::bad_lvalue_range_preferred{});
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::CJDB_TEST_CONCAT(faulty_, CPO), cjdb_test::bad_lvalue_range_private_members{});

	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::CJDB_TEST_CONCAT(faulty_, CPO), cjdb_test::bad_rvalue_range_members{});
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::CJDB_TEST_CONCAT(faulty_, CPO), cjdb_test::bad_rvalue_range_unqualified{});
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::CJDB_TEST_CONCAT(faulty_, CPO), cjdb_test::bad_rvalue_range_preferred{});
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::CJDB_TEST_CONCAT(faulty_, CPO), cjdb_test::bad_rvalue_range_private_members{});

	// NOLINTNEXTLINE(readability-magic-numbers)
	CJDB_EVALUATE_TEST_CASE(cjdb_test::lvalue_array<int, 30>{});
	// NOLINTNEXTLINE(readability-magic-numbers)
	CJDB_EVALUATE_TEST_CASE(cjdb_test::lvalue_array<double, 43>{});
	// NOLINTNEXTLINE(readability-magic-numbers)
	CJDB_EVALUATE_TEST_CASE(cjdb_test::lvalue_array<cjdb_test::dummy, 210>{});

	cjdb_test::CJDB_TEST_CONCAT(member_, CPO)<std::vector<std::set<int>>>{}();
	cjdb_test::CJDB_TEST_CONCAT(member_, CPO)<cjdb_test::lvalue_range_with_members>{}();
	cjdb_test::CJDB_TEST_CONCAT(member_, CPO)<cjdb_test::lvalue_range_with_members_and_unqualified_friends>{}();

	CJDB_EVALUATE_TEST_CASE(cjdb_test::unqualified<cjdb_test::unqualified_lvalue_range<>&>{});
	CJDB_EVALUATE_TEST_CASE(cjdb_test::unqualified<cjdb_test::unqualified_lvalue_range_preferred<>&>{});
	CJDB_EVALUATE_TEST_CASE(cjdb_test::unqualified<cjdb_test::unqualified_lvalue_range_private_members<>&>{});
	CJDB_EVALUATE_TEST_CASE(cjdb_test::unqualified<cjdb_test::unqualified_rvalue_range<>&&>{});
	CJDB_EVALUATE_TEST_CASE(cjdb_test::unqualified<cjdb_test::unqualified_rvalue_range_preferred<>&&>{});
	CJDB_EVALUATE_TEST_CASE(cjdb_test::unqualified<cjdb_test::unqualified_rvalue_range_private_members<>&&>{});

	return ::test_result();
}
