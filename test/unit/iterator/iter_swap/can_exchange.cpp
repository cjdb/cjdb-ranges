// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/detail/iterator/iter_swap.hpp"
#include "cjdb/iterator/concepts/indirectly_swappable.hpp"

#include <array>
#include "cjdb/contracts.hpp"
#include "cjdb/iterator/reference.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/pseudoalgorithm/swap_ranges.hpp"

namespace cjdb_test {
	template<typename R>
	using iterator_t = decltype(begin(std::declval<R&>()));

	template<typename R>
	using const_iterator_t = decltype(cbegin(std::declval<R&>()));

	template<typename R>
	using reverse_iterator_t = decltype(rbegin(std::declval<R&>()));

	template<typename R>
	using const_reverse_iterator_t = decltype(crbegin(std::declval<R&>()));

	auto test_exchange = []<typename R1, typename R2>(R1 r1, R2 r2)
	requires
	         indirectly_swappable<iterator_t<R1>, iterator_t<R2>> and
	         indirectly_swappable<iterator_t<R1>, reverse_iterator_t<R2>> and
	         indirectly_swappable<reverse_iterator_t<R1>, iterator_t<R2>> and
	         indirectly_swappable<reverse_iterator_t<R1>, reverse_iterator_t<R2>> and
	         (not indirectly_swappable<iterator_t<R1>, const_iterator_t<R2>>) and
	         (not indirectly_swappable<const_iterator_t<R1>, iterator_t<R2>>) and
	         (not indirectly_swappable<const_iterator_t<R1>, const_iterator_t<R2>>) and
	         (not indirectly_swappable<const_iterator_t<R1>, reverse_iterator_t<R2>>) and
	         (not indirectly_swappable<reverse_iterator_t<R1>, const_iterator_t<R2>>) and
	         (not indirectly_swappable<reverse_iterator_t<R1>, const_reverse_iterator_t<R2>>) and
	         (not indirectly_swappable<const_reverse_iterator_t<R1>, reverse_iterator_t<R2>>) and
	         (not indirectly_swappable<const_reverse_iterator_t<R1>, const_reverse_iterator_t<R2>>)
	{

	};
} // namespace cjdb_test

int main()
{
	return ::test_result();
}
