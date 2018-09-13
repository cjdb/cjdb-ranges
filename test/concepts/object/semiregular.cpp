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
#include "cjdb/detail/concepts/object/semiregular.hpp"

#include "../object.hpp"

static_assert(cjdb::Semiregular<int>);
static_assert(cjdb::Semiregular<double>);
static_assert(not cjdb::Semiregular<void>);
static_assert(not cjdb::Semiregular<int&>);
static_assert(cjdb::Semiregular<semiregular>);
static_assert(cjdb::Semiregular<regular>);
static_assert(cjdb::Semiregular<copyable>);
static_assert(not cjdb::Semiregular<moveonly>);
static_assert(not cjdb::Semiregular<nonmovable>);
static_assert(not cjdb::Semiregular<copyonly>);
static_assert(not cjdb::Semiregular<explicit_move>);
static_assert(not cjdb::Semiregular<explicit_copy>);

int main() {}
