// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/concepts/core/integral.hpp"

#include "cjdb/type_traits/expose_type.hpp"

template<class I>
constexpr void models_integral() noexcept
{
	static_assert(cjdb::integral<I>);
	static_assert(cjdb::integral<I const>);
	static_assert(cjdb::integral<I volatile>);
	static_assert(cjdb::integral<I const volatile>);

	static_assert(not cjdb::integral<I*>);
	static_assert(not cjdb::integral<I const*>);
	static_assert(not cjdb::integral<I volatile*>);
	static_assert(not cjdb::integral<I const volatile*>);

	static_assert(not cjdb::integral<I&>);
	static_assert(not cjdb::integral<I const&>);
	static_assert(not cjdb::integral<I volatile&>);
	static_assert(not cjdb::integral<I const volatile&>);

	static_assert(not cjdb::integral<std::remove_reference_t<I>&&>);
	static_assert(not cjdb::integral<std::remove_reference_t<I> const&&>);
	static_assert(not cjdb::integral<std::remove_reference_t<I> volatile&&>);
	static_assert(not cjdb::integral<std::remove_reference_t<I> const volatile&&>);
}

template<cjdb::signed_integral I>
constexpr void models_signed_integral() noexcept
{
	models_integral<I>();

	static_assert(cjdb::signed_integral<I>);
	static_assert(cjdb::signed_integral<I const>);
	static_assert(cjdb::signed_integral<I volatile>);
	static_assert(cjdb::signed_integral<I const volatile>);

	static_assert(not cjdb::signed_integral<I*>);
	static_assert(not cjdb::signed_integral<I const*>);
	static_assert(not cjdb::signed_integral<I volatile*>);
	static_assert(not cjdb::signed_integral<I const volatile*>);

	static_assert(not cjdb::signed_integral<I&>);
	static_assert(not cjdb::signed_integral<I const&>);
	static_assert(not cjdb::signed_integral<I volatile&>);
	static_assert(not cjdb::signed_integral<I const volatile&>);

	static_assert(not cjdb::signed_integral<std::remove_reference_t<I>&&>);
	static_assert(not cjdb::signed_integral<std::remove_reference_t<I> const&&>);
	static_assert(not cjdb::signed_integral<std::remove_reference_t<I> volatile&&>);
	static_assert(not cjdb::signed_integral<std::remove_reference_t<I> const volatile&&>);
}

template<cjdb::unsigned_integral I>
constexpr void models_unsigned_integral() noexcept
{
	models_integral<I>();

	static_assert(cjdb::unsigned_integral<I>);
	static_assert(cjdb::unsigned_integral<I const>);
	static_assert(cjdb::unsigned_integral<I volatile>);
	static_assert(cjdb::unsigned_integral<I const volatile>);

	static_assert(not cjdb::unsigned_integral<I*>);
	static_assert(not cjdb::unsigned_integral<I const*>);
	static_assert(not cjdb::unsigned_integral<I volatile*>);
	static_assert(not cjdb::unsigned_integral<I const volatile*>);

	static_assert(not cjdb::unsigned_integral<I&>);
	static_assert(not cjdb::unsigned_integral<I const&>);
	static_assert(not cjdb::unsigned_integral<I volatile&>);
	static_assert(not cjdb::unsigned_integral<I const volatile&>);

	static_assert(not cjdb::unsigned_integral<std::remove_reference_t<I>&&>);
	static_assert(not cjdb::unsigned_integral<std::remove_reference_t<I> const&&>);
	static_assert(not cjdb::unsigned_integral<std::remove_reference_t<I> volatile&&>);
	static_assert(not cjdb::unsigned_integral<std::remove_reference_t<I> const volatile&&>);
}

template<class T>
constexpr void models_none() noexcept
{
	static_assert(not cjdb::integral<T>);
	static_assert(not cjdb::signed_integral<T>);
	static_assert(not cjdb::unsigned_integral<T>);
}

int main()
{
	models_integral<bool>();
	models_integral<char>();
	models_integral<char16_t>();
	models_integral<char32_t>();
	models_integral<wchar_t>();

	models_signed_integral<signed char>();
	static_assert(not cjdb::unsigned_integral<signed char>);

	models_unsigned_integral<unsigned char>();
	static_assert(not cjdb::signed_integral<unsigned char>);

	models_signed_integral<short>();
	static_assert(not cjdb::unsigned_integral<short>);

	models_unsigned_integral<unsigned short>();
	static_assert(not cjdb::signed_integral<unsigned short>);

	models_signed_integral<int>();
	static_assert(not cjdb::unsigned_integral<int>);

	models_unsigned_integral<unsigned int>();
	static_assert(not cjdb::signed_integral<unsigned int>);

	models_signed_integral<long>();
	static_assert(not cjdb::unsigned_integral<long>);

	models_unsigned_integral<unsigned long>();
	static_assert(not cjdb::signed_integral<unsigned long>);

	models_signed_integral<long long>();
	static_assert(not cjdb::unsigned_integral<long long>);

	models_unsigned_integral<unsigned long long>();
	static_assert(not cjdb::signed_integral<unsigned long long>);

	models_none<float>();
	models_none<double>();
	models_none<long double>();

	struct S {};
	models_none<S>();
}
