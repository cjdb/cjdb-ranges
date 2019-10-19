// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/detail/iterator/iter_swap.hpp"
#include "cjdb/iterator/concepts/indirectly_swappable.hpp"

#include "cjdb/contracts.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/utility/swap.hpp"
#include <utility>

class s {
public:
	s() = default;

	constexpr explicit s(int const x) noexcept
	: x_{x}
	{}

	[[nodiscard]] constexpr int value() const noexcept { return x_; }

	friend constexpr void iter_swap(s& x, s& y)
	{
		cjdb::ranges::swap(x, y);
	}
private:
	int x_ = 0;
};
static_assert(cjdb::ranges::detail_iter_swap::unqualified_iter_swap<s&, s&>);

static_assert(not cjdb::ranges::detail_iter_swap::unqualified_iter_swap<s&, s const&>);
static_assert(not cjdb::ranges::detail_iter_swap::unqualified_iter_swap<s const&, s&>);
static_assert(not cjdb::ranges::detail_iter_swap::unqualified_iter_swap<s const&, s const&>);
static_assert(not cjdb::ranges::detail_iter_swap::unqualified_iter_swap<s&, s>);
static_assert(not cjdb::ranges::detail_iter_swap::unqualified_iter_swap<s, s&>);
static_assert(not cjdb::ranges::detail_iter_swap::unqualified_iter_swap<s, s>);
static_assert(not noexcept(iter_swap(std::declval<s&>(), std::declval<s&>())));
static_assert(not noexcept(cjdb::ranges::iter_swap(std::declval<s&>(), std::declval<s&>())));
static_assert(not cjdb::indirectly_swappable<s, s>);
static_assert(not cjdb::indirectly_swappable<s const, s>);
static_assert(not cjdb::indirectly_swappable<s, s const>);
static_assert(not cjdb::indirectly_swappable<s const, s const>);

auto test_case_1 = []{
	auto x = s{};
	CJDB_ASSERT(x.value() == 0);

	auto y = s{1};
	CJDB_ASSERT(y.value() == 1);

	cjdb::ranges::iter_swap(x, y);
	CJDB_CONSTEXPR_CHECK(x.value() == 1);
	CJDB_CONSTEXPR_CHECK(y.value() == 0);

	cjdb::ranges::iter_swap(x, y);
	CJDB_CONSTEXPR_CHECK(x.value() == 0);
	CJDB_CONSTEXPR_CHECK(y.value() == 1);
};

auto test_case_2 = []{
	constexpr auto initial_x = 44;
	auto x = s{initial_x};
	CJDB_ASSERT(x.value() == initial_x);

	constexpr auto initial_y = -314;
	auto y = s{initial_y};
	CJDB_ASSERT(y.value() == initial_y);

	using cjdb::ranges::iter_swap;
	iter_swap(x, y);
	CJDB_CONSTEXPR_CHECK(x.value() == initial_y);
	CJDB_CONSTEXPR_CHECK(y.value() == initial_x);

	iter_swap(x, y);
	CJDB_CONSTEXPR_CHECK(x.value() == initial_x);
	CJDB_CONSTEXPR_CHECK(y.value() == initial_y);
};

int main()
{
	CJDB_EVALUATE_TEST_CASE(test_case_1);
	CJDB_EVALUATE_TEST_CASE(test_case_2);
	return ::test_result();
}
