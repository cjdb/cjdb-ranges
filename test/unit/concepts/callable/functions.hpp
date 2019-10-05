// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_CONCEPTS_CALLABLE_FUNCTIONS_HPP
#define CJDB_TEST_CONCEPTS_CALLABLE_FUNCTIONS_HPP

namespace regular_invocable {
	struct A {
		int i_ = 13;
		constexpr int f() const noexcept { return 42; }
		constexpr int g(int i) { return 2 * i + 1; }
		constexpr int h(int j) && { return i_ * j; }
	};

	constexpr int f() noexcept { return 13; }
	constexpr int g(int i) { return 2 * i + 1; }
} // namespace regular_invocable

namespace predicate {
	struct l2r_sorted {
		template<class T>
		constexpr bool operator()(T const& a, T const& b, T const& c) const noexcept
		{
			return a <= b and b <= c;
		}
	};

	struct not_a_predicate {
		constexpr void operator()() const noexcept {}
	};
} // namespace predicate

namespace relation {
	constexpr int greater(int x, int y) noexcept
	{
		return x > y;
	}
} // namespace relation

namespace strict_weak_order {} // namespace strict_weak_order

#endif // CJDB_TEST_CONCEPTS_CALLABLE_FUNCTIONS_HPP
