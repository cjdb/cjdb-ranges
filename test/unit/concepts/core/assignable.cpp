// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/concepts/core/assignable_from.hpp"

#include <memory>
#include <mutex>
#include <vector>

template<typename T1, typename T2 = T1>
void models_assignable_from()
{
	static_assert(not cjdb::assignable_from<T1, T2>);
	static_assert(not cjdb::assignable_from<T1, T2 const>);
	static_assert(not cjdb::assignable_from<T1, T2&>);
	static_assert(not cjdb::assignable_from<T1, T2 const&>);
	static_assert(not cjdb::assignable_from<T1, T2&&>);
	static_assert(not cjdb::assignable_from<T1, T2 const&&>);

	static_assert(cjdb::assignable_from<T1&, T2>);
	static_assert(cjdb::assignable_from<T1&, T2 const>);
	static_assert(cjdb::assignable_from<T1&, T2&>);
	static_assert(cjdb::assignable_from<T1&, T2 const&>);
	static_assert(cjdb::assignable_from<T1&, T2&&>);
	static_assert(cjdb::assignable_from<T1&, T2 const&&>);

	static_assert(not cjdb::assignable_from<T1 const&, T2>);
	static_assert(not cjdb::assignable_from<T1 const&, T2 const>);
	static_assert(not cjdb::assignable_from<T1 const&, T2&>);
	static_assert(not cjdb::assignable_from<T1 const&, T2 const&>);
	static_assert(not cjdb::assignable_from<T1 const&, T2&&>);
	static_assert(not cjdb::assignable_from<T1 const&, T2 const&&>);

	static_assert(not cjdb::assignable_from<T1&&, T2>);
	static_assert(not cjdb::assignable_from<T1&&, T2 const>);
	static_assert(not cjdb::assignable_from<T1&&, T2&>);
	static_assert(not cjdb::assignable_from<T1&&, T2 const&>);
	static_assert(not cjdb::assignable_from<T1&&, T2&&>);
	static_assert(not cjdb::assignable_from<T1&&, T2 const&&>);

	static_assert(not cjdb::assignable_from<T1 const&&, T2>);
	static_assert(not cjdb::assignable_from<T1 const&&, T2 const>);
	static_assert(not cjdb::assignable_from<T1 const&&, T2&>);
	static_assert(not cjdb::assignable_from<T1 const&&, T2 const&>);
	static_assert(not cjdb::assignable_from<T1 const&&, T2&&>);
	static_assert(not cjdb::assignable_from<T1 const&&, T2 const&&>);
}

struct real_assignable {
	real_assignable(int); // NOLINT(google-explicit-constructor)
	real_assignable& operator=(int);
};

template<template<class> class TQual, template<class> class QQual>
struct cjdb::basic_common_reference<real_assignable, int, TQual, QQual> {
	using type = real_assignable;
};

template<template<class> class TQual, template<class> class QQual>
struct cjdb::basic_common_reference<int, real_assignable, TQual, QQual> {
	using type = real_assignable;
};

int main()
{
	models_assignable_from<int>();
	models_assignable_from<double>();
	models_assignable_from<std::vector<int>>();
	models_assignable_from<std::vector<double>>();

	struct default_assignable {};
	models_assignable_from<default_assignable>();

	models_assignable_from<int, double>();
	models_assignable_from<double, int>();

	struct fake_assignable {
		fake_assignable& operator=(int);
	};
	models_assignable_from<fake_assignable>();
	static_assert(not cjdb::assignable_from<fake_assignable&, int>);

	models_assignable_from<real_assignable>();
	models_assignable_from<real_assignable, int>();

	static_assert(not cjdb::assignable_from<int, std::vector<int>>);
	static_assert(not cjdb::assignable_from<std::vector<int>, int>);
	static_assert(not cjdb::assignable_from<std::vector<int>, std::vector<double>>);
}
