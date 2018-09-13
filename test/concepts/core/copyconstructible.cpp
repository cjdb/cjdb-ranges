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
#include "cjdb/detail/concepts/core/copyconstructible.hpp"

#include "../object.hpp"

static_assert(not cjdb::CopyConstructible<void>);
static_assert(cjdb::CopyConstructible<int>);
static_assert(cjdb::CopyConstructible<const int>);
static_assert(cjdb::CopyConstructible<int&>);
static_assert(not cjdb::CopyConstructible<int&&>);
static_assert(cjdb::CopyConstructible<const int&>);
static_assert(not cjdb::CopyConstructible<const int&&>);
static_assert(not cjdb::CopyConstructible<int[4]>);
static_assert(not cjdb::CopyConstructible<void()>);

static_assert(cjdb::CopyConstructible<copyable>);
static_assert(not cjdb::CopyConstructible<moveonly>);
static_assert(not cjdb::CopyConstructible<nonmovable>);
static_assert(not cjdb::CopyConstructible<copyonly>);
static_assert(not cjdb::CopyConstructible<explicit_move>);
static_assert(not cjdb::CopyConstructible<explicit_copy>);
static_assert(cjdb::CopyConstructible<nonmovable &>);
static_assert(not cjdb::CopyConstructible<nonmovable &&>);
static_assert(cjdb::CopyConstructible<const nonmovable &>);
static_assert(not cjdb::CopyConstructible<const nonmovable &&>);

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
static_assert(not cjdb::CopyConstructible<not_mutable_ref>);
static_assert(not cjdb::CopyConstructible<not_const_ref_ref>);

int main() {}
