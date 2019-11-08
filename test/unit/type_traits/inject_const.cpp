// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/detail/type_traits/inject_const.hpp"

using cjdb::detail_inject_const::inject_const_t;

static_assert(cjdb::same_as<inject_const_t<int>, int const>);
static_assert(cjdb::same_as<inject_const_t<int const>, int const>);

static_assert(cjdb::same_as<inject_const_t<int&>, int const&>);
static_assert(cjdb::same_as<inject_const_t<int const&>, int const&>);

static_assert(cjdb::same_as<inject_const_t<int&&>, int const&&>);
static_assert(cjdb::same_as<inject_const_t<int const&&>, int const&&>);

static_assert(cjdb::same_as<inject_const_t<int*>, int const*>);
static_assert(cjdb::same_as<inject_const_t<int const*>, int const*>);

static_assert(cjdb::same_as<inject_const_t<int**>, int* const*>);
static_assert(cjdb::same_as<inject_const_t<int* const*>, int* const*>);

static_assert(cjdb::same_as<inject_const_t<int const**>, int const* const*>);
static_assert(cjdb::same_as<inject_const_t<int const* const*>, int const* const*>);

template<typename T>
constexpr void check(T&& t)
{
	if constexpr (std::is_lvalue_reference_v<decltype(t)>) {
		static_assert(cjdb::same_as<inject_const_t<decltype(t)>,
		                            std::remove_reference_t<decltype(t)> const&>);
	}
	else {
		static_assert(cjdb::same_as<inject_const_t<decltype(t)>,
		                            std::remove_reference_t<decltype(t)> const&&>);
	}
}

int main()
{
	check(0);

	auto i = 0;
	check(i);
}
