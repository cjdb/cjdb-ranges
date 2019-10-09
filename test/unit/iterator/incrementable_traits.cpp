// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/detail/iterator/incrementable_traits.hpp"

#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/concepts/core/integral.hpp"
#include <iterator>
#include <vector>

template<typename T, typename Expected>
constexpr void instantiate_incrementable_traits()
{
	static_assert(cjdb::same_as<typename cjdb::incrementable_traits<T>::difference_type, Expected>);
	static_assert(cjdb::same_as<cjdb::iter_difference_t<T>, Expected>);
}

template<typename T>
constexpr void check_pointer()
{
	instantiate_incrementable_traits<T*, std::ptrdiff_t>();
	instantiate_incrementable_traits<T const*, std::ptrdiff_t>();

	instantiate_incrementable_traits<T[], std::ptrdiff_t>(); // NOLINT(modernize-avoid-c-arrays)
}

template<typename T>
constexpr void check_with_difference_type()
{
	struct diff { using difference_type = T; };
	instantiate_incrementable_traits<diff, T>();
	instantiate_incrementable_traits<diff const, T>();
}

template<typename T>
struct friend_minus {
	friend T operator-(friend_minus, friend_minus) { return T(); }
};

template<cjdb::integral D>
constexpr void check_minus()
{
	struct member {
		D operator-(member) const { return D{}; }
	};
	instantiate_incrementable_traits<member, std::make_signed_t<D>>();
	instantiate_incrementable_traits<member const, std::make_signed_t<D>>();
	instantiate_incrementable_traits<friend_minus<D>, std::make_signed_t<D>>();
	instantiate_incrementable_traits<friend_minus<D> const, std::make_signed_t<D>>();
}

template<typename T>
constexpr void check_minus()
{
	constexpr auto result = requires {
		typename cjdb::incrementable_traits<friend_minus<T>>::difference_type;
	};
	static_assert(not result, "cjdb::iter_difference_t<bad_minus<T>> should fail.");
}

template<typename D, typename Minus>
struct difference_minus {
	using difference_type = D;
	constexpr friend Minus operator-(difference_minus, difference_minus)
	{ return Minus(); }
};

template<typename D, cjdb::integral Minus>
requires (not cjdb::same_as<D, Minus>)
constexpr void check_with_both()
{
	struct member {
		using difference_type = D;
		Minus operator-(member const&) const;
	};
	instantiate_incrementable_traits<member, D>();
	instantiate_incrementable_traits<member const, D>();
	instantiate_incrementable_traits<difference_minus<D, Minus>, D>();
	instantiate_incrementable_traits<difference_minus<D, Minus> const, D>();
}

int main()
{
	struct dummy {};

	check_pointer<int>();
	check_pointer<double>();
	check_pointer<int*>();
	check_pointer<dummy>();

	check_with_difference_type<int>();
	check_with_difference_type<long>();
	check_with_difference_type<float>();
	check_with_difference_type<dummy>();
	check_with_difference_type<int&>();
	check_with_difference_type<int const&>();
	check_with_difference_type<int volatile&>();
	check_with_difference_type<int*>();
	check_with_difference_type<int* const>();
	check_with_difference_type<int* volatile>();
	check_with_difference_type<int(*)()>();
	check_with_difference_type<int(&)()>();

	{
		// succeeds
		check_minus<char>();
		check_minus<signed char>();
		check_minus<unsigned char>();
		check_minus<short>();
		check_minus<unsigned short>();
		check_minus<int>();
		check_minus<unsigned int>();
		check_minus<long>();
		check_minus<unsigned long>();
		check_minus<long long>();
		check_minus<unsigned long long>();

		// fails
		check_minus<void>();
		check_minus<double>();
		check_minus<dummy>();
		check_minus<int&>();
		check_minus<int const&>();
		check_minus<int volatile&>();
		check_minus<int*>();
		check_minus<int* const>();
		check_minus<int* volatile>();
		check_minus<int(*)()>();
		check_minus<int(&)()>();
	}

	check_with_both<int, long>();
	check_with_both<double, int>();
	check_with_both<dummy, char>();
	check_with_both<int&, char>();
	check_with_both<int const&, char>();
	check_with_both<int volatile&, char>();
	check_with_both<int*, char>();
	check_with_both<int* const, char>();
	check_with_both<int* volatile, char>();
	check_with_both<int(*)(), char>();
	check_with_both<int(&)(), char>();

	// now for some standard types
	using cjdb::same_as, cjdb::iter_difference_t;
	static_assert(same_as<iter_difference_t<std::reverse_iterator<int*>>, std::ptrdiff_t>);
	static_assert(same_as<iter_difference_t<std::vector<int>>, std::vector<int>::difference_type>);
}
