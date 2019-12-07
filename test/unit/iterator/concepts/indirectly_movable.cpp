// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-.0 WITH LLVM-exception
//
#include "cjdb/iterator/concepts/indirectly_movable.hpp"

#include "cjdb/test/iterator/read_write.hpp"

template<typename T, typename U = T, bool expected = true>
constexpr void check_indirectly_movable()
{
	static_assert(cjdb::indirectly_movable<T, U> == expected);
	static_assert(cjdb::indirectly_movable<T, U const> == expected);
	static_assert(cjdb::indirectly_movable<T const, U> == expected);
	static_assert(cjdb::indirectly_movable<T, U const> == expected);
	static_assert(cjdb::indirectly_movable<T const, U const> == expected);
}

int main()
{
	check_indirectly_movable<cjdb_test::traditional_indirection>();
	check_indirectly_movable<cjdb_test::traditional_indirection, int*>();
	check_indirectly_movable<cjdb_test::traditional_indirection, float*>();
	check_indirectly_movable<int*, cjdb_test::traditional_indirection>();
	check_indirectly_movable<float*, cjdb_test::traditional_indirection>();

	check_indirectly_movable<cjdb_test::alternative_indirection>();
	check_indirectly_movable<cjdb_test::alternative_indirection, int*>();
	check_indirectly_movable<cjdb_test::alternative_indirection, float*>();
	check_indirectly_movable<int*, cjdb_test::alternative_indirection>();
	check_indirectly_movable<float*, cjdb_test::alternative_indirection>();

	check_indirectly_movable<cjdb_test::proxy_indirection, int*, true>();

	check_indirectly_movable<int, int, false>();
	check_indirectly_movable<cjdb_test::traditional_indirection, int const*, false>();
	check_indirectly_movable<cjdb_test::traditional_indirection, float const*, false>();
	check_indirectly_movable<cjdb_test::proxy_indirection, cjdb_test::proxy_indirection, false>();
	check_indirectly_movable<int*, cjdb_test::proxy_indirection, false>();
	check_indirectly_movable<cjdb_test::read_only_indirection, cjdb_test::read_only_indirection, false>();
	check_indirectly_movable<cjdb_test::missing_dereference, cjdb_test::missing_dereference, false>();
}
