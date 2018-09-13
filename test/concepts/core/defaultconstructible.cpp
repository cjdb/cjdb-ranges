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
#include "cjdb/detail/concepts/core/defaultconstructible.hpp"

#include "../object.hpp"
#include <initializer_list>

static_assert(cjdb::DefaultConstructible<int>);
static_assert(cjdb::DefaultConstructible<int const>);
static_assert(not cjdb::DefaultConstructible<int&>);
static_assert(not cjdb::DefaultConstructible<int const&>);
static_assert(not cjdb::DefaultConstructible<int()>);
static_assert(not cjdb::DefaultConstructible<int(&)()>);
static_assert(cjdb::DefaultConstructible<double>);
static_assert(not cjdb::DefaultConstructible<void>);
static_assert(not cjdb::DefaultConstructible<int[]>);
static_assert(cjdb::DefaultConstructible<int[2]>);
static_assert(not cjdb::DefaultConstructible<nondefaultconstructible>);

// It's hard to catch explicit default constructors, see
// http://www.open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#1518.
// static_assert(not cjdb::DefaultConstructible<explicit_default>);
static_assert(cjdb::DefaultConstructible<explicit_move>);
static_assert(cjdb::DefaultConstructible<explicit_copy>);
static_assert(not cjdb::DefaultConstructible<deleted_default>);

static_assert(cjdb::DefaultConstructible<std::initializer_list<int>>);
static_assert(cjdb::DefaultConstructible<int*>);

int main() {}
