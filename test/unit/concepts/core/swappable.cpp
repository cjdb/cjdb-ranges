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
#include "cjdb/concepts/core/swappable.hpp"

#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/type_traits/type_traits.hpp"
#include "cjdb/test/simple_test.hpp"

namespace swappable_test {
   static_assert(cjdb::swappable<int>);
   static_assert(cjdb::swappable_with<int&, int&>);
   static_assert(cjdb::swappable<int[4]>); // NOLINT(modernize-avoid-c-arrays,readability-magic-numbers)
   static_assert(cjdb::swappable_with<int(&)[4], int(&)[4]>); // NOLINT(modernize-avoid-c-arrays,readability-magic-numbers)
   static_assert(not cjdb::swappable_with<int, int>);
   static_assert(not cjdb::swappable_with<int&, double&>);
   static_assert(not cjdb::swappable_with<int(&)[4], bool(&)[4]>); // NOLINT(modernize-avoid-c-arrays,readability-magic-numbers)
   static_assert(not cjdb::swappable<int[]>);    // NOLINT(modernize-avoid-c-arrays,readability-magic-numbers)
   static_assert(not cjdb::swappable<int[][4]>); // NOLINT(modernize-avoid-c-arrays,readability-magic-numbers)

   static_assert(noexcept(cjdb::ranges::swap(std::declval<int&>(), std::declval<int&>())));
   static_assert(std::is_nothrow_swappable_with_v<int&, int&>);
   static_assert(std::is_nothrow_swappable_with_v<int(&)[42], int(&)[42]>); // NOLINT(modernize-avoid-c-arrays,readability-magic-numbers)

   static_assert(cjdb::swappable<int[3][4]>); // NOLINT(modernize-avoid-c-arrays)
   static_assert(cjdb::swappable_with<int(&)[3][4], int(&)[3][4]>); // NOLINT(modernize-avoid-c-arrays,readability-magic-numbers)
   static_assert(cjdb::swappable<int[3][4][1][2]>); // NOLINT(modernize-avoid-c-arrays,readability-magic-numbers)
   static_assert(cjdb::swappable_with<int(&)[3][4][1][2], int(&)[3][4][1][2]>); // NOLINT(modernize-avoid-c-arrays,readability-magic-numbers)
   static_assert(not cjdb::swappable_with<int(&)[3][4][1][2], int(&)[4][4][1][2]>); // NOLINT(modernize-avoid-c-arrays,readability-magic-numbers)
   static_assert(std::is_nothrow_swappable_with_v<int(&)[6][7], int(&)[6][7]>); // NOLINT(modernize-avoid-c-arrays,readability-magic-numbers)

   // Has std:: as an associated namespace
   struct unswappable : std::string { // NOLINT(cppcoreguidelines-special-member-functions)
      [[maybe_unused]] unswappable() = default;
      [[maybe_unused]] unswappable(const unswappable&) = delete;
      [[maybe_unused]] unswappable(unswappable&&) = delete;
   };
   static_assert(not cjdb::swappable_with<unswappable&, unswappable&>);

   namespace detail::constrained_swappable {
      // Has a constrained swap findable via ADL:
      struct constrained_swappable { // NOLINT(cppcoreguidelines-special-member-functions)
         [[maybe_unused]] constrained_swappable() = default;
         [[maybe_unused]] constrained_swappable(const constrained_swappable&) = default;
         [[maybe_unused]] constrained_swappable(constrained_swappable&&) = default;
      };
      template <class T>
      concept ConstrainedSwappable =
         cjdb::same_as<T, constrained_swappable>;
      template <ConstrainedSwappable T, ConstrainedSwappable U>
      void swap(T&, U&) {}
      template <ConstrainedSwappable T>
      void swap(T &, T &) {}
   } // namespace detail::constrained_swappable
   using detail::constrained_swappable::constrained_swappable;
   static_assert(cjdb::swappable_with<constrained_swappable&, constrained_swappable&>);
   static_assert(not cjdb::swappable_with<const volatile constrained_swappable&, const volatile constrained_swappable&>);

   namespace {
      struct A { // NOLINT(cppcoreguidelines-special-member-functions)
         [[maybe_unused]] A() = default;
         A(A&&) = delete;
         A& operator=(A&&) = delete;
         [[maybe_unused]] friend void swap(A&, A&) noexcept {}
      };

      static_assert(cjdb::swappable<A>);
      static_assert(noexcept(cjdb::ranges::swap(std::declval<A&>(), std::declval<A&>())));
      static_assert(std::is_nothrow_swappable_with_v<A&, A&>);
   } // namespace

   namespace {
      struct B {
         [[maybe_unused]] friend void swap(B&, B&) {}
      };

      static_assert(cjdb::swappable<B>);
      static_assert(not noexcept(cjdb::ranges::swap(std::declval<B&>(), std::declval<B&>())));
      static_assert(not std::is_nothrow_swappable_with_v<B&, B&>);
   } // namespace
} // namespace swappable_test



namespace ranges = cjdb::ranges;

template<class T, cjdb::swappable_with<T> U>
void value_swap(T&& t, U&& u) {
   ranges::swap(std::forward<T>(t), std::forward<U>(u));
}

template<cjdb::swappable T>
void lv_swap(T& t1, T& t2) {
ranges::swap(t1, t2);
}

// From [concept.swappable]/5
namespace N {
   struct A { int m; };
   struct Proxy {
      A* a; // NOLINT(misc-non-private-member-variables-in-classes)
      Proxy(A& a) : a{&a} {} // NOLINT(google-explicit-constructor)
      friend void swap(Proxy&& x, Proxy&& y) {
         ranges::swap(x.a, y.a);
      }
   };
   Proxy proxy(A& a) { return Proxy{ a }; }
   void swap(A& x, Proxy p) {
      ranges::swap(x.m, p.a->m);
   }
   void swap(Proxy p, A& x) { swap(x, p); } // satisfy symmetry requirement
} // namespace N

int main()
{
   { // From [concept.swappable]/5
      auto i = 1;
      auto j = 2;
      lv_swap(i, j);
      CHECK(i == 2);
      CHECK(j == 1);
      auto a1 = N::A{5};  // NOLINT(readability-magic-numbers)
      auto a2 = N::A{-5}; // NOLINT(readability-magic-numbers)
      value_swap(a1, proxy(a2));
      CHECK(a1.m == -5);
      CHECK(a2.m == 5);
   }
   { // From cmcstl2
      int a[2][2] = {{0, 1}, {2, 3}}; // NOLINT(modernize-avoid-c-arrays,readability-magic-numbers)
      int b[2][2] = {{4, 5}, {6, 7}}; // NOLINT(modernize-avoid-c-arrays,readability-magic-numbers)

      static_assert(cjdb::swappable_with<decltype((a)),decltype((b))>);
      cjdb::ranges::swap(a, b);
      static_assert(noexcept(cjdb::ranges::swap(a, b)));

      CHECK(a[0][0] == 4); // NOLINT(readability-magic-numbers)
      CHECK(a[0][1] == 5); // NOLINT(readability-magic-numbers)
      CHECK(a[1][0] == 6); // NOLINT(readability-magic-numbers)
      CHECK(a[1][1] == 7); // NOLINT(readability-magic-numbers)

      CHECK(b[0][0] == 0);
      CHECK(b[0][1] == 1);
      CHECK(b[1][0] == 2);
      CHECK(b[1][1] == 3);
   }

   return ::test_result();
}
