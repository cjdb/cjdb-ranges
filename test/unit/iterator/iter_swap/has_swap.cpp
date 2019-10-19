// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/detail/iterator/iter_swap.hpp"
#include "cjdb/iterator/concepts/indirectly_swappable.hpp"

#include <array>
#include "cjdb/contracts.hpp"
#include "cjdb/iterator/reference.hpp"
#include "cjdb/test/constexpr_check.hpp"

namespace cjdb_test {
	auto swap_ranges = [](auto& r1, auto& r2) {
		auto first1 = r1.begin();
		auto first2 = r2.begin();
		for (; first1 != r1.end() and first2 != r2.end(); ++first1, (void)++first2) {
			cjdb::ranges::iter_swap(first1, first2);
		}
	};

	auto homogeneous_swapping = []<cjdb::equality_comparable R>(R r1, R r2)
	requires cjdb::copyable<cjdb::iter_value_t<R>>
	{
		using iterator               = typename std::remove_cvref_t<R>::iterator;
		using const_iterator         = typename std::remove_cvref_t<R>::const_iterator;
		using reverse_iterator       = typename std::remove_cvref_t<R>::reverse_iterator;
		using const_reverse_iterator = typename std::remove_cvref_t<R>::const_reverse_iterator;

		using cjdb::ranges::detail_iter_swap::swappable_references;
		static_assert(swappable_references<iterator, iterator>);
		static_assert(swappable_references<iterator, reverse_iterator>);
		static_assert(swappable_references<reverse_iterator, iterator>);

		static_assert(cjdb::indirectly_swappable<iterator, iterator>);
		static_assert(cjdb::indirectly_swappable<iterator, reverse_iterator>);
		static_assert(cjdb::indirectly_swappable<reverse_iterator, iterator>);
		static_assert(cjdb::indirectly_swappable<reverse_iterator, reverse_iterator>);

		if constexpr (not cjdb::readable<cjdb::iter_reference_t<iterator>>) {
			static_assert(not swappable_references<cjdb::iter_value_t<iterator>,
			                                       cjdb::iter_value_t<iterator>>);
			static_assert(not swappable_references<cjdb::iter_value_t<iterator>, iterator>);
			static_assert(not swappable_references<iterator, cjdb::iter_value_t<iterator>>);
		}

		static_assert(not swappable_references<iterator, const_iterator>);
		static_assert(not swappable_references<const_iterator, iterator>);

		static_assert(not swappable_references<iterator, const_reverse_iterator>);
		static_assert(not swappable_references<const_reverse_iterator, iterator>);
		static_assert(not swappable_references<reverse_iterator, const_iterator>);
		static_assert(not swappable_references<const_iterator, reverse_iterator>);
		static_assert(not swappable_references<reverse_iterator, const_reverse_iterator>);
		static_assert(not swappable_references<const_reverse_iterator, reverse_iterator>);

		static_assert(not cjdb::indirectly_swappable<iterator, const_iterator>);
		static_assert(not cjdb::indirectly_swappable<const_iterator, iterator>);
		static_assert(not cjdb::indirectly_swappable<reverse_iterator, const_iterator>);
		static_assert(not cjdb::indirectly_swappable<const_iterator, reverse_iterator>);
		static_assert(not cjdb::indirectly_swappable<const_iterator, const_iterator>);

		static_assert(not cjdb::indirectly_swappable<iterator, const_reverse_iterator>);
		static_assert(not cjdb::indirectly_swappable<const_reverse_iterator, iterator>);
		static_assert(not cjdb::indirectly_swappable<reverse_iterator, const_reverse_iterator>);
		static_assert(not cjdb::indirectly_swappable<const_iterator, const_reverse_iterator>);
		static_assert(not cjdb::indirectly_swappable<const_reverse_iterator, const_reverse_iterator>);

		auto const expected = std::array{r1, r2};
		CJDB_ASSERT(r1 == expected.front());
		CJDB_ASSERT(r2 == expected.back());
		cjdb_test::swap_ranges(r1, r2);
		CJDB_CONSTEXPR_CHECK(r2 == expected.front());
		CJDB_CONSTEXPR_CHECK(r1 == expected.back());
	};
} // namespace cjdb_test

int main()
{
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::homogeneous_swapping,
	                          std::array{0, 0, 0, 0},
	                          std::array{0, 0, 0, 0});
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::homogeneous_swapping,
	                          std::array{12, 16},
	                          std::array{37, 41});
	CJDB_EVALUATE_TEST_CASE_N(cjdb_test::homogeneous_swapping,
	                          std::array{43.21, 109.5, 892.25, 45.5454e100}, // NOLINT(readability-magic-numbers)
	                          std::array{345.0, 215.5, -16.32, -640e-21});   // NOLINT(readability-magic-numbers)
	return ::test_result();
}
