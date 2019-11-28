// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/concepts/comparison/three_way_comparable.hpp"

#include <version>
#if defined(__cpp_lib_three_way_comparison) and __cpp_lib_three_way_comparison >= 201711

#include "cjdb/concepts/core/common_reference_with.hpp"
#include "cjdb/concepts/core/convertible_to.hpp"
#include "three_way_comparable.hpp"

template<typename T, typename Cat, bool expected>
constexpr void check_three_way_comparable_impl() noexcept
{
	static_assert(cjdb::three_way_comparable<T, Cat> == expected);
}

template<typename T, cjdb::common_reference_with<T> U, typename Cat, bool expected>
constexpr void check_three_way_comparable_with_impl() noexcept
{
	static_assert(cjdb::three_way_comparable_with<T, U, Cat> == expected);
}

template<typename T, cjdb::convertible_to<std::partial_ordering> Cat>
constexpr void check_three_way_comparable() noexcept
{
	check_three_way_comparable_impl<T, std::partial_ordering, true>();
	check_three_way_comparable_with_impl<T, T, std::partial_ordering, true>();

	check_three_way_comparable_impl<T, std::weak_ordering,
	                                cjdb::convertible_to<Cat, std::weak_ordering>>();
	check_three_way_comparable_with_impl<T, T, std::weak_ordering,
	                                cjdb::convertible_to<Cat, std::weak_ordering>>();

	check_three_way_comparable_impl<T, std::strong_ordering,
	                                cjdb::convertible_to<Cat, std::strong_ordering>>();
	check_three_way_comparable_with_impl<T, T, std::strong_ordering,
	                                cjdb::convertible_to<Cat, std::strong_ordering>>();

	check_three_way_comparable_impl<T, int, false>();
	check_three_way_comparable_with_impl<T, T, int, false>();
}

template<cjdb::common_reference_with<cjdb_test::strong_three_way const&> T>
constexpr void check_not_three_way_comparable() noexcept
{
	check_three_way_comparable_impl<T, std::partial_ordering, false>();
	check_three_way_comparable_with_impl<T, T, std::partial_ordering, false>();

	check_three_way_comparable_impl<T, std::weak_ordering, false>();
	check_three_way_comparable_with_impl<T, T, std::weak_ordering, false>();

	check_three_way_comparable_impl<T, std::strong_ordering, false>();
	check_three_way_comparable_with_impl<T, T, std::strong_ordering, false>();

	check_three_way_comparable_impl<T, int, false>();
	check_three_way_comparable_with_impl<T, T, int, false>();

	check_three_way_comparable_with_impl<T, cjdb_test::strong_three_way, std::partial_ordering, false>();
	check_three_way_comparable_with_impl<cjdb_test::strong_three_way, T, std::partial_ordering, false>();

	check_three_way_comparable_with_impl<T, cjdb_test::strong_three_way, std::weak_ordering, false>();
	check_three_way_comparable_with_impl<cjdb_test::strong_three_way, T, std::weak_ordering, false>();

	check_three_way_comparable_with_impl<T, cjdb_test::strong_three_way, std::strong_ordering, false>();
	check_three_way_comparable_with_impl<cjdb_test::strong_three_way, T, std::strong_ordering, false>();
}

template<typename T, typename U, cjdb::convertible_to<std::partial_ordering> Cat>
constexpr void check_three_way_comparable_with() noexcept
{
	check_three_way_comparable_impl<T, std::partial_ordering, true>();
	check_three_way_comparable_impl<U, std::partial_ordering, true>();

	check_three_way_comparable_with_impl<T, U, std::partial_ordering, true>();
	check_three_way_comparable_with_impl<U, T, std::partial_ordering, true>();

	check_three_way_comparable_with_impl<T, U, std::weak_ordering,
	                                     cjdb::convertible_to<Cat, std::weak_ordering>>();

	check_three_way_comparable_with_impl<T, U, std::strong_ordering,
	                                     cjdb::convertible_to<Cat, std::strong_ordering>>();

	check_three_way_comparable_with_impl<T, T, int, false>();
	check_three_way_comparable_with_impl<T, U, int, false>();
	check_three_way_comparable_with_impl<U, T, int, false>();
	check_three_way_comparable_with_impl<U, U, int, false>();
}

int main()
{
	{ // three-way comparable
		check_three_way_comparable<cjdb_test::auto_three_way, std::strong_ordering>();
		check_three_way_comparable<cjdb_test::partial_three_way, std::partial_ordering>();
		check_three_way_comparable<cjdb_test::weak_three_way, std::weak_ordering>();
		check_three_way_comparable<cjdb_test::strong_three_way, std::strong_ordering>();
	}
	{ // not three-way comparable
		check_not_three_way_comparable<cjdb_test::int_three_way>();
		check_not_three_way_comparable<cjdb_test::partial_three_way_bad_eq>();
		check_not_three_way_comparable<cjdb_test::weak_three_way_bad_eq>();
		check_not_three_way_comparable<cjdb_test::strong_three_way_bad_eq>();

		check_not_three_way_comparable<cjdb_test::partial_missing_equal_to>();
		check_not_three_way_comparable<cjdb_test::weak_missing_equal_to>();
		check_not_three_way_comparable<cjdb_test::strong_missing_equal_to>();

		check_not_three_way_comparable<cjdb_test::partial_missing_not_equal_to>();
		check_not_three_way_comparable<cjdb_test::weak_missing_not_equal_to>();
		check_not_three_way_comparable<cjdb_test::strong_missing_not_equal_to>();

		check_not_three_way_comparable<cjdb_test::partial_missing_less>();
		check_not_three_way_comparable<cjdb_test::weak_missing_less>();
		check_not_three_way_comparable<cjdb_test::strong_missing_less>();

		check_not_three_way_comparable<cjdb_test::partial_missing_less_equal>();
		check_not_three_way_comparable<cjdb_test::weak_missing_less_equal>();
		check_not_three_way_comparable<cjdb_test::strong_missing_less_equal>();

		check_not_three_way_comparable<cjdb_test::partial_missing_greater>();
		check_not_three_way_comparable<cjdb_test::weak_missing_greater>();
		check_not_three_way_comparable<cjdb_test::strong_missing_greater>();

		check_not_three_way_comparable<cjdb_test::partial_missing_greater_equal>();
		check_not_three_way_comparable<cjdb_test::weak_missing_greater_equal>();
		check_not_three_way_comparable<cjdb_test::strong_missing_greater_equal>();
	}
	{ // cross-type three-way comparable
		check_three_way_comparable_with<cjdb_test::auto_three_way, cjdb_test::partial_three_way, std::partial_ordering>();

		// check that when `t <=> u` and `u <=> t` have different types, this still holds
		check_three_way_comparable_with<cjdb_test::partial_three_way, cjdb_test::weak_three_way, std::partial_ordering>();
	}
}
#else
int main() {}
#endif
