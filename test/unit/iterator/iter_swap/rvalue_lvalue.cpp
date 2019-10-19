// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/detail/iterator/iter_swap.hpp"

#include "cjdb/contracts.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/utility/swap.hpp"
#include <utility>

class s {
public:
	s() = default;

	constexpr explicit s(int x) noexcept
	: x_{x}
	{}

	constexpr s(s&& other) noexcept
	: x_{other.x_}
	{}

	constexpr s& operator=(s&& other) noexcept
	{
		x_ = other.x_;
		return *this;
	}

	constexpr s(s const& other) noexcept // NOLINT(modernize-use-equals-default)
	: x_{other.x_}
	{}

	constexpr s& operator=(s const& other) noexcept // NOLINT(modernize-use-equals-default)
	{
		x_ = other.x_;
		return *this;
	}

	[[nodiscard]] constexpr int x() const noexcept
	{ return x_; }

	friend constexpr void iter_swap(s&& x, s& y) noexcept
	{
		cjdb::ranges::swap(std::move(x), y);
	}

	friend constexpr void swap(s&& x, s& y) noexcept
	{
		x = std::exchange(y, std::move(x));
	}
private:
	int x_;
};
static_assert(cjdb::ranges::detail_iter_swap::unqualified_iter_swap<s, s&>);
static_assert(noexcept(iter_swap(std::declval<s>(), std::declval<s&>())));
static_assert(noexcept(cjdb::ranges::iter_swap(std::declval<s>(), std::declval<s&>())));

static_assert(not cjdb::ranges::detail_iter_swap::unqualified_iter_swap<s&, s&>);
static_assert(not cjdb::ranges::detail_iter_swap::unqualified_iter_swap<s const&, s&>);
static_assert(not cjdb::ranges::detail_iter_swap::unqualified_iter_swap<s&, s const&>);
static_assert(not cjdb::ranges::detail_iter_swap::unqualified_iter_swap<s const&, s const&>);
static_assert(not cjdb::ranges::detail_iter_swap::unqualified_iter_swap<s&, s>);
static_assert(not cjdb::ranges::detail_iter_swap::unqualified_iter_swap<s const&, s>);
static_assert(not cjdb::ranges::detail_iter_swap::unqualified_iter_swap<s, s const&>);
static_assert(not cjdb::ranges::detail_iter_swap::unqualified_iter_swap<s, s>);
static_assert(not cjdb::indirectly_swappable<s, s>);
static_assert(not cjdb::indirectly_swappable<s const, s>);
static_assert(not cjdb::indirectly_swappable<s, s const>);
static_assert(not cjdb::indirectly_swappable<s const, s const>);

auto first_test = []{
	constexpr auto initial_x = 10;
	auto x = s{initial_x};
	CJDB_ASSERT(x.x() == initial_x);

	constexpr auto initial_y = -119;
	auto y = s{initial_y};
	CJDB_ASSERT(y.x() == initial_y);

	cjdb::ranges::iter_swap(std::move(x), y);
	CJDB_CONSTEXPR_CHECK(x.x() == initial_y); // NOLINT(bugprone-use-after-move)
	CJDB_CONSTEXPR_CHECK(y.x() == initial_x);

	cjdb::ranges::iter_swap(std::move(y), x);
	CJDB_CONSTEXPR_CHECK(x.x() == initial_x);
	CJDB_CONSTEXPR_CHECK(y.x() == initial_y); // NOLINT(bugprone-use-after-move)
};

auto second_test = []{
	constexpr auto initial_x = -32542;
	auto x = s{initial_x};
	CJDB_ASSERT(x.x() == initial_x);

	constexpr auto initial_y = 33112;
	auto y = s{initial_y};
	CJDB_ASSERT(y.x() == initial_y);

	using namespace cjdb::ranges;
	iter_swap(std::move(y), x);
	CJDB_CONSTEXPR_CHECK(x.x() == initial_y);
	CJDB_CONSTEXPR_CHECK(y.x() == initial_x); // NOLINT(bugprone-use-after-move)

	iter_swap(std::move(x), y);
	CJDB_CONSTEXPR_CHECK(x.x() == initial_x); // NOLINT(bugprone-use-after-move)
	CJDB_CONSTEXPR_CHECK(y.x() == initial_y);
};

int main()
{
	CJDB_EVALUATE_TEST_CASE(first_test);
	CJDB_EVALUATE_TEST_CASE(second_test);
	return ::test_result();
}
