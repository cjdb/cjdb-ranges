// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/detail/range/end.hpp"

#include "cjdb/concepts/callable/invocable.hpp"
#include "cjdb/test/constexpr_check.hpp"

class dummy {
public:
	[[nodiscard]] int* begin() noexcept;
	[[nodiscard]] int* begin() const noexcept;
	[[nodiscard]] int* end() noexcept;
	[[nodiscard]] int* end() const noexcept;
};
// NOLINTNEXTLINE(modernize-avoid-c-arrays,readability-magic-numbers)
static_assert(not cjdb::invocable<cjdb::ranges::detail_end::end_fn, double[321]>);

// checks that unbounded arrays can't be called using ranges::end
// NOLINTNEXTLINE(modernize-avoid-c-arrays)
static_assert(not cjdb::invocable<cjdb::ranges::detail_end::end_fn, long(&)[]>);

#include <iostream>

template<typename T, std::size_t size>
struct lvalue_array {
	constexpr void operator()() const noexcept
	{
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		static_assert(cjdb::invocable<cjdb::ranges::detail_end::end_fn, T(&)[size]>);

		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		static_assert(std::is_nothrow_invocable_v<cjdb::ranges::detail_end::end_fn, T(&)[size]>);

		T array[size]{}; // NOLINT(modernize-avoid-c-arrays)
		auto* const decay = array + size;
		CJDB_CONSTEXPR_CHECK(cjdb::ranges::end(array) == decay);
	}
};

int main()
{
	CJDB_EVALUATE_TEST_CASE(lvalue_array<int, 30>{});    // NOLINT(readability-magic-numbers)
	CJDB_EVALUATE_TEST_CASE(lvalue_array<double, 43>{}); // NOLINT(readability-magic-numbers)
	CJDB_EVALUATE_TEST_CASE(lvalue_array<dummy, 210>{}); // NOLINT(readability-magic-numbers)

	// NOLINTNEXTLINE(modernize-avoid-c-arrays,readability-magic-numbers)
	CJDB_EVALUATE_TEST_CASE(lvalue_array<int[22], 30>{});

	return ::test_result();
}
