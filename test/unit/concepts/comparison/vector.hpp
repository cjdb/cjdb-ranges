// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_CONCEPTS_COMPARISON_VECTOR_HPP
#define CJDB_TEST_CONCEPTS_COMPARISON_VECTOR_HPP

#include <vector>

bool operator<(std::vector<int> const& x, std::vector<int>::size_type const y) noexcept
{
	return x.size() < y;
}

bool operator<(std::vector<int>::size_type const x, std::vector<int> const& y) noexcept
{
	return x < y.size();
}

bool operator>(std::vector<int> const& x, std::vector<int>::size_type const y) noexcept
{
	return y < x;
}

bool operator>(std::vector<int>::size_type const x, std::vector<int> const& y) noexcept
{
	return y < x;
}

bool operator<=(std::vector<int> const& x, std::vector<int>::size_type const y) noexcept
{
	return not (y < x);
}

bool operator<=(std::vector<int>::size_type const x, std::vector<int> const& y) noexcept
{
	return not (y < x);
}

bool operator>=(std::vector<int> const& x, std::vector<int>::size_type const y) noexcept
{
	return not (x < y);
}

bool operator>=(std::vector<int>::size_type const x, std::vector<int> const& y) noexcept
{
	return not (x < y);
}

bool operator==(std::vector<int> const& x, std::vector<int>::size_type const y) noexcept
{
	return x.size() == y;
}

bool operator==(std::vector<int>::size_type const x, std::vector<int> const& y) noexcept
{
	return y == x;
}

bool operator!=(std::vector<int> const& x, std::vector<int>::size_type const y) noexcept
{
	return not (x == y);
}

bool operator!=(std::vector<int>::size_type const x, std::vector<int> const& y) noexcept
{
	return not (y == x);
}

template<class T1, class T2>
concept weakly_sto = requires(T1 const& x, T2 const y) {
	x == y;
	x != y;

	y == x;
	y != x;

	x < y;
	x <= y;
	x >= y;
	x > y;

	y < x;
	y <= x;
	y >= x;
	y > x;
};

static_assert(weakly_sto<std::vector<int>, std::vector<int>::size_type>);

#endif // CJDB_TEST_CONCEPTS_COMPARISON_VECTOR_HPP
