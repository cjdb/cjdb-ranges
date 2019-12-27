// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/range/access/size.hpp"
#include "cjdb/range/concepts/sized_range.hpp"

#include <array>
#include "cjdb/concepts/core/integral.hpp"
#include "cjdb/concepts/callable/invocable.hpp"
#include "cjdb/iterator/concepts/iterator.hpp"
#include "cjdb/range/concepts/refinements.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/range/unqualified_lvalue_range.hpp"
#include "cjdb/test/range/unqualified_rvalue_range.hpp"
#include <forward_list>
#include <list>
#include <type_traits>
#include <utility>
#include <vector>

namespace cjdb_test {
	namespace ranges = cjdb::ranges;

	template<typename T>
	constexpr void check_not_sizeable() noexcept
	{
		static_assert(not cjdb::invocable<ranges::detail_size::size_fn, T&>);
		static_assert(not cjdb::invocable<ranges::detail_size::size_fn, T const&>);
		static_assert(not cjdb::invocable<ranges::detail_size::size_fn, T&&>);
		static_assert(not cjdb::invocable<ranges::detail_size::size_fn, T const&&>);
		static_assert(not ranges::sized_range<T>);
		static_assert(not ranges::sized_range<T&>);
		static_assert(not ranges::sized_range<T&&>);
		static_assert(not ranges::sized_range<T const&>);
		static_assert(not ranges::sized_range<T const&&>);
	}

	template<std::size_t expected_size>
	constexpr void check_array() noexcept
	{
		using array_t = int[expected_size]; // NOLINT(modernize-avoid-c-arrays)

		static_assert(cjdb::invocable<ranges::detail_size::size_fn, array_t>);
		static_assert(ranges::sized_range<array_t>);

		static_assert(std::is_nothrow_invocable_v<ranges::detail_size::size_fn, array_t>);
		static_assert(cjdb::unsigned_integral<std::invoke_result_t<ranges::detail_size::size_fn, array_t>>);

		array_t x{};
		CJDB_CONSTEXPR_CHECK(ranges::size(x) == expected_size);
	};

	template<typename T>
	using size_type_t = typename std::remove_cvref_t<T>::size_type;

	template<typename T>
	constexpr auto member(size_type_t<T> const expected_size) noexcept -> void
	{
		using range_t = std::remove_cvref_t<T>;
		auto t1 = range_t(expected_size);
		auto t2 = range_t(expected_size);
		auto t3 = range_t(expected_size);

		static_assert(cjdb::invocable<ranges::detail_size::size_fn, T>);
		static_assert(ranges::sized_range<T>);

		static_assert(ranges::detail_size::member_size<T>);
		static_assert(noexcept(ranges::size(t1)) == noexcept(t1.size()));
		static_assert(noexcept(ranges::size(std::as_const(t1))) == noexcept(std::as_const(t1).size()));
		CJDB_CONSTEXPR_CHECK(ranges::size(std::forward<T>(t1)) == std::forward<T>(t2).size());

		CJDB_CONSTEXPR_CHECK(ranges::size(std::forward<T>(t3)) == expected_size);
	}

	template<typename T>
	constexpr auto unqualified() noexcept -> void
	{
		using range_t = std::remove_reference_t<T>;
		auto t1 = range_t{};
		auto t2 = range_t{};
		auto t3 = range_t{};

		static_assert(cjdb::invocable<ranges::detail_size::size_fn, T>);
		if constexpr (not cjdb::same_as<range_t&&, T>) {
			static_assert(ranges::sized_range<range_t>);
		}
		else {
			static_assert(not ranges::range<range_t>);
			static_assert(not ranges::sized_range<range_t>);
		}

		static_assert(ranges::detail_size::unqualified_size<T>);
		static_assert(noexcept(ranges::size(std::forward<T>(t1))) == noexcept(size(std::forward<T>(t1))));
		CJDB_CONSTEXPR_CHECK(ranges::size(std::forward<T>(t1)) == size(std::forward<T>(t2)));
		CJDB_CONSTEXPR_CHECK(ranges::size(std::forward<T>(t3)) == t3.data_.size());
	}

