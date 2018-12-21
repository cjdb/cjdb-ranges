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

static_assert(cjdb::Regular<int>);
static_assert(cjdb::Regular<double>);
static_assert(not cjdb::Regular<void>);
static_assert(not cjdb::Regular<int&>);
static_assert(not cjdb::Regular<semiregular>);
static_assert(cjdb::Regular<regular>);
static_assert(not cjdb::Regular<copyable>);
static_assert(not cjdb::Regular<moveonly>);
static_assert(not cjdb::Regular<nonmovable>);
static_assert(not cjdb::Regular<copyonly>);
static_assert(not cjdb::Regular<explicit_move>);
static_assert(not cjdb::Regular<explicit_copy>);

int main() {}
