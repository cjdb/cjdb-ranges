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
#include "cjdb/concepts/core/move_constructible.hpp"

#include "../object.hpp"

static_assert(not cjdb::move_constructible<void>);
static_assert(cjdb::move_constructible<int>);
static_assert(cjdb::move_constructible<const int>);
static_assert(not cjdb::move_constructible<int[4]>);
static_assert(not cjdb::move_constructible<void()>);
static_assert(cjdb::move_constructible<int &>);
static_assert(cjdb::move_constructible<int &&>);
static_assert(cjdb::move_constructible<const int &>);
static_assert(cjdb::move_constructible<const int &&>);

static_assert(cjdb::move_constructible<copyable>);
static_assert(cjdb::move_constructible<moveonly>);
static_assert(not cjdb::move_constructible<nonmovable>);
static_assert(not cjdb::move_constructible<copyonly>);
static_assert(not cjdb::move_constructible<explicit_move>);
static_assert(cjdb::move_constructible<explicit_copy>);

static_assert(cjdb::move_constructible<nonmovable &>);
static_assert(cjdb::move_constructible<nonmovable &&>);
static_assert(cjdb::move_constructible<const nonmovable &>);
static_assert(cjdb::move_constructible<const nonmovable &&>);

int main() {}
