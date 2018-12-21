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
#include "cjdb/concepts/core/moveconstructible.hpp"

#include "../object.hpp"

static_assert(not cjdb::MoveConstructible<void>);
static_assert(cjdb::MoveConstructible<int>);
static_assert(cjdb::MoveConstructible<const int>);
static_assert(not cjdb::MoveConstructible<int[4]>);
static_assert(not cjdb::MoveConstructible<void()>);
static_assert(cjdb::MoveConstructible<int &>);
static_assert(cjdb::MoveConstructible<int &&>);
static_assert(cjdb::MoveConstructible<const int &>);
static_assert(cjdb::MoveConstructible<const int &&>);

static_assert(cjdb::MoveConstructible<copyable>);
static_assert(cjdb::MoveConstructible<moveonly>);
static_assert(not cjdb::MoveConstructible<nonmovable>);
static_assert(not cjdb::MoveConstructible<copyonly>);
static_assert(not cjdb::MoveConstructible<explicit_move>);
static_assert(cjdb::MoveConstructible<explicit_copy>);

static_assert(cjdb::MoveConstructible<nonmovable &>);
static_assert(cjdb::MoveConstructible<nonmovable &&>);
static_assert(cjdb::MoveConstructible<const nonmovable &>);
static_assert(cjdb::MoveConstructible<const nonmovable &&>);

int main() {}
