// cmcstl2 - A concept-enabled C++ standard library
//
//  Copyright Casey Carter 2015
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/caseycarter/cmcstl2
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "cjdb/functional/invoke.hpp"
#include <doctest.h>
#include <memory>
#include <utility>

constexpr struct {
	template <typename T>
	constexpr auto&& operator()(T&& arg) const noexcept {
		return std::forward<T>(arg);
	}
} h;

struct A {
	int i = 13;
	constexpr int f() const noexcept { return 42; }
	constexpr int g(int i) { return 2 * i; }
};

constexpr int f() noexcept { return 13; }
constexpr int g(int i) { return 2 * i + 1; }

TEST_CASE("[func.invoke]") { // NOLINT(readability-function-size)
	CHECK(cjdb::invoke(f) == 13);
	CHECK(noexcept(cjdb::invoke(f) == 13));
	CHECK(cjdb::invoke(g, 2) == 5);
	CHECK(cjdb::invoke(h, 42) == 42);
	CHECK(noexcept(cjdb::invoke(h, 42) == 42));
	{
		int i = 13;
		CHECK(&cjdb::invoke(h, i) == &i);
		CHECK(noexcept(&cjdb::invoke(h, i) == &i));
	}

	CHECK(cjdb::invoke(&A::f, A{}) == 42);
	CHECK(noexcept(cjdb::invoke(&A::f, A{}) == 42));
	CHECK(cjdb::invoke(&A::g, A{}, 2) == 4);
	{
		A a;
		const auto& ca = a;
		CHECK(cjdb::invoke(&A::f, a) == 42);
		CHECK(noexcept(cjdb::invoke(&A::f, a) == 42));
		CHECK(cjdb::invoke(&A::f, ca) == 42);
		CHECK(noexcept(cjdb::invoke(&A::f, ca) == 42));
		CHECK(cjdb::invoke(&A::g, a, 2) == 4);
	}

	{
		A a;
		const auto& ca = a;
		CHECK(cjdb::invoke(&A::f, &a) == 42);
		CHECK(noexcept(cjdb::invoke(&A::f, &a) == 42));
		CHECK(cjdb::invoke(&A::f, &ca) == 42);
		CHECK(noexcept(cjdb::invoke(&A::f, &ca) == 42));
		CHECK(cjdb::invoke(&A::g, &a, 2) == 4);
	}
	{
		auto up = std::make_unique<A>();
		CHECK(cjdb::invoke(&A::f, up) == 42);
		CHECK(cjdb::invoke(&A::g, up, 2) == 4);
	}
	{
		auto sp = std::make_shared<A>();
		CHECK(cjdb::invoke(&A::f, sp) == 42);
		CHECK(noexcept(cjdb::invoke(&A::f, sp) == 42));
		CHECK(cjdb::invoke(&A::g, sp, 2) == 4);
	}

	CHECK(cjdb::invoke(&A::i, A{}) == 13);
	CHECK(noexcept(cjdb::invoke(&A::i, A{}) == 13));
	{ int&& tmp = cjdb::invoke(&A::i, A{}); (void)tmp; }

	{
		A a;
		const auto& ca = a;
		CHECK(cjdb::invoke(&A::i, a) == 13);
		CHECK(noexcept(cjdb::invoke(&A::i, a) == 13));
		CHECK(cjdb::invoke(&A::i, ca) == 13);
		CHECK(noexcept(cjdb::invoke(&A::i, ca) == 13));
		CHECK(cjdb::invoke(&A::i, &a) == 13);
		CHECK(noexcept(cjdb::invoke(&A::i, &a) == 13));
		CHECK(cjdb::invoke(&A::i, &ca) == 13);
		CHECK(noexcept(cjdb::invoke(&A::i, &ca) == 13));

		cjdb::invoke(&A::i, a) = 0;
		CHECK(a.i == 0);
		cjdb::invoke(&A::i, &a) = 1;
		CHECK(a.i == 1);
		static_assert(cjdb::same_as<decltype(cjdb::invoke(&A::i, ca)), const int&>);
		static_assert(cjdb::same_as<decltype(cjdb::invoke(&A::i, &ca)), const int&>);
	}

	{
		auto up = std::make_unique<A>();
		CHECK(cjdb::invoke(&A::i, up) == 13);
		cjdb::invoke(&A::i, up) = 0;
		CHECK(up->i == 0);
	}

	{
		auto sp = std::make_shared<A>();
		CHECK(cjdb::invoke(&A::i, sp) == 13);
		cjdb::invoke(&A::i, sp) = 0;
		CHECK(sp->i == 0);
	}
}
