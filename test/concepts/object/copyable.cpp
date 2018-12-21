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
#include "cjdb/concepts/object/copyable.hpp"

#include "../object.hpp"

static_assert(cjdb::Copyable<int>);
static_assert(not cjdb::Copyable<const int>);
static_assert(cjdb::Copyable<double>);
static_assert(not cjdb::Copyable<void>);
static_assert(cjdb::Copyable<copyable>);
static_assert(not cjdb::Copyable<moveonly>);
static_assert(not cjdb::Copyable<nonmovable>);
static_assert(not cjdb::Copyable<copyonly>);

int main() {}