	template<ranges::forward_range R>
	requires ranges::disable_sized_range<R> and
	         cjdb::sized_sentinel_for<ranges::sentinel_t<R>, ranges::iterator_t<R>> and
	         requires(R const r) { r.size(); }
	constexpr auto disabled_size(size_type_t<R> const size) noexcept -> void
	{
		static_assert(not ranges::detail_size::member_size<R>);
		static_assert(not ranges::detail_size::unqualified_size<R>);
		static_assert(cjdb::invocable<ranges::detail_size::size_fn, R>);
		static_assert(ranges::sized_range<R>);

		static_assert(cjdb::unsigned_integral<std::invoke_result_t<ranges::detail_size::size_fn, R>>);

		auto r = R(size);
		static_assert(noexcept(ranges::size(r)) == noexcept(ranges::end(r) - ranges::begin(r)));
		static_assert(noexcept(ranges::size(static_cast<R const&>(r))) ==
		              noexcept(ranges::end(static_cast<R const&>(r)) - ranges::begin(static_cast<R const&>(r))));
		CJDB_CONSTEXPR_CHECK(ranges::size(r) == size);
		CJDB_CONSTEXPR_CHECK(ranges::size(r) == static_cast<decltype(size)>(ranges::end(r) - ranges::begin(r)));
	}

	template<typename F>
	constexpr auto check(F f) noexcept
	{
		f(0);     // NOLINT(readability-magic-numbers)
		f(1);     // NOLINT(readability-magic-numbers)
		f(2);     // NOLINT(readability-magic-numbers)
		f(454);   // NOLINT(readability-magic-numbers)
		f(45487); // NOLINT(readability-magic-numbers)
	}

	template<template<bool> typename T, template<typename> typename add_reference>
	constexpr auto check_unqualified() noexcept
	{
		cjdb_test::unqualified<typename add_reference<T<false>>::type>();
		static_assert(not cjdb::ranges::detail_size::unqualified_size<typename add_reference<T<false> const>::type>);

		cjdb_test::unqualified<typename add_reference<T<true>>::type>();
		cjdb_test::unqualified<typename add_reference<T<true> const>::type>();
	}
} // namespace cjdb_test

namespace cjdb::ranges {
	template<>
	inline constexpr auto disable_sized_range<std::vector<double>> = true;

	template<>
	inline constexpr auto disable_sized_range<std::list<double>> = true;
} // namespace cjdb::ranges

int main()
{
	cjdb_test::check_not_sizeable<std::forward_list<int>>();
	cjdb_test::check_not_sizeable<std::forward_list<double>>();
	cjdb_test::check_not_sizeable<std::list<double>>();

	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::check_array<1>);    // NOLINT(readability-magic-numbers)
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::check_array<2>);    // NOLINT(readability-magic-numbers)
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::check_array<3>);    // NOLINT(readability-magic-numbers)
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::check_array<214>);  // NOLINT(readability-magic-numbers)
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::check_array<9834>); // NOLINT(readability-magic-numbers)

	// TODO(@cjdb): apply EVALUATE_TEST_CASE_N when std::vector is made constexpr
	cjdb_test::check(cjdb_test::member<std::vector<int>>);
	cjdb_test::check(cjdb_test::member<std::list<int>>);

	cjdb_test::check_unqualified<cjdb_test::unqualified_lvalue_range,
	                             std::add_lvalue_reference>();
	cjdb_test::check_unqualified<cjdb_test::unqualified_lvalue_range_preferred,
	                             std::add_lvalue_reference>();
	cjdb_test::check_unqualified<cjdb_test::unqualified_lvalue_range_private_members,
	                             std::add_lvalue_reference>();
	cjdb_test::check_unqualified<cjdb_test::unqualified_rvalue_range,
	                             std::add_rvalue_reference>();
	cjdb_test::check_unqualified<cjdb_test::unqualified_rvalue_range_preferred,
	                             std::add_rvalue_reference>();
	cjdb_test::check_unqualified<cjdb_test::unqualified_rvalue_range_private_members,
	                             std::add_rvalue_reference>();

	static_assert(cjdb::ranges::disable_sized_range<std::vector<double>>);
	cjdb_test::check(cjdb_test::disabled_size<std::vector<double>>);

	return ::test_result();
}
