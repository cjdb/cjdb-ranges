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
#include "cjdb/concepts/object/regular.hpp"

#include "../object.hpp"

static_assert(cjdb::regular<int>);
static_assert(cjdb::regular<double>);
static_assert(not cjdb::regular<void>);
static_assert(not cjdb::regular<int&>);
static_assert(not cjdb::regular<semiregular>);
static_assert(cjdb::regular<regular>);
static_assert(not cjdb::regular<copyable>);
static_assert(not cjdb::regular<moveonly>);
static_assert(not cjdb::regular<nonmovable>);
static_assert(not cjdb::regular<copyonly>);
static_assert(not cjdb::regular<explicit_move>);
static_assert(not cjdb::regular<explicit_copy>);

int main() {}
