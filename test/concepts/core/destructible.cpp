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

static_assert(cjdb::Destructible<int>);
static_assert(cjdb::Destructible<const int>);
static_assert(not cjdb::Destructible<void>);
static_assert(cjdb::Destructible<int&>);
static_assert(not cjdb::Destructible<void()>);
static_assert(cjdb::Destructible<void(*)()>);
static_assert(cjdb::Destructible<void(&)()>);
static_assert(not cjdb::Destructible<int[]>);
static_assert(cjdb::Destructible<int[2]>);
static_assert(cjdb::Destructible<int(*)[2]>);
static_assert(cjdb::Destructible<int(&)[2]>);
static_assert(cjdb::Destructible<moveonly>);
static_assert(cjdb::Destructible<nonmovable>);
static_assert(not cjdb::Destructible<indestructible>);
static_assert(not cjdb::Destructible<throwing_destructor>);

int main() {}
