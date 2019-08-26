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
#include "cjdb/concepts/core/default_initializable.hpp"

#include "../object.hpp"
#include <initializer_list>

static_assert(cjdb::default_initializable<int>);
static_assert(cjdb::default_initializable<int const>);
static_assert(not cjdb::default_initializable<int&>);
static_assert(not cjdb::default_initializable<int const&>);
static_assert(not cjdb::default_initializable<int()>);
static_assert(not cjdb::default_initializable<int(&)()>);
static_assert(cjdb::default_initializable<double>);
static_assert(not cjdb::default_initializable<void>);
static_assert(not cjdb::default_initializable<int[]>);
static_assert(cjdb::default_initializable<int[2]>);
static_assert(not cjdb::default_initializable<nondefaultconstructible>);

// It's hard to catch explicit default constructors, see
// http://www.open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#1518.
// static_assert(not cjdb::default_initializable<explicit_default>);
static_assert(cjdb::default_initializable<explicit_move>);
static_assert(cjdb::default_initializable<explicit_copy>);
static_assert(not cjdb::default_initializable<deleted_default>);

static_assert(cjdb::default_initializable<std::initializer_list<int>>);
static_assert(cjdb::default_initializable<int*>);

int main() {}
