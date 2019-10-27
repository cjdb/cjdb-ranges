// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/detail/range/begin.hpp"

#include "cjdb/concepts/core/default_initializable.hpp"
#include "cjdb/concepts/callable/invocable.hpp"
#include "cjdb/detail/concepts/core/reference.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/range/unqualified_lvalue_range.hpp"
#include "cjdb/test/range/unqualified_rvalue_range.hpp"
#include <utility>

template<cjdb::detail_reference_concepts::reference T>
struct unqualified {
	using type = std::remove_reference_t<T>;

	template<typename X>
	using good_reference = std::conditional_t<std::is_lvalue_reference_v<T>, X&, X&&>;

	template<typename X>
	using faulty_reference = std::conditional_t<std::is_lvalue_reference_v<T>, X&&, X&>;

	static_assert(cjdb::ranges::detail_begin::unqualified_begin<good_reference<type>>);
	static_assert(cjdb::ranges::detail_begin::unqualified_begin<good_reference<type const>>);
	static_assert(cjdb::invocable<cjdb::ranges::detail_begin::begin_fn, good_reference<type>>);
	static_assert(cjdb::invocable<cjdb::ranges::detail_begin::begin_fn, good_reference<type const>>);

	static_assert(not cjdb::ranges::detail_begin::unqualified_begin<faulty_reference<type>>);
	static_assert(not cjdb::ranges::detail_begin::unqualified_begin<faulty_reference<type const>>);
	static_assert(not cjdb::invocable<cjdb::ranges::detail_begin::begin_fn, faulty_reference<type>>);
	static_assert(not cjdb::invocable<cjdb::ranges::detail_begin::begin_fn, faulty_reference<type const>>);

	constexpr void operator()() const
	{
		auto t = type{};
		CJDB_CONSTEXPR_CHECK(cjdb::ranges::begin(static_cast<T>(t)) == begin(static_cast<T>(t)));
		CJDB_CONSTEXPR_CHECK(cjdb::ranges::begin(static_cast<T>(t)) == static_cast<T>(t).data.begin());
		static_assert(not noexcept(cjdb::ranges::begin(static_cast<T>(t))));

		using good_ref = good_reference<type const>;
		good_ref c = static_cast<T>(t);
		CJDB_CONSTEXPR_CHECK(cjdb::ranges::begin(static_cast<good_ref>(c)) == begin(static_cast<good_ref>(c)));
		CJDB_CONSTEXPR_CHECK(cjdb::ranges::begin(static_cast<good_ref>(c)) == static_cast<T>(t).data.begin());
		static_assert(noexcept(cjdb::ranges::begin(static_cast<good_ref>(c))));

		auto copy = t;
		CJDB_CONSTEXPR_CHECK(cjdb::ranges::begin(static_cast<T>(t))
		                  != cjdb::ranges::begin(static_cast<T>(copy)));
	}
};

int main()
{
	CJDB_EVALUATE_TEST_CASE(unqualified<cjdb_test::unqualified_lvalue_range&>{});
	CJDB_EVALUATE_TEST_CASE(unqualified<cjdb_test::unqualified_lvalue_range_preferred&>{});
	CJDB_EVALUATE_TEST_CASE(unqualified<cjdb_test::unqualified_lvalue_range_private_members&>{});
	CJDB_EVALUATE_TEST_CASE(unqualified<cjdb_test::unqualified_rvalue_range&&>{});
	CJDB_EVALUATE_TEST_CASE(unqualified<cjdb_test::unqualified_rvalue_range_preferred&&>{});
	CJDB_EVALUATE_TEST_CASE(unqualified<cjdb_test::unqualified_rvalue_range_private_members&&>{});
	return ::test_result();
}
