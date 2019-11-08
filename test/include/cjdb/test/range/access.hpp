// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_RANGE_ACCESS_HPP
#define CJDB_TEST_RANGE_ACCESS_HPP

#include "cjdb/concepts/core/default_initializable.hpp"
#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/concepts/callable/invocable.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/range/bad_lvalue_range.hpp"
#include "cjdb/test/range/bad_rvalue_range.hpp"
#include "cjdb/test/range/lvalue_range_with_members.hpp"
#include "cjdb/test/range/unqualified_lvalue_range.hpp"
#include "cjdb/test/range/unqualified_rvalue_range.hpp"
#include <iterator>
#include <type_traits>
#include <utility>

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

namespace cjdb_test {
	class dummy {
	public:
		[[nodiscard]] constexpr int* begin() noexcept
		{
			return &second_;
		}

		[[nodiscard]] constexpr int end() noexcept
		{
			return first_;
		}
	private:
		int first_ = 0;
		int second_ = 54; // NOLINT(readability-magic-numbers)
	};
} // namespace cjdb_test

#define DEFINE_CHECK_FOR_C_ARRAY_ACCESS(cpo)                                                                                                             \
static_assert(not cjdb::invocable<cjdb::ranges::detail_##cpo::cpo##_fn, double[321]>); /* NOLINT(modernize-avoid-c-arrays,readability-magic-numbers) */  \
                                                                                                                                                         \
/* checks that unbounded arrays can't be called using the CPO */                                                                                         \
static_assert(not cjdb::invocable<cjdb::ranges::detail_##cpo::cpo##_fn, long(&)[]>); /* NOLINT(modernize-avoid-c-arrays) */                              \
                                                                                                                                                         \
template<typename T, std::size_t size>                                                                                                                   \
struct lvalue_array {                                                                                                                                    \
	constexpr void operator()() const noexcept                                                                                                            \
	{                                                                                                                                                     \
		static_assert(cjdb::invocable<cjdb::ranges::detail_##cpo::cpo##_fn, T(&)[size]>); /* NOLINT(modernize-avoid-c-arrays) */                           \
		static_assert(std::is_nothrow_invocable_v<cjdb::ranges::detail_##cpo::cpo##_fn, T(&)[size]>); /* NOLINT(modernize-avoid-c-arrays) */               \
                                                                                                                                                         \
		T array[size]{}; /* NOLINT(modernize-avoid-c-arrays) */                                                                                            \
		CJDB_CONSTEXPR_CHECK(cjdb::ranges::cpo(array) == std::cpo(array));                                                                                 \
	}                                                                                                                                                     \
}

#define DEFINE_CHECK_FOR_FAULTY_ACCESS(cpo, base_cpo)                                     \
auto faulty_##cpo = []<typename T>(T) {                                                   \
	static_assert(not cjdb::ranges::detail_##base_cpo::member_##base_cpo<T&>);             \
	static_assert(not cjdb::ranges::detail_##base_cpo::member_##base_cpo<T const&>);       \
	static_assert(not cjdb::ranges::detail_##base_cpo::member_##base_cpo<T&&>);            \
	static_assert(not cjdb::ranges::detail_##base_cpo::member_##base_cpo<T const&&>);      \
	                                                                                       \
	static_assert(not cjdb::ranges::detail_##base_cpo::unqualified_##base_cpo<T&>);        \
	static_assert(not cjdb::ranges::detail_##base_cpo::unqualified_##base_cpo<T const&>);  \
	static_assert(not cjdb::ranges::detail_##base_cpo::unqualified_##base_cpo<T&&>);       \
	static_assert(not cjdb::ranges::detail_##base_cpo::unqualified_##base_cpo<T const&&>); \
	                                                                                       \
	static_assert(not cjdb::invocable<cjdb::ranges::detail_##cpo::cpo##_fn, T&>);          \
	static_assert(not cjdb::invocable<cjdb::ranges::detail_##cpo::cpo##_fn, T const&>);    \
	static_assert(not cjdb::invocable<cjdb::ranges::detail_##cpo::cpo##_fn, T>);           \
	static_assert(not cjdb::invocable<cjdb::ranges::detail_##cpo::cpo##_fn, T const>);     \
}

#define DEFINE_CHECK_FOR_MEMBER_ACCESS(cpo, base_cpo)                                                                                           \
/* NOLINTNEXTLINE(readability-magic-numbers) */                                                                                                 \
static_assert(cjdb::ranges::detail_##base_cpo::member_##base_cpo<std::array<int, 100>&>);                                                       \
/* NOLINTNEXTLINE(readability-magic-numbers) */                                                                                                 \
static_assert(cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::array<int, 100>&>);                                          \
static_assert(cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::map<int, double>&>);                                         \
static_assert(cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::map<int, double> const&>);                                   \
static_assert(cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::multimap<int, double>&>);                                    \
static_assert(cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::multimap<int, double> const&>);                              \
static_assert(cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::multiset<std::array<int, 1>>&>);                             \
static_assert(cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::multiset<std::array<int, 1>> const&>);                       \
static_assert(cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::set<std::array<int, 1>>&>);                                  \
static_assert(cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::set<std::array<int, 1>> const&>);                            \
static_assert(cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::unordered_map<int, int>&>);                                  \
static_assert(cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::unordered_map<int, int> const&>);                            \
static_assert(cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::unordered_multimap<int, int>&>);                             \
static_assert(cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::unordered_multimap<int, int> const&>);                       \
static_assert(cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::unordered_set<float>&>);                                     \
static_assert(cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::unordered_set<float> const&>);                               \
static_assert(cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::unordered_multiset<float>&>);                                \
static_assert(cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::unordered_multiset<float> const&>);                          \
                                                                                                                                                \
static_assert(not cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::map<int, double>&&>);                                    \
static_assert(not cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::multimap<int, double>&&>);                               \
static_assert(not cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::multiset<std::array<int, 1>>&&>);                        \
static_assert(not cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::set<std::array<int, 1>>&&>);                             \
static_assert(not cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::unordered_map<int, int>&&>);                             \
static_assert(not cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::unordered_multimap<int, int>&&>);                        \
static_assert(not cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::unordered_set<float>&&>);                                \
static_assert(not cjdb::invocable<cjdb::ranges::detail_##base_cpo::base_cpo##_fn, std::unordered_multiset<float>&&>);                           \
                                                                                                                                                \
template<cjdb::default_initializable Range>                                                                                                     \
struct member_##cpo {                                                                                                                           \
	void operator()() const noexcept                                                                                                             \
	{                                                                                                                                            \
		static_assert(cjdb::ranges::detail_##base_cpo::member_##base_cpo<Range&>);                                                                \
		static_assert(cjdb::invocable<cjdb::ranges::detail_##cpo::cpo##_fn, Range&>);                                                             \
		static_assert(cjdb::input_or_output_iterator<std::invoke_result_t<cjdb::ranges::detail_##cpo::cpo##_fn, Range&>>);                        \
		{                                                                                                                                         \
			auto r = Range{};                                                                                                                      \
			/* if we're using cr?(begin|end|data), we need to be checking against a reference-to-const */                                          \
			using range_t = std::conditional_t<cjdb::same_as<decltype(cjdb::ranges::cpo), decltype(cjdb::ranges::base_cpo)>, Range, Range const>;  \
			static_assert(noexcept(cjdb::ranges::cpo(r)) == noexcept(static_cast<range_t&>(r).base_cpo()));                                        \
		}                                                                                                                                         \
                                                                                                                                                \
		static_assert(cjdb::ranges::detail_##base_cpo::member_##base_cpo<Range const&>);                                                          \
		static_assert(cjdb::invocable<cjdb::ranges::detail_##cpo::cpo##_fn, Range const&>);                                                       \
		static_assert(cjdb::input_or_output_iterator<std::invoke_result_t<cjdb::ranges::detail_##cpo::cpo##_fn, Range const&>>);                  \
		{                                                                                                                                         \
			auto const r = Range{};                                                                                                                \
			static_assert(noexcept(cjdb::ranges::cpo(r)));                                                                                         \
		}                                                                                                                                         \
                                                                                                                                                \
		static_assert(not cjdb::invocable<cjdb::ranges::detail_##cpo::cpo##_fn, Range>);                                                          \
		static_assert(not cjdb::invocable<cjdb::ranges::detail_##cpo::cpo##_fn, Range&&>);                                                        \
                                                                                                                                                \
		if (not std::is_constant_evaluated()) { /* TODO(@cjdb): remove me once std::vector and std::string are constexpr */                       \
			constexpr auto container_size = 100;                                                                                                   \
			auto r = Range(container_size, typename Range::value_type{});                                                                          \
			static_assert(cjdb::equality_comparable<decltype(r.base_cpo())>);                                                                      \
			CHECK(cjdb::ranges::cpo(r) == std::cpo(r));                                                                                            \
		}                                                                                                                                         \
	}                                                                                                                                            \
}

#define DEFINE_CHECK_FOR_UNQUALIFIED_ACCESS(cpo, base_cpo, is_const)                                              \
template<cjdb::detail_reference_concepts::reference T>                                                            \
struct unqualified {                                                                                              \
	using type = std::remove_reference_t<T>;                                                                       \
	                                                                                                               \
	template<typename X>                                                                                           \
	using good_reference = std::conditional_t<std::is_lvalue_reference_v<T>, X&, X&&>;                             \
	                                                                                                               \
	template<typename X>                                                                                           \
	using faulty_reference = std::conditional_t<std::is_lvalue_reference_v<T>, X&&, X&>;                           \
	                                                                                                               \
	static_assert(cjdb::ranges::detail_##base_cpo::unqualified_##base_cpo<good_reference<type>>);                  \
	static_assert(cjdb::ranges::detail_##base_cpo::unqualified_##base_cpo<good_reference<type const>>);            \
	static_assert(cjdb::invocable<cjdb::ranges::detail_##cpo::cpo##_fn, good_reference<type>>);                    \
	static_assert(cjdb::invocable<cjdb::ranges::detail_##cpo::cpo##_fn, good_reference<type const>>);              \
	                                                                                                               \
	static_assert(not cjdb::ranges::detail_##base_cpo::unqualified_##base_cpo<faulty_reference<type>>);            \
	static_assert(not cjdb::ranges::detail_##base_cpo::unqualified_##base_cpo<faulty_reference<type const>>);      \
	static_assert(not cjdb::invocable<cjdb::ranges::detail_##cpo::cpo##_fn, faulty_reference<type>>);              \
	static_assert(not cjdb::invocable<cjdb::ranges::detail_##cpo::cpo##_fn, faulty_reference<type const>>);        \
	                                                                                                               \
	constexpr void operator()() const                                                                              \
	{                                                                                                              \
		auto t = type{};                                                                                            \
		CJDB_CONSTEXPR_CHECK(cjdb::ranges::cpo(std::forward<T>(t)) == base_cpo(std::forward<T>(t)));                \
		CJDB_CONSTEXPR_CHECK(cjdb::ranges::cpo(std::forward<T>(t)) == std::forward<T>(t).data.cpo());               \
		static_assert(noexcept(cjdb::ranges::cpo(std::forward<T>(t))) == (is_const));                               \
		                                                                                                            \
		using good_ref = good_reference<type const>;                                                                \
		good_ref c = std::forward<T>(t);                                                                            \
		CJDB_CONSTEXPR_CHECK(cjdb::ranges::cpo(std::forward<good_ref>(c)) == base_cpo(std::forward<good_ref>(c)));  \
		CJDB_CONSTEXPR_CHECK(cjdb::ranges::cpo(std::forward<good_ref>(c)) == std::forward<T>(t).data.cpo());        \
		static_assert(noexcept(cjdb::ranges::cpo(std::forward<good_ref>(c))));                                      \
		                                                                                                            \
		auto copy = t;                                                                                              \
		CJDB_CONSTEXPR_CHECK(cjdb::ranges::cpo(std::forward<T>(t)) != cjdb::ranges::cpo(std::forward<T>(copy)));    \
	}                                                                                                              \
}

#define CHECK_RANGE_ACCESS(cpo, base_cpo, is_const)                                                         \
namespace cjdb_test {                                                                                       \
	DEFINE_CHECK_FOR_FAULTY_ACCESS(cpo, base_cpo);                                                           \
	DEFINE_CHECK_FOR_C_ARRAY_ACCESS(cpo);                                                                    \
	DEFINE_CHECK_FOR_MEMBER_ACCESS(cpo, base_cpo);                                                           \
	DEFINE_CHECK_FOR_UNQUALIFIED_ACCESS(cpo, base_cpo, is_const);                                            \
} /* namespace cjdb_test */                                                                                 \
                                                                                                            \
int main()                                                                                                  \
{                                                                                                           \
	/* NOLINTNEXTLINE(readability-magic-numbers) */                                                          \
	CJDB_EVALUATE_TEST_CASE(cjdb_test::lvalue_array<int, 30>{});                                             \
	/* NOLINTNEXTLINE(readability-magic-numbers) */                                                          \
	CJDB_EVALUATE_TEST_CASE(cjdb_test::lvalue_array<double, 43>{});                                          \
	/* NOLINTNEXTLINE(readability-magic-numbers) */                                                          \
	CJDB_EVALUATE_TEST_CASE(cjdb_test::lvalue_array<cjdb_test::dummy, 210>{});                               \
	                                                                                                         \
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::faulty_##cpo, cjdb_test::bad_lvalue_range_unqualified{});           \
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::faulty_##cpo, cjdb_test::bad_lvalue_range_preferred{});             \
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::faulty_##cpo, cjdb_test::bad_lvalue_range_private_members{});       \
	                                                                                                         \
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::faulty_##cpo, cjdb_test::bad_rvalue_range_members{});               \
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::faulty_##cpo, cjdb_test::bad_rvalue_range_unqualified{});           \
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::faulty_##cpo, cjdb_test::bad_rvalue_range_preferred{});             \
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::faulty_##cpo, cjdb_test::bad_rvalue_range_private_members{});       \
	                                                                                                         \
	cjdb_test::member_##cpo<std::deque<double(*)()>>{}();                                                    \
	cjdb_test::member_##cpo<std::forward_list<int>>{}();                                                     \
	cjdb_test::member_##cpo<std::list<std::vector<int>>>{}();                                                \
	cjdb_test::member_##cpo<std::vector<std::set<int>>>{}();                                                 \
	cjdb_test::member_##cpo<cjdb_test::lvalue_range_with_members>{}();                                       \
	cjdb_test::member_##cpo<cjdb_test::lvalue_range_with_members_and_unqualified_friends>{}();               \
	                                                                                                         \
	CJDB_EVALUATE_TEST_CASE(cjdb_test::unqualified<cjdb_test::unqualified_lvalue_range&>{});                 \
	CJDB_EVALUATE_TEST_CASE(cjdb_test::unqualified<cjdb_test::unqualified_lvalue_range_preferred&>{});       \
	CJDB_EVALUATE_TEST_CASE(cjdb_test::unqualified<cjdb_test::unqualified_lvalue_range_private_members&>{}); \
	CJDB_EVALUATE_TEST_CASE(cjdb_test::unqualified<cjdb_test::unqualified_rvalue_range&&>{});                \
	CJDB_EVALUATE_TEST_CASE(cjdb_test::unqualified<cjdb_test::unqualified_rvalue_range_preferred&&>{});      \
	CJDB_EVALUATE_TEST_CASE(cjdb_test::unqualified<cjdb_test::unqualified_rvalue_range_private_members&&>{});\
	                                                                                                         \
	return ::test_result();                                                                                  \
}

#endif // CJDB_TEST_RANGE_ACCESS_HPP
