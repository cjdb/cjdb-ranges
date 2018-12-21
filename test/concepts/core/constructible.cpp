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
#include "cjdb/concepts/core/constructible.hpp"

#include "../object.hpp"
#include <initializer_list>

static_assert(cjdb::Constructible<int>);
static_assert(cjdb::Constructible<int const>);
static_assert(not cjdb::Constructible<int const&>);
static_assert(not cjdb::Constructible<int()>);
static_assert(not cjdb::Constructible<int(&)()>);
static_assert(not cjdb::Constructible<int[]>);
static_assert(cjdb::Constructible<int[5]>);
static_assert(not cjdb::Constructible<nondefaultconstructible>);
static_assert(cjdb::Constructible<int const(&)[5], int(&)[5]>);
static_assert(not cjdb::Constructible<int, int(&)[3]>);

static_assert(cjdb::Constructible<int, int>);
static_assert(cjdb::Constructible<int, int&>);
static_assert(cjdb::Constructible<int, int&&>);
static_assert(cjdb::Constructible<int, const int>);
static_assert(cjdb::Constructible<int, const int&>);
static_assert(cjdb::Constructible<int, const int&&>);

static_assert(cjdb::Constructible<copyable, copyable>);
static_assert(cjdb::Constructible<copyable, copyable&>);
static_assert(cjdb::Constructible<copyable, copyable&&>);
static_assert(cjdb::Constructible<copyable, const copyable>);
static_assert(cjdb::Constructible<copyable, const copyable&>);
static_assert(cjdb::Constructible<copyable, const copyable&&>);

static_assert(not cjdb::Constructible<int&, int>);
static_assert(cjdb::Constructible<int&, int&>);
static_assert(not cjdb::Constructible<int&, int&&>);
static_assert(not cjdb::Constructible<int&, const int>);
static_assert(not cjdb::Constructible<int&, const int&>);
static_assert(not cjdb::Constructible<int&, const int&&>);

static_assert(cjdb::Constructible<const int&, int>);
static_assert(cjdb::Constructible<const int&, int&>);
static_assert(cjdb::Constructible<const int&, int&&>);
static_assert(cjdb::Constructible<const int&, const int>);
static_assert(cjdb::Constructible<const int&, const int&>);
static_assert(cjdb::Constructible<const int&, const int&&>);

static_assert(cjdb::Constructible<int&&, int>);
static_assert(not cjdb::Constructible<int&&, int&>);
static_assert(cjdb::Constructible<int&&, int&&>);
static_assert(not cjdb::Constructible<int&&, const int>);
static_assert(not cjdb::Constructible<int&&, const int&>);
static_assert(not cjdb::Constructible<int&&, const int&&>);

static_assert(cjdb::Constructible<const int&&, int>);
static_assert(not cjdb::Constructible<const int&&, int&>);
static_assert(cjdb::Constructible<const int&&, int&&>);
static_assert(cjdb::Constructible<const int&&, const int>);
static_assert(not cjdb::Constructible<const int&&, const int&>);
static_assert(cjdb::Constructible<const int&&, const int&&>);

static_assert(cjdb::Constructible<XXX, int>);

static_assert(cjdb::Constructible<moveonly, moveonly>);

static_assert(cjdb::Constructible<std::initializer_list<int>>);
static_assert(cjdb::Constructible<int*>);

// https://github.com/ericniebler/stl2/issues/301
static_assert(not cjdb::Constructible<int&, long&>);

int main() {}
