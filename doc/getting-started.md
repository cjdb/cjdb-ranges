# Getting started

This tutorial will help you get started with `cjdb-ranges`.

## Prerequisites

For brevity, there will be an assumption that you're familiar with both Conan and CMake.

## Installing cjdb-ranges

See [install.md].

## Writing a simple file with cjdb-ranges

We're going to implement a concept-checked version of `std::plus`, which is similar to the one found
in [P1813].

```cpp
#include <cjdb/concepts.hpp>
#include <cjdb/range.hpp>
#include <iostream>
#include <utility>
#include <vector>

namespace example::detail {
	/// \brief Checks that two objects of possibly different types can be added.
	///
	/// \pre **Axiom:**
	/// The expression `t + u` is expression-equivalent to `u + t`.
	/// \pre **Axiom:**
	/// `T{}` and `U{}` represent the zeroes of their respective types. That is the expressions
	/// `t + T{}` and `T{} + t` are equal to `t`, and the expressions `u + U{}` and `U{} + u` are
	///  equal to `u`.
	/// \note **Complexity:**
	/// All described operations have amortised constant-time evaluation.
	///
	template<typename T, typename U>
	concept summable_with =
		cjdb::default_initializable<T> and
		cjdb::default_initializable<U> and
		cjdb::common_reference_with<T, U> and
		requires(T&& t, U&& u) {
			{ std::forward<T>(t) + std::forward<T>(t) } -> cjdb::common_with<T>;
			{ std::forward<U>(u) + std::forward<U>(u) } -> cjdb::common_with<U>;
			{ std::forward<T>(t) + std::forward<U>(u) } -> cjdb::common_with<T>;
			{ std::forward<U>(u) + std::forward<T>(t) } -> cjdb::common_with<U>;
			requires cjdb::same_as<decltype(std::forward<T>(t) + std::forward<U>(u)),
			                       decltype(std::forward<U>(u) + std::forward<T>(t))>;
		};
} // namespace example::detail
```
Here, we've defined an implementation-detail concept that checks it's okay to 'add' two objects of
potentially different types. This concept requires that the declarations `T t;` and `U u;` are
well-formed (compilable), and that `T` and `U` share some sort of common reference. Further, it must
be possible to add `t` to itself, `u` to itself, `t` to `u`, `u` to `t`, and that the types for
these four expressions are types in common with `T` and `U` respectively. Finally, we require that
`t + u` has the same type as `u + t` to help guarantee _[equaltional reasoning][1]_.

Notice that we've provided some documentation that details the axioms and complexity requirements of
something that usees this concept. Concepts are split into three parts: syntax requirements
(constraints), which can be checked at compile-time by the compiler; semantic requirements (axioms),
which can be checked at run-time using contracts, or at compile-time with sophisticated compile-time
analysis; and complexity requirements, which might be checkable using sophisticated benchmarking
tools, but probably require mathematical proof. We say that a type _satisfies_ a concept if it meets
all of the requirements imposed by the constraints, and that it _models_ a concept if it meets all
of the axioms and complexity requirements.

People sometimes express concern over non-constraints, claiming that they can't be checked. Marshall
Clow has likened axioms to pre- and post-conditions, which is a good way to think about them: the
concept documents (some of) the pre- and post-conditions of an algorithm, which means that there are
implied pre-conditions for anyone that uses `summable_with`. A good library should pass on a detail
concept's axioms to the lowest public-facing entity, which is what we'll do when we build `plus`.

One axiom is that we require _commutativity_: `t + u` produces the exact same value as `u + t`.
Our other axiom requires the existence of a _zero_; that is, there exists a value representable
by both `T` and `U` such that when added with any other value from `T` or `U`, we get back that
other value as our result (just like when adding something to `0`). This particular concept expects
that value to be represented as `T{}` and `U{}`.

```cpp
namespace example {
	/// \brief Function object for adding two objects together.
	///
	/// \pre The expression `t + u` is expression-equivalent to `u + t`.
	/// \pre `T{}` and `U{}` represent the zeroes of their respective types. That is the
	///      expressions `t + T{}` and `T{} + t` are equal to `t`, and the expressions `u + U{}`
	///      and `U{} + u` are equal to `u`.
	/// \note **Complexity:**
	/// All described operations have amortised constant-time evaluation.
	///
	struct plus {
		template<typename T, detail::summable_with<T> U>
		constexpr auto operator()(T&& t, U&& u) const
		{
			return std::forward<T>(t) + std::forward<U>(u);
		}
	};
} // namespace example
```

And here's our implementation of `plus`. As teased, the axioms have been moved forward into our
public-facing entity, but changed into function pre-conditions.

We can now use it to add things together.

```cpp
int main()
{
	auto sum = []<cjdb::ranges::range R>(R&& r)
	requires cjdb::regular<cjdb::ranges::range_value_t<R>>
	{
		auto result = cjdb::ranges::range_value_t<R>{};
		for (auto const& i : r) {
			result = example::plus{}(std::move(result), i);
		}
		return result;
	};

	std::cout << sum(std::vector(100, 0)) << '\n';   // prints 0
	std::cout << sum(std::vector(200, 0.5)) << '\n'; // prints 100
}
```

[P1813]: https://wg21.link/p1813
[1]: https://link.springer.com/chapter/10.1007%2F1-84628-598-4_2
