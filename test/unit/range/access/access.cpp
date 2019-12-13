// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CPO
	#error "CPO must be defined by the compiler."
#endif // CPO

#ifndef BASE_CPO
	#error "BASE_CPO must be defined by the compiler."
#endif // BASE_CPO

#ifndef IS_CONST
	#error "IS_CONST must be defined by the compiler."
#endif // BASE_CPO

#if defined(BEGIN) and not (defined(CBEGIN) or defined(END) or defined(CEND))
	#include "cjdb/detail/range/begin.hpp"
#elif defined(CBEGIN) and not (defined(BEGIN) or defined(END) or defined(CEND))
	#include "cjdb/detail/range/cbegin.hpp"
#elif defined(END) and not (defined(BEGIN) or defined(CBEGIN) or defined(CEND))
	#include "cjdb/detail/range/end.hpp"
#elif defined(CEND) and not (defined(BEGIN) or defined(CBEGIN) or defined(END))
	#include "cjdb/detail/range/cend.hpp"
#else
	#error "Must define exactly one of BEGIN, CBEGIN, END, or CEND"
#endif // CPO

#include "cjdb/test/range/access.hpp"

namespace cjdb_test {
	DEFINE_CHECK_FOR_FAULTY_ACCESS(CPO, BASE_CPO);
	DEFINE_CHECK_FOR_C_ARRAY_ACCESS(CPO, BASE_CPO);
	DEFINE_CHECK_FOR_MEMBER_ACCESS(CPO, BASE_CPO);
	DEFINE_CHECK_FOR_UNQUALIFIED_ACCESS(CPO, BASE_CPO, IS_CONST);
} // namespace cjdb_test

static_assert(cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::map<int, double>&>);
static_assert(cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::map<int, double> const&>);
static_assert(cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::multimap<int, double>&>);
static_assert(cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::multimap<int, double> const&>);
static_assert(cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::multiset<std::array<int, 1>>&>);
static_assert(cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::multiset<std::array<int, 1>> const&>);
static_assert(cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::set<std::array<int, 1>>&>);
static_assert(cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::set<std::array<int, 1>> const&>);
static_assert(cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::unordered_map<int, int>&>);
static_assert(cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::unordered_map<int, int> const&>);
static_assert(cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::unordered_multimap<int, int>&>);
static_assert(cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::unordered_multimap<int, int> const&>);
static_assert(cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::unordered_set<float>&>);
static_assert(cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::unordered_set<float> const&>);
static_assert(cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::unordered_multiset<float>&>);
static_assert(cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::unordered_multiset<float> const&>);

static_assert(not cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::map<int, double>&&>);
static_assert(not cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::multimap<int, double>&&>);
static_assert(not cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::multiset<std::array<int, 1>>&&>);
static_assert(not cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::set<std::array<int, 1>>&&>);
static_assert(not cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::unordered_map<int, int>&&>);
static_assert(not cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::unordered_multimap<int, int>&&>);
static_assert(not cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::unordered_set<float>&&>);
static_assert(not cjdb::invocable<cjdb::ranges::CJDB_TEST_CONCAT(detail_, BASE_CPO)::CJDB_TEST_CONCAT(BASE_CPO, _fn), std::unordered_multiset<float>&&>);

int main()
{
	// NOLINTNEXTLINE(readability-magic-numbers)
	CJDB_EVALUATE_TEST_CASE(cjdb_test::lvalue_array<int, 30>{});
	//* NOLINTNEXTLINE(readability-magic-numbers)
	CJDB_EVALUATE_TEST_CASE(cjdb_test::lvalue_array<double, 43>{});
	// NOLINTNEXTLINE(readability-magic-numbers)
	CJDB_EVALUATE_TEST_CASE(cjdb_test::lvalue_array<cjdb_test::dummy, 210>{});

	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::CJDB_TEST_CONCAT(faulty_, CPO), cjdb_test::bad_lvalue_range_unqualified{});
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::CJDB_TEST_CONCAT(faulty_, CPO), cjdb_test::bad_lvalue_range_preferred{});
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::CJDB_TEST_CONCAT(faulty_, CPO), cjdb_test::bad_lvalue_range_private_members{});

	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::CJDB_TEST_CONCAT(faulty_, CPO), cjdb_test::bad_rvalue_range_members{});
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::CJDB_TEST_CONCAT(faulty_, CPO), cjdb_test::bad_rvalue_range_unqualified{});
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::CJDB_TEST_CONCAT(faulty_, CPO), cjdb_test::bad_rvalue_range_preferred{});
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::CJDB_TEST_CONCAT(faulty_, CPO), cjdb_test::bad_rvalue_range_private_members{});

	cjdb_test::CJDB_TEST_CONCAT(member_, CPO)<std::deque<double(*)()>>{}();
	cjdb_test::CJDB_TEST_CONCAT(member_, CPO)<std::forward_list<int>>{}();
	cjdb_test::CJDB_TEST_CONCAT(member_, CPO)<std::list<std::vector<int>>>{}();
	cjdb_test::CJDB_TEST_CONCAT(member_, CPO)<std::vector<std::set<int>>>{}();
	cjdb_test::CJDB_TEST_CONCAT(member_, CPO)<cjdb_test::lvalue_range_with_members>{}();
	cjdb_test::CJDB_TEST_CONCAT(member_, CPO)<cjdb_test::lvalue_range_with_members_and_unqualified_friends>{}();

	CJDB_EVALUATE_TEST_CASE(cjdb_test::unqualified<cjdb_test::unqualified_lvalue_range&>{});
	CJDB_EVALUATE_TEST_CASE(cjdb_test::unqualified<cjdb_test::unqualified_lvalue_range_preferred&>{});
	CJDB_EVALUATE_TEST_CASE(cjdb_test::unqualified<cjdb_test::unqualified_lvalue_range_private_members&>{});
	CJDB_EVALUATE_TEST_CASE(cjdb_test::unqualified<cjdb_test::unqualified_rvalue_range&&>{});
	CJDB_EVALUATE_TEST_CASE(cjdb_test::unqualified<cjdb_test::unqualified_rvalue_range_preferred&&>{});
	CJDB_EVALUATE_TEST_CASE(cjdb_test::unqualified<cjdb_test::unqualified_rvalue_range_private_members&&>{});

	return ::test_result();
}
