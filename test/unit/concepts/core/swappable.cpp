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
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "cjdb/detail/concepts/core/swappable.hpp"

#include "cjdb/detail/concepts/core/same.hpp"
#include "cjdb/detail/type_traits/type_traits.hpp"
#include <doctest.h>

namespace swappable_test {
   static_assert(cjdb::Swappable<int>);
   static_assert(cjdb::SwappableWith<int&, int&>);
   static_assert(cjdb::Swappable<int[4]>);
   static_assert(cjdb::SwappableWith<int(&)[4], int(&)[4]>);
   static_assert(not cjdb::SwappableWith<int, int>);
   static_assert(not cjdb::SwappableWith<int&, double&>);
   static_assert(not cjdb::SwappableWith<int(&)[4], bool(&)[4]>);
   static_assert(not cjdb::Swappable<int[]>);
   static_assert(not cjdb::Swappable<int[][4]>);

   static_assert(noexcept(cjdb::ranges::swap(std::declval<int&>(), std::declval<int&>())));
   static_assert(std::is_nothrow_swappable_with_v<int&, int&>);
   static_assert(std::is_nothrow_swappable_with_v<int(&)[42], int(&)[42]>);

   static_assert(cjdb::Swappable<int[3][4]>);
   static_assert(cjdb::SwappableWith<int(&)[3][4], int(&)[3][4]>);
   static_assert(cjdb::Swappable<int[3][4][1][2]>);
   static_assert(cjdb::SwappableWith<int(&)[3][4][1][2], int(&)[3][4][1][2]>);
   static_assert(not cjdb::SwappableWith<int(&)[3][4][1][2], int(&)[4][4][1][2]>);
   static_assert(std::is_nothrow_swappable_with_v<int(&)[6][7], int(&)[6][7]>);

   // Has std:: as an associated namespace
   struct unswappable : std::string { // NOLINT(cppcoreguidelines-special-member-functions)
      unswappable() = default;
      unswappable(const unswappable&) = delete;
      unswappable(unswappable&&) = delete;
   };
   static_assert(not cjdb::SwappableWith<unswappable&, unswappable&>);

   namespace detail::constrained_swappable {
      // Has a constrained swap findable via ADL:
      struct constrained_swappable { // NOLINT(cppcoreguidelines-special-member-functions)
         constrained_swappable() = default;
         constrained_swappable(const constrained_swappable&) = default;
         constrained_swappable(constrained_swappable&&) = default;
      };
      template <class T>
      concept ConstrainedSwappable =
         cjdb::Same<T, constrained_swappable>;
      template <ConstrainedSwappable T, ConstrainedSwappable U>
      void swap(T&, U&) {}
      template <ConstrainedSwappable T>
      void swap(T &, T &) {}
   } // namespace detail::constrained_swappable
   using detail::constrained_swappable::constrained_swappable;
   static_assert(cjdb::SwappableWith<constrained_swappable&, constrained_swappable&>);
   static_assert(not cjdb::SwappableWith<const volatile constrained_swappable&, const volatile constrained_swappable&>);

   namespace {
      struct A { // NOLINT(cppcoreguidelines-special-member-functions)
         A() = default;
         A(A&&) = delete;
         A& operator=(A&&) = delete;
         [[maybe_unused]] friend void swap(A&, A&) noexcept {}
      };

      static_assert(cjdb::Swappable<A>);
      static_assert(noexcept(cjdb::ranges::swap(std::declval<A&>(), std::declval<A&>())));
      static_assert(std::is_nothrow_swappable_with_v<A&, A&>);
   } // namespace

   namespace {
      struct B {
         [[maybe_unused]] friend void swap(B&, B&) {}
      };

      static_assert(cjdb::Swappable<B>);
      static_assert(not noexcept(cjdb::ranges::swap(std::declval<B&>(), std::declval<B&>())));
      static_assert(not std::is_nothrow_swappable_with_v<B&, B&>);
   } // namespace
} // namespace swappable_test



namespace ranges = cjdb::ranges;

template<class T, cjdb::SwappableWith<T> U>
void value_swap(T&& t, U&& u) {
ranges::swap(std::forward<T>(t), std::forward<U>(u));
}

template<cjdb::Swappable T>
void lv_swap(T& t1, T& t2) {
ranges::swap(t1, t2);
}

// From [concept.swappable]/5
namespace N {
   struct A { int m; };
   struct Proxy {
      A* a_;
      Proxy(A& a) : a_{&a} {}
      friend void swap(Proxy&& x, Proxy&& y) {
         ranges::swap(x.a_, y.a_);
      }
   };
   Proxy proxy(A& a) { return Proxy{ a }; }
   void swap(A& x, Proxy p) {
      ranges::swap(x.m, p.a_->m);
   }
   void swap(Proxy p, A& x) { swap(x, p); } // satisfy symmetry requirement
}

TEST_CASE("Test [concepts.swappable]") {
   { // From [concept.swappable]/5
      int i = 1, j = 2;
      lv_swap(i, j);
      CHECK(i == 2);
      CHECK(j == 1);
      N::A a1 = { 5 }, a2 = { -5 };
      value_swap(a1, proxy(a2));
      CHECK(a1.m == -5);
      CHECK(a2.m == 5);
   }
   { // From cmcstl2
      int a[2][2] = {{0, 1}, {2, 3}};
      int b[2][2] = {{4, 5}, {6, 7}};

      static_assert(cjdb::SwappableWith<decltype((a)),decltype((b))>);
      cjdb::ranges::swap(a, b);
      static_assert(noexcept(cjdb::ranges::swap(a, b)));

      CHECK(a[0][0] == 4);
      CHECK(a[0][1] == 5);
      CHECK(a[1][0] == 6);
      CHECK(a[1][1] == 7);

      CHECK(b[0][0] == 0);
      CHECK(b[0][1] == 1);
      CHECK(b[1][0] == 2);
      CHECK(b[1][1] == 3);
   }
}
