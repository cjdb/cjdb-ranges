// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/concepts/callable/predicate.hpp"

#include "functions.hpp"
#include "cjdb/functional/rangecmp/less.hpp"

template<class F, class... Args>
requires cjdb::predicate<F, Args...>
constexpr void models_predicate(F, Args&&...) noexcept {}

template<class F, class... Args>
requires (not cjdb::predicate<F, Args...>)
constexpr void not_predicate(F, Args&&...) noexcept {}

int main()
{
	{
		using namespace regular_invocable;
		A a;
		models_predicate(&A::f, a);
		models_predicate(&A::g, a, 0);
		models_predicate(&A::h, A{}, 0);
	}
	models_predicate(predicate::l2r_sorted{}, 0, 0, 0);
	not_predicate(predicate::not_a_predicate{});

	models_predicate(cjdb::ranges::less{}, 0, 0);
	models_predicate(cjdb::ranges::less{}, 0, 0.0);
	models_predicate(relation::greater, 0, 0);
	models_predicate(relation::greater, 0, 0.0);
}
