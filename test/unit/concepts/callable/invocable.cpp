// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/concepts/callable/invocable.hpp"

#include "functions.hpp"
#include <memory>
#include <random>
#include <utility>

template<class F, class... Args>
requires cjdb::invocable<F, Args...>
constexpr void models_invocable(F, Args&&...) noexcept {}

template<class F, class... Args>
requires (not cjdb::invocable<F, Args...>)
constexpr void not_invocable(F, Args&&...) noexcept {}

int main() // NOLINT(bugprone-exception-escape)
{
	{
		using namespace regular_invocable;

		models_invocable(f);
		not_invocable(f, 0);

		models_invocable(g, 2);
		not_invocable(g);
		not_invocable(g, 3, 0);

		not_invocable(&A::i_);
		not_invocable(&A::f);

		{
			auto a = A{};
			models_invocable(&A::i_, a);
			models_invocable(&A::f, a);
			models_invocable(&A::g, a, 0);
			not_invocable(&A::g, a);
			not_invocable(&A::g, 0);
			not_invocable(&A::h);

			auto const& c = a;
			models_invocable(&A::i_, c);
			models_invocable(&A::f, c);
			not_invocable(&A::g, c, 0);
			not_invocable(&A::h, c, 0);
		}

		models_invocable(&A::i_, A{});
		models_invocable(&A::f, A{});
		models_invocable(&A::g, A{}, 0);
		models_invocable(&A::h, A{}, 0);

		{
			auto up = std::make_unique<A>();
			models_invocable(&A::i_, up);
			models_invocable(&A::f, up);
			models_invocable(&A::g, up, 0);
			not_invocable(&A::h, up, 0);
		}
		{
			auto sp = std::make_shared<A>();
			models_invocable(&A::i_, sp);
			models_invocable(&A::f, sp);
			models_invocable(&A::g, sp, 0);
			not_invocable(&A::h, sp, 0);
		}
	}
	{
		auto generator = std::mt19937_64{std::random_device{}()};
		auto distribution = std::uniform_int_distribution<>();
		models_invocable(distribution, generator);
	}
}
