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
#include "cjdb/concepts/object/movable.hpp"

#include "../object.hpp"

static_assert(cjdb::movable<int>);
static_assert(not cjdb::movable<const int>);
static_assert(cjdb::movable<double>);
static_assert(not cjdb::movable<void>);
static_assert(cjdb::movable<copyable>);
static_assert(cjdb::movable<moveonly>);
static_assert(not cjdb::movable<nonmovable>);
static_assert(not cjdb::movable<copyonly>);

// https://github.com/ericniebler/stl2/issues/310
static_assert(not cjdb::movable<int&&>);

int main() {}
