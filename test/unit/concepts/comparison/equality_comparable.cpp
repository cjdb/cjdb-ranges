// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/concepts/comparison/equality_comparable.hpp"

#include "equality_comparable.hpp"
#include "vector.hpp"

constexpr void check_equality_comparable() noexcept
{
	using cjdb::equality_comparable;

	static_assert(equality_comparable<int>);
	static_assert(equality_comparable<double>);
	static_assert(equality_comparable<std::vector<int>>);

	using cjdb_test::equality_comparable1, cjdb_test::equality_comparable2,
	      cjdb_test::equality_comparable3, cjdb_test::equality_comparable4;

	static_assert(equality_comparable<equality_comparable1>);
	static_assert(equality_comparable<equality_comparable2>);
	static_assert(equality_comparable<equality_comparable3>);
	static_assert(equality_comparable<equality_comparable4>);

	using cjdb_test::not_equality_comparable1, cjdb_test::not_equality_comparable2,
	      cjdb_test::not_equality_comparable3;

	static_assert(not equality_comparable<void>);
	static_assert(not equality_comparable<not_equality_comparable1>);
	static_assert(not equality_comparable<not_equality_comparable2>);
	static_assert(not equality_comparable<not_equality_comparable3>);
}

constexpr void check_equality_comparable_with() noexcept
{
	using cjdb::equality_comparable_with;

	static_assert(equality_comparable_with<int, int&>);
	static_assert(equality_comparable_with<int, long>);
	static_assert(equality_comparable_with<int, long&>);
	static_assert(equality_comparable_with<int, double>);

	using cjdb_test::equality_comparable1, cjdb_test::equality_comparable2,
	      cjdb_test::equality_comparable3, cjdb_test::equality_comparable4;

	static_assert(equality_comparable_with<equality_comparable1, int>);
	static_assert(equality_comparable_with<equality_comparable1&, equality_comparable3>);
	static_assert(equality_comparable_with<equality_comparable1, equality_comparable4>);

	static_assert(not equality_comparable_with<void, int>);
	static_assert(not equality_comparable_with<std::vector<int>, int>);
	static_assert(not equality_comparable_with<std::vector<int>, std::vector<int>::size_type>);
	static_assert(not equality_comparable_with<equality_comparable1, long>);
	static_assert(not equality_comparable_with<equality_comparable1, equality_comparable2>);
	static_assert(not equality_comparable_with<equality_comparable2, equality_comparable3>);
}

int main()
{
	check_equality_comparable();
	check_equality_comparable_with();
}
