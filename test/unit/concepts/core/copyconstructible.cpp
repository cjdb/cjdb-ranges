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
#include "cjdb/concepts/core/copy_constructible.hpp"

#include "../object.hpp"

static_assert(not cjdb::copy_constructible<void>);
static_assert(cjdb::copy_constructible<int>);
static_assert(cjdb::copy_constructible<const int>);
static_assert(cjdb::copy_constructible<int&>);
static_assert(not cjdb::copy_constructible<int&&>);
static_assert(cjdb::copy_constructible<const int&>);
static_assert(not cjdb::copy_constructible<const int&&>);
static_assert(not cjdb::copy_constructible<int[4]>); // NOLINT(modernize-avoid-c-arrays)
static_assert(not cjdb::copy_constructible<void()>);

static_assert(cjdb::copy_constructible<copyable>);
static_assert(not cjdb::copy_constructible<moveonly>);
static_assert(not cjdb::copy_constructible<nonmovable>);
static_assert(not cjdb::copy_constructible<copyonly>);
static_assert(not cjdb::copy_constructible<explicit_move>);
static_assert(not cjdb::copy_constructible<explicit_copy>);
static_assert(cjdb::copy_constructible<nonmovable &>);
static_assert(not cjdb::copy_constructible<nonmovable &&>);
static_assert(cjdb::copy_constructible<const nonmovable &>);
static_assert(not cjdb::copy_constructible<const nonmovable &&>);

// https://github.com/ericniebler/stl2/issues/301
struct not_mutable_ref { // NOLINT(cppcoreguidelines-special-member-functions)
   not_mutable_ref() = default;
   not_mutable_ref(const not_mutable_ref&) = default;
   not_mutable_ref(not_mutable_ref&&) = default;
   not_mutable_ref(not_mutable_ref&) = delete;
};
struct not_const_ref_ref { // NOLINT(cppcoreguidelines-special-member-functions)
   not_const_ref_ref() = default;
   not_const_ref_ref(const not_const_ref_ref&) = default;
   not_const_ref_ref(not_const_ref_ref&&) = default;
   not_const_ref_ref(const not_const_ref_ref&&) = delete;
};
static_assert(not cjdb::copy_constructible<not_mutable_ref>);
static_assert(not cjdb::copy_constructible<not_const_ref_ref>);

int main() {}
