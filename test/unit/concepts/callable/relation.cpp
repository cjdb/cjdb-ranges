// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/concepts/callable/relation.hpp"
#include "cjdb/concepts/callable/strict_weak_order.hpp"

#include "cjdb/functional/rangecmp/less.hpp"
#include "functions.hpp"

template<class F, class T1, class T2>
requires cjdb::relation<F, T1, T2>
constexpr void models_relation(F&&, T1&&, T2&&) noexcept {}

template<class F, class T1, class T2>
requires (not cjdb::relation<F, T1, T2>)
constexpr void not_relation(F&&, T1&&, T2&&) noexcept {}

// Tests also: strict_weak_order [concept.strictweakorder]
template<class F, class T1, class T2>
requires cjdb::relation<F, T1, T2>
constexpr void models_strict_weak_order(F&&, T1&&, T2&&) noexcept {}

// Tests also: strict_weak_order [concept.strictweakorder]
template<class F, class T1, class T2>
requires (not cjdb::relation<F, T1, T2>)
constexpr void not_strict_weak_order(F&&, T1&&, T2&&) noexcept {}

int main()
{
	{
		using namespace regular_invocable;

		auto a = A{};
		not_relation(&A::g, a, 0);
		not_relation(&A::h, A{}, 0);

		// Tests also: strict_weak_order [concept.strictweakorder]
		not_strict_weak_order(&A::g, a, 0);
		not_strict_weak_order(&A::h, A{}, 0);
	}
	{
		using namespace relation;

		models_relation(cjdb::ranges::less{}, 0, 1);
		models_relation(greater, 0, 1);

		// Tests also: strict_weak_order [concept.strictweakorder]
		models_strict_weak_order(cjdb::ranges::less{}, 0, 1);
		models_strict_weak_order(greater, 0, 1);
	}
}
