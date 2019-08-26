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
#include "cjdb/concepts/object/semiregular.hpp"

#include "../object.hpp"

static_assert(cjdb::semiregular<int>);
static_assert(cjdb::semiregular<double>);
static_assert(not cjdb::semiregular<void>);
static_assert(not cjdb::semiregular<int&>);
static_assert(cjdb::semiregular<semiregular>);
static_assert(cjdb::semiregular<regular>);
static_assert(cjdb::semiregular<copyable>);
static_assert(not cjdb::semiregular<moveonly>);
static_assert(not cjdb::semiregular<nonmovable>);
static_assert(not cjdb::semiregular<copyonly>);
static_assert(not cjdb::semiregular<explicit_move>);
static_assert(not cjdb::semiregular<explicit_copy>);

int main() {}
