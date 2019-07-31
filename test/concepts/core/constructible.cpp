//  Copyright Casey Carter
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Derived from: https://github.com/caseycarter/cmcstl2
// Project home: https://github.com/cjdb/clang-concepts-ranges
//
#include "cjdb/concepts/core/constructible_from.hpp"

#include "../object.hpp"
#include <initializer_list>

static_assert(cjdb::constructible_from<int>);
static_assert(cjdb::constructible_from<int const>);
static_assert(not cjdb::constructible_from<int const&>);
static_assert(not cjdb::constructible_from<int()>);
static_assert(not cjdb::constructible_from<int(&)()>);
static_assert(not cjdb::constructible_from<int[]>);
static_assert(cjdb::constructible_from<int[5]>);
static_assert(not cjdb::constructible_from<nondefaultconstructible>);
static_assert(cjdb::constructible_from<int const(&)[5], int(&)[5]>);
static_assert(not cjdb::constructible_from<int, int(&)[3]>);

static_assert(cjdb::constructible_from<int, int>);
static_assert(cjdb::constructible_from<int, int&>);
static_assert(cjdb::constructible_from<int, int&&>);
static_assert(cjdb::constructible_from<int, const int>);
static_assert(cjdb::constructible_from<int, const int&>);
static_assert(cjdb::constructible_from<int, const int&&>);

static_assert(cjdb::constructible_from<copyable, copyable>);
static_assert(cjdb::constructible_from<copyable, copyable&>);
static_assert(cjdb::constructible_from<copyable, copyable&&>);
static_assert(cjdb::constructible_from<copyable, const copyable>);
static_assert(cjdb::constructible_from<copyable, const copyable&>);
static_assert(cjdb::constructible_from<copyable, const copyable&&>);

static_assert(not cjdb::constructible_from<int&, int>);
static_assert(cjdb::constructible_from<int&, int&>);
static_assert(not cjdb::constructible_from<int&, int&&>);
static_assert(not cjdb::constructible_from<int&, const int>);
static_assert(not cjdb::constructible_from<int&, const int&>);
static_assert(not cjdb::constructible_from<int&, const int&&>);

static_assert(cjdb::constructible_from<const int&, int>);
static_assert(cjdb::constructible_from<const int&, int&>);
static_assert(cjdb::constructible_from<const int&, int&&>);
static_assert(cjdb::constructible_from<const int&, const int>);
static_assert(cjdb::constructible_from<const int&, const int&>);
static_assert(cjdb::constructible_from<const int&, const int&&>);

static_assert(cjdb::constructible_from<int&&, int>);
static_assert(not cjdb::constructible_from<int&&, int&>);
static_assert(cjdb::constructible_from<int&&, int&&>);
static_assert(not cjdb::constructible_from<int&&, const int>);
static_assert(not cjdb::constructible_from<int&&, const int&>);
static_assert(not cjdb::constructible_from<int&&, const int&&>);

static_assert(cjdb::constructible_from<const int&&, int>);
static_assert(not cjdb::constructible_from<const int&&, int&>);
static_assert(cjdb::constructible_from<const int&&, int&&>);
static_assert(cjdb::constructible_from<const int&&, const int>);
static_assert(not cjdb::constructible_from<const int&&, const int&>);
static_assert(cjdb::constructible_from<const int&&, const int&&>);

static_assert(cjdb::constructible_from<XXX, int>);

static_assert(cjdb::constructible_from<moveonly, moveonly>);

static_assert(cjdb::constructible_from<std::initializer_list<int>>);
static_assert(cjdb::constructible_from<int*>);

// https://github.com/ericniebler/stl2/issues/301
static_assert(not cjdb::constructible_from<int&, long&>);

int main() {}
