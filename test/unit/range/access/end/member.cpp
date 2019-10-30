// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/detail/range/end.hpp"

#include "cjdb/concepts/core/default_initializable.hpp"
#include "cjdb/concepts/callable/invocable.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/range/lvalue_range_with_members.hpp"

#include <algorithm>
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <set>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// NOLINTNEXTLINE(readability-magic-numbers)
static_assert(cjdb::ranges::detail_end::member_end<std::array<int, 100>&>);
// NOLINTNEXTLINE(readability-magic-numbers)
static_assert(cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::array<int, 100>&>);
static_assert(cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::map<int, double>&>);
static_assert(cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::map<int, double> const&>);
static_assert(cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::multimap<int, double>&>);
static_assert(cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::multimap<int, double> const&>);
static_assert(cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::multiset<std::array<int, 1>>&>);
static_assert(cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::multiset<std::array<int, 1>> const&>);
static_assert(cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::set<std::array<int, 1>>&>);
static_assert(cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::set<std::array<int, 1>> const&>);
static_assert(cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::unordered_map<int, int>&>);
static_assert(cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::unordered_map<int, int> const&>);
static_assert(cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::unordered_multimap<int, int>&>);
static_assert(cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::unordered_multimap<int, int> const&>);
static_assert(cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::unordered_set<float>&>);
static_assert(cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::unordered_set<float> const&>);
static_assert(cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::unordered_multiset<float>&>);
static_assert(cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::unordered_multiset<float> const&>);

static_assert(not cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::map<int, double>&&>);
static_assert(not cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::multimap<int, double>&&>);
static_assert(not cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::multiset<std::array<int, 1>>&&>);
static_assert(not cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::set<std::array<int, 1>>&&>);
static_assert(not cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::unordered_map<int, int>&&>);
static_assert(not cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::unordered_multimap<int, int>&&>);
static_assert(not cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::unordered_set<float>&&>);
static_assert(not cjdb::invocable<cjdb::ranges::detail_end::end_fn, std::unordered_multiset<float>&&>);

namespace cjdb_test {
	template<cjdb::default_initializable Range>
	struct member_end {
		void operator()() const noexcept
		{
			static_assert(cjdb::ranges::detail_end::member_end<Range&>);
			static_assert(cjdb::invocable<cjdb::ranges::detail_end::end_fn, Range&>);
			static_assert(cjdb::input_or_output_iterator<std::invoke_result_t<cjdb::ranges::detail_end::end_fn, Range&>>);
			{
				auto r = Range{};
				static_assert(noexcept(cjdb::ranges::end(r)) == noexcept(r.end()));
			}

			static_assert(cjdb::ranges::detail_end::member_end<Range const&>);
			static_assert(cjdb::invocable<cjdb::ranges::detail_end::end_fn, Range const&>);
			static_assert(cjdb::input_or_output_iterator<std::invoke_result_t<cjdb::ranges::detail_end::end_fn, Range const&>>);
			{
				auto const r = Range{};
				static_assert(noexcept(cjdb::ranges::end(r)) == noexcept(r.end()));
			}

			static_assert(not cjdb::invocable<cjdb::ranges::detail_end::end_fn, Range>);
			static_assert(not cjdb::invocable<cjdb::ranges::detail_end::end_fn, Range&&>);

			// TODO(@cjdb): remove me once std::vector and std::string are constexpr
			if (not std::is_constant_evaluated()) {
				constexpr auto container_size = 100;
				auto r = Range(container_size, typename Range::value_type{});
				static_assert(cjdb::equality_comparable<decltype(r.end())>);
				CHECK(r.end() == cjdb::ranges::end(r));
			}
		}
	};
} // namespace cjdb_test

int main()
{
	cjdb_test::member_end<std::deque<double(*)()>>{}();
	cjdb_test::member_end<std::forward_list<int>>{}();
	cjdb_test::member_end<std::list<std::vector<int>>>{}();
	cjdb_test::member_end<std::vector<std::set<int>>>{}();
	cjdb_test::member_end<cjdb_test::lvalue_range_with_members>{}();
	cjdb_test::member_end<cjdb_test::lvalue_range_with_members_and_unqualified_friends>{}();

	return ::test_result();
}
