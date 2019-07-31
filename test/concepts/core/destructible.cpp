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
#include "cjdb/concepts/core/destructible.hpp"

#include "../object.hpp"

static_assert(cjdb::destructible<int>);
static_assert(cjdb::destructible<const int>);
static_assert(not cjdb::destructible<void>);
static_assert(cjdb::destructible<int&>);
static_assert(not cjdb::destructible<void()>);
static_assert(cjdb::destructible<void(*)()>);
static_assert(cjdb::destructible<void(&)()>);
static_assert(not cjdb::destructible<int[]>);
static_assert(cjdb::destructible<int[2]>);
static_assert(cjdb::destructible<int(*)[2]>);
static_assert(cjdb::destructible<int(&)[2]>);
static_assert(cjdb::destructible<moveonly>);
static_assert(cjdb::destructible<nonmovable>);
static_assert(not cjdb::destructible<indestructible>);
static_assert(not cjdb::destructible<throwing_destructor>);

int main() {}
