// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/concepts/callable/regular_invocable.hpp"

#include "functions.hpp"
#include <memory>
#include <utility>

template<class F, class... Args>
requires cjdb::regular_invocable<F, Args...>
constexpr void models_regular_invocable(F, Args&&...) noexcept {}

template<class F, class... Args>
requires (not cjdb::regular_invocable<F, Args...>)
constexpr void not_regular_invocable(F, Args&&...) noexcept {}

int main() // NOLINT(bugprone-exception-escape)
{
	{
		using namespace regular_invocable;

		models_regular_invocable(f);
		not_regular_invocable(f, 0);

		models_regular_invocable(g, 2);
		not_regular_invocable(g);
		not_regular_invocable(g, 3, 0);

		not_regular_invocable(&A::i_);
		not_regular_invocable(&A::f);

		{
			auto a = A{};
			models_regular_invocable(&A::i_, a);
			models_regular_invocable(&A::f, a);
			models_regular_invocable(&A::g, a, 0);
			not_regular_invocable(&A::g, a);
			not_regular_invocable(&A::g, 0);
			not_regular_invocable(&A::h);

			auto const& c = a;
			models_regular_invocable(&A::i_, c);
			models_regular_invocable(&A::f, c);
			not_regular_invocable(&A::g, c, 0);
			not_regular_invocable(&A::h, c, 0);
		}

		models_regular_invocable(&A::i_, A{});
		models_regular_invocable(&A::f, A{});
		models_regular_invocable(&A::g, A{}, 0);
		models_regular_invocable(&A::h, A{}, 0);

		{
			auto up = std::make_unique<A>();
			models_regular_invocable(&A::i_, up);
			models_regular_invocable(&A::f, up);
			models_regular_invocable(&A::g, up, 0);
			not_regular_invocable(&A::h, up, 0);
		}
		{
			auto sp = std::make_shared<A>();
			models_regular_invocable(&A::i_, sp);
			models_regular_invocable(&A::f, sp);
			models_regular_invocable(&A::g, sp, 0);
			not_regular_invocable(&A::h, sp, 0);
		}
	}

	models_regular_invocable(predicate::l2r_sorted{}, 0, 1, 2);
	models_regular_invocable(predicate::not_a_predicate{});
}
