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
#ifndef CJDB_TEST_CONCEPTS_OBJECT_HPP
#define CJDB_TEST_CONCEPTS_OBJECT_HPP

struct copyable {};

struct moveonly {
   moveonly() = default;
   moveonly(moveonly&&) = default;
   moveonly& operator=(moveonly&&) = default;
};

struct copyonly {
   copyonly() = default;
   copyonly(const copyonly&) = default;
   copyonly& operator=(const copyonly&) = default;
   copyonly(copyonly&&) = delete;
   copyonly& operator=(copyonly&&) = delete;
};

struct nonmovable {
   nonmovable() = default;
   nonmovable(nonmovable&&) = delete;
};

struct nondefaultconstructible {
   nondefaultconstructible(int) {}
};

struct indestructible {
   ~indestructible() = delete;
};

struct throwing_destructor {
   ~throwing_destructor() noexcept(false);
};

struct explicit_default {
   explicit explicit_default() {}
};

struct deleted_default {
   deleted_default() = delete;
};

struct explicit_move {
   explicit_move() = default;
   explicit explicit_move(explicit_move&&) = default;
};

struct explicit_copy {
   explicit_copy() = default;
   explicit_copy(explicit_copy&&) = default;
   explicit explicit_copy(const explicit_copy&) = default;
};

struct semiregular {};

struct regular {
   friend constexpr bool operator==(const regular&, const regular&) {
      return true;
   }
   friend constexpr bool operator!=(const regular&, const regular&) {
      return false;
   }
};

struct XXX
{
   XXX() = default;
   XXX(XXX&&) = delete;
   explicit XXX(int) {}
};

#endif // CJDB_TEST_CONCEPTS_OBJECT_HPP
