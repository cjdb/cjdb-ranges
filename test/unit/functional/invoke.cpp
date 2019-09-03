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
#include "cjdb/functional/invoke.hpp"

#include "cjdb/test/simple_test.hpp"
#include <memory>
#include <utility>

constexpr struct {
	template <typename T>
	constexpr auto&& operator()(T&& arg) const noexcept {
		return std::forward<T>(arg);
	}
} h;

struct A {
	int i = 13; // NOLINT(misc-non-private-member-variables-in-classes,readability-magic-numbers)
	[[nodiscard]] constexpr int f() const noexcept { return 42; } // NOLINT(readability-magic-numbers,readability-convert-member-functions-to-static)
	constexpr int g(int i_) { return 2 * i_; } // NOLINT(readability-convert-member-functions-to-static)
};

constexpr int f() noexcept { return 13; } // NOLINT(readability-magic-numbers)
constexpr int g(int i) { return 2 * i + 1; } // NOLINT(readability-magic-numbers)

int main() // NOLINT(bugprone-exception-escape)
{
	CHECK(cjdb::invoke(f) == 13); // NOLINT(readability-magic-numbers)
	CHECK(noexcept(cjdb::invoke(f) == 13)); // NOLINT(readability-magic-numbers)
	CHECK(cjdb::invoke(g, 2) == 5); // NOLINT(readability-magic-numbers)
	CHECK(cjdb::invoke(h, 42) == 42); // NOLINT(readability-magic-numbers)
	CHECK(noexcept(cjdb::invoke(h, 42) == 42)); // NOLINT(readability-magic-numbers)
	{
		int i = 13; // NOLINT(readability-magic-numbers)
		CHECK(&cjdb::invoke(h, i) == &i);
		CHECK(noexcept(&cjdb::invoke(h, i) == &i));
	}

	CHECK(cjdb::invoke(&A::f, A{}) == 42); // NOLINT(readability-magic-numbers)
	CHECK(noexcept(cjdb::invoke(&A::f, A{}) == 42)); // NOLINT(readability-magic-numbers)
	CHECK(cjdb::invoke(&A::g, A{}, 2) == 4); // NOLINT(readability-magic-numbers)
	{
		A a;
		const auto& ca = a;
		CHECK(cjdb::invoke(&A::f, a) == 42); // NOLINT(readability-magic-numbers)
		CHECK(noexcept(cjdb::invoke(&A::f, a) == 42)); // NOLINT(readability-magic-numbers)
		CHECK(cjdb::invoke(&A::f, ca) == 42); // NOLINT(readability-magic-numbers)
		CHECK(noexcept(cjdb::invoke(&A::f, ca) == 42)); // NOLINT(readability-magic-numbers)
		CHECK(cjdb::invoke(&A::g, a, 2) == 4); // NOLINT(readability-magic-numbers)
	}

	{
		A a;
		const auto& ca = a;
		CHECK(cjdb::invoke(&A::f, &a) == 42); // NOLINT(readability-magic-numbers)
		CHECK(noexcept(cjdb::invoke(&A::f, &a) == 42)); // NOLINT(readability-magic-numbers)
		CHECK(cjdb::invoke(&A::f, &ca) == 42); // NOLINT(readability-magic-numbers)
		CHECK(noexcept(cjdb::invoke(&A::f, &ca) == 42)); // NOLINT(readability-magic-numbers)
		CHECK(cjdb::invoke(&A::g, &a, 2) == 4); // NOLINT(readability-magic-numbers)
	}
	{
		auto up = std::make_unique<A>();
		CHECK(cjdb::invoke(&A::f, up) == 42); // NOLINT(readability-magic-numbers)
		CHECK(cjdb::invoke(&A::g, up, 2) == 4); // NOLINT(readability-magic-numbers)
	}
	{
		auto sp = std::make_shared<A>();
		CHECK(cjdb::invoke(&A::f, sp) == 42); // NOLINT(readability-magic-numbers)
		CHECK(noexcept(cjdb::invoke(&A::f, sp) == 42)); // NOLINT(readability-magic-numbers)
		CHECK(cjdb::invoke(&A::g, sp, 2) == 4); // NOLINT(readability-magic-numbers)
	}

	CHECK(cjdb::invoke(&A::i, A{}) == 13); // NOLINT(readability-magic-numbers)
	CHECK(noexcept(cjdb::invoke(&A::i, A{}) == 13)); // NOLINT(readability-magic-numbers)
	{ int&& tmp = cjdb::invoke(&A::i, A{}); (void)tmp; }

	{
		A a;
		const auto& ca = a;
		CHECK(cjdb::invoke(&A::i, a) == 13); // NOLINT(readability-magic-numbers)
		CHECK(noexcept(cjdb::invoke(&A::i, a) == 13)); // NOLINT(readability-magic-numbers)
		CHECK(cjdb::invoke(&A::i, ca) == 13); // NOLINT(readability-magic-numbers)
		CHECK(noexcept(cjdb::invoke(&A::i, ca) == 13)); // NOLINT(readability-magic-numbers)
		CHECK(cjdb::invoke(&A::i, &a) == 13); // NOLINT(readability-magic-numbers)
		CHECK(noexcept(cjdb::invoke(&A::i, &a) == 13)); // NOLINT(readability-magic-numbers)
		CHECK(cjdb::invoke(&A::i, &ca) == 13); // NOLINT(readability-magic-numbers)
		CHECK(noexcept(cjdb::invoke(&A::i, &ca) == 13)); // NOLINT(readability-magic-numbers)

		cjdb::invoke(&A::i, a) = 0;
		CHECK(a.i == 0);
		cjdb::invoke(&A::i, &a) = 1;
		CHECK(a.i == 1);
		static_assert(cjdb::same_as<decltype(cjdb::invoke(&A::i, ca)), const int&>);
		static_assert(cjdb::same_as<decltype(cjdb::invoke(&A::i, &ca)), const int&>);
	}

	{
		auto up = std::make_unique<A>();
		CHECK(cjdb::invoke(&A::i, up) == 13); // NOLINT(readability-magic-numbers)
		cjdb::invoke(&A::i, up) = 0;
		CHECK(up->i == 0);
	}

	{
		auto sp = std::make_shared<A>();
		CHECK(cjdb::invoke(&A::i, sp) == 13); // NOLINT(readability-magic-numbers)
		cjdb::invoke(&A::i, sp) = 0;
		CHECK(sp->i == 0);
	}

	return ::test_result();
}
