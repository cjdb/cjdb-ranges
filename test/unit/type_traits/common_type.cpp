//
//  Copyright Christopher Di Bella
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "cjdb/type_traits/common_type.hpp"
#include "cjdb/type_traits/common_reference.hpp"

#include <array>
#include <doctest.h>
#include <functional>
#include <initializer_list>
#include <tuple>
#include "cjdb/type_traits/type_traits.hpp"
#include <utility>

template <typename>
constexpr auto has_trait = false;

template <typename T>
requires requires {
   typename cjdb::_t<T>;
}
constexpr auto has_trait<T> = true;

template <typename T>
concept Trait = has_trait<T>;

template<template<class...> class T, class... Args>
concept Valid = requires { typename T<Args...>; };

using cjdb::common_type, cjdb::common_type_t;
using cjdb::common_reference, cjdb::common_reference_t;

// template <typename Expected, typename... T>
// requires (sizeof...(T) > 0) and
//    has_trait<common_type<T...>>
// void check_common_type_impl()
// {
//    static_assert(std::is_same_v<common_type_t<T...>, Expected>);
//    static_assert(std::is_same_v<common_type_t<std::add_const_t<T>...>, Expected>);
//    static_assert(std::is_same_v<common_type_t<std::add_volatile_t<T>...>, Expected>);
//    static_assert(std::is_same_v<common_type_t<std::add_cv_t<T>...>, Expected>);

//    if constexpr (has_trait<common_type<std::add_pointer_t<T>...>>) {
//       static_assert(std::is_same_v<common_type_t<std::add_pointer_t<T>...>, Expected*>);
//       static_assert(std::is_same_v<common_type_t<std::add_pointer_t<std::add_const_t<T>>...>, Expected const*>);
//       static_assert(std::is_same_v<common_type_t<std::add_pointer_t<std::add_volatile_t<T>>...>, Expected volatile*>);
//       static_assert(std::is_same_v<common_type_t<std::add_pointer_t<std::add_cv_t<T>>...>, Expected const volatile*>);
//    }

//    static_assert(std::is_same_v<common_type_t<std::add_lvalue_reference_t<T>...>, Expected>);
//    static_assert(std::is_same_v<common_type_t<std::add_lvalue_reference_t<std::add_const_t<T>>...>, Expected>);
//    static_assert(std::is_same_v<common_type_t<std::add_lvalue_reference_t<std::add_volatile_t<T>>...>, Expected>);
//    static_assert(std::is_same_v<common_type_t<std::add_lvalue_reference_t<std::add_cv_t<T>>...>, Expected>);

//    static_assert(std::is_same_v<common_type_t<std::add_rvalue_reference_t<T>...>, Expected>);
//    static_assert(std::is_same_v<common_type_t<std::add_rvalue_reference_t<std::add_const_t<T>>...>, Expected>);
//    static_assert(std::is_same_v<common_type_t<std::add_rvalue_reference_t<std::add_volatile_t<T>>...>, Expected>);
//    static_assert(std::is_same_v<common_type_t<std::add_rvalue_reference_t<std::add_cv_t<T>>...>, Expected>);
// }

// template <typename Expected, typename T>
// requires has_trait<common_type<T>>
// void check_common_type()
// {
//    check_common_type_impl<Expected, T>();
// }

// template <typename Expected, typename T1, typename T2>
// requires has_trait<common_type<T1, T2>>
// void check_common_type()
// {
//    check_common_type_impl<Expected, T1, T2>();
//    check_common_type_impl<Expected, T2, T1>();
// }

// template <typename Expected, typename T1, typename T2, typename T3>
// requires has_trait<common_type<T1, T2, T3>>
// void check_common_type()
// {
//    check_common_type_impl<Expected, T1, T2, T3>();
//    check_common_type_impl<Expected, T1, T3, T2>();
//    check_common_type_impl<Expected, T2, T1, T3>();
//    check_common_type_impl<Expected, T2, T3, T1>();
//    check_common_type_impl<Expected, T3, T1, T2>();
//    check_common_type_impl<Expected, T3, T2, T1>();
// }

// template <typename Expected, typename T1, typename T2, typename T3, typename T4>
// requires has_trait<common_type<T1, T2, T3, T4>>
// void check_common_type()
// {
//    check_common_type_impl<Expected, T1, T2, T3, T4>();
//    check_common_type_impl<Expected, T1, T2, T4, T3>();
//    check_common_type_impl<Expected, T1, T3, T2, T4>();
//    check_common_type_impl<Expected, T1, T3, T4, T2>();
//    check_common_type_impl<Expected, T1, T4, T2, T3>();
//    check_common_type_impl<Expected, T1, T4, T3, T2>();

//    check_common_type_impl<Expected, T2, T1, T3, T4>();
//    check_common_type_impl<Expected, T2, T1, T4, T3>();
//    check_common_type_impl<Expected, T2, T3, T1, T4>();
//    check_common_type_impl<Expected, T2, T3, T4, T1>();
//    check_common_type_impl<Expected, T2, T4, T1, T3>();
//    check_common_type_impl<Expected, T2, T4, T3, T1>();

//    check_common_type_impl<Expected, T3, T2, T1, T4>();
//    check_common_type_impl<Expected, T3, T2, T4, T1>();
//    check_common_type_impl<Expected, T3, T1, T2, T4>();
//    check_common_type_impl<Expected, T3, T1, T4, T2>();
//    check_common_type_impl<Expected, T3, T4, T2, T1>();
//    check_common_type_impl<Expected, T3, T4, T1, T2>();

//    check_common_type_impl<Expected, T4, T2, T3, T1>();
//    check_common_type_impl<Expected, T4, T2, T1, T3>();
//    check_common_type_impl<Expected, T4, T3, T2, T1>();
//    check_common_type_impl<Expected, T4, T3, T1, T2>();
//    check_common_type_impl<Expected, T4, T1, T2, T3>();
//    check_common_type_impl<Expected, T4, T1, T3, T2>();
// }

// template <typename T1, typename T2>
// void check_no_common_type()
// {
//    // lvalues
//    static_assert(not has_trait<common_type<T1, T2>>);
//    static_assert(not has_trait<common_type<T2, T1>>);

//    static_assert(not has_trait<common_type<T1 const, T2 const>>);
//    static_assert(not has_trait<common_type<T2 const, T1 const>>);

//    static_assert(not has_trait<common_type<T1 volatile, T2 volatile>>);
//    static_assert(not has_trait<common_type<T2 volatile, T1 volatile>>);

//    static_assert(not has_trait<common_type<T1 const volatile, T2 const volatile>>);
//    static_assert(not has_trait<common_type<T2 const volatile, T1 const volatile>>);

//    // pointers
//    static_assert(not has_trait<common_type<T1*, T2*>>);
//    static_assert(not has_trait<common_type<T2*, T1*>>);

//    static_assert(not has_trait<common_type<T1 const*, T2 const*>>);
//    static_assert(not has_trait<common_type<T2 const*, T1 const*>>);

//    static_assert(not has_trait<common_type<T1 volatile*, T2 volatile*>>);
//    static_assert(not has_trait<common_type<T2 volatile*, T1 volatile*>>);

//    static_assert(not has_trait<common_type<T1 const volatile*, T2 const volatile*>>);
//    static_assert(not has_trait<common_type<T2 const volatile*, T1 const volatile*>>);

//    // lvalue references
//    static_assert(not has_trait<common_type<T1&, T2&>>);
//    static_assert(not has_trait<common_type<T2&, T1&>>);

//    static_assert(not has_trait<common_type<T1 const&, T2 const&>>);
//    static_assert(not has_trait<common_type<T2 const&, T1 const&>>);

//    static_assert(not has_trait<common_type<T1 volatile&, T2 volatile&>>);
//    static_assert(not has_trait<common_type<T2 volatile&, T1 volatile&>>);

//    static_assert(not has_trait<common_type<T1 const volatile&, T2 const volatile&>>);
//    static_assert(not has_trait<common_type<T2 const volatile&, T1 const volatile&>>);

//    // rvalue references
//    static_assert(not has_trait<common_type<T1&&, T2&&>>);
//    static_assert(not has_trait<common_type<T2&&, T1&&>>);

//    static_assert(not has_trait<common_type<T1 const&&, T2 const&&>>);
//    static_assert(not has_trait<common_type<T2 const&&, T1 const&&>>);

//    static_assert(not has_trait<common_type<T1 volatile&&, T2 volatile&&>>);
//    static_assert(not has_trait<common_type<T2 volatile&&, T1 volatile&&>>);

//    static_assert(not has_trait<common_type<T1 const volatile&&, T2 const volatile&&>>);
//    static_assert(not has_trait<common_type<T2 const volatile&&, T1 const volatile&&>>);
// }

// struct S1 {};
// struct S2 : S1 {};
// struct S3 {};
// struct S4 : private S1 {};
// struct S5 : protected S2 {};
// struct S6 : S2 {};
// struct S7 : S2 {};

// TEST_CASE("") {
//    SECTION("Zero-sized common_type_t") {
//       static_assert(not has_trait<common_type<>>);
//    }

//    SECTION("common_type_t with only one parameter") {
//       check_common_type<int, int>();
//       check_common_type<S1, S1>();
//       check_common_type<S2, S2>();
//    }

//    SECTION("common_type_t with two homogeneous parameters") {
//       check_common_type<int, int, int>();
//       check_common_type<S1, S1, S1>();
//       check_common_type<S2, S2, S2>();
//    }

//    SECTION("common_type_t with two unrelated parameters") {
//       check_no_common_type<S1, int>();
//       check_no_common_type<S2, int>();
//       check_no_common_type<S1, S3>();
//       check_no_common_type<S2, S3>();

//       SECTION("non-public inheritance inhibits common_type_t") {
//          check_no_common_type<int, int*>();
//          check_no_common_type<int*, double*>();
//          check_no_common_type<S1, S4>();
//          check_no_common_type<S1, S5>();
//          check_no_common_type<S2, S4>();
//          check_no_common_type<S2, S5>();
//          check_no_common_type<S4, S5>();
//          check_no_common_type<S6, S7>();
//       }
//    }

//    SECTION("common_type_t with two related parameters") {
//       check_common_type<long long, int, long long>();
//       check_common_type<int, char, wchar_t>();
//       check_common_type<int, signed char, char>();
//       check_common_type<int, signed char, unsigned char>();
//       check_common_type<int, int, wchar_t>();
//       check_common_type<double, int, double>();
//       check_common_type<S1, S1, S2>();
//       check_common_type<S2, S2, S6>();
//       check_common_type<S2, S2, S7>();
//       check_common_type<S1, S1, S6>();
//       check_common_type<S1, S1, S7>();
//    }

//    SECTION("common_type_t with three parameters (homogeneous)") {
//       check_common_type<int, int, int, int>();
//       check_common_type<S1, S1, S1, S1>();
//       check_common_type<S2, S2, S2, S2>();
//    }

//    SECTION("common_type_t with four parameters (homogeneous)") {
//       check_common_type<int, int, int, int, int>();
//       check_common_type<S1, S1, S1, S1, S1>();
//       check_common_type<S2, S2, S2, S2, S2>();
//    }
// }

// cmcstl2 - A concept-enabled C++ standard library
//
//  Copyright Eric Niebler 2015
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Derived from: https://github.com/caseycarter/cmcstl2
// Project home: https://github.com/cjdb/clang-concepts-ranges
//

static_assert(std::is_same_v<common_type_t<int, short&, int, char>, int>);
static_assert(not has_trait<common_type<int, short, int, char*>>);

struct X {};
struct Y { explicit Y(X){} };

namespace cjdb {
   template<> struct common_type<X, Y> { using type = Y; };
   template<> struct common_type<Y, X> { using type = Y; };
} // namespace cjdb

static_assert(std::is_same_v<common_type_t<X, Y>, Y>);    // (A)
static_assert(std::is_same_v<common_type_t<X, Y, Y>, Y>); // (B)
static_assert(std::is_same_v<common_type_t<X, X, Y>, Y>); // (C)

struct AA { // NOLINT(cppcoreguidelines-special-member-functions)
   AA() = default;
   AA(AA &&) = delete;
   AA(AA const &) = delete;
};
struct BB : AA { };

static_assert(std::is_same_v<common_type_t<AA, BB>, AA>); // (C)

static_assert(std::is_same_v<common_reference_t<int &&, int const &, int volatile &>, int const volatile &>);
static_assert(std::is_same_v<common_reference_t<int &&, int const &, float &>, float>);
static_assert(not has_trait<common_reference<int, short, int, char*>>);

namespace cjdb {
template<class... T, class... U, template<class> class TQual, template<class> class UQual>
   requires(Valid<common_reference_t, TQual<T>, UQual<U>> && ...)
struct basic_common_reference<std::tuple<T...>, std::tuple<U...>, TQual, UQual> {
   using type = std::tuple<common_reference_t<TQual<T>, UQual<U>>...>;
};
} // namespace cjdb

static_assert(std::is_same_v<
   common_reference_t<const std::tuple<int, short> &, std::tuple<int&,short volatile&>>,
   std::tuple<const int&,const volatile short&>>);

static_assert(std::is_same_v<
   common_reference_t<volatile std::tuple<int, short> &, const std::tuple<int,short>&>,
   const volatile std::tuple<int, short>&>);

static_assert(not has_trait<
   common_reference<volatile std::tuple<short> &, const std::tuple<int,short>&>>);

struct B {};
struct D : B {};

struct noncopyable { // NOLINT(cppcoreguidelines-special-member-functions)
   noncopyable() = default;
   noncopyable(noncopyable const &) = delete;
   noncopyable(noncopyable &&) = default;
   noncopyable &operator=(noncopyable const &) = delete;
   noncopyable &operator=(noncopyable &&) = default;
};

struct noncopyable2 : noncopyable
{};

static_assert(std::is_same_v<common_reference_t<B &, D &>, B &>);
static_assert(std::is_same_v<common_reference_t<B &, D const &>, B const &>);
static_assert(std::is_same_v<common_reference_t<B &, D const &, D &>, B const &>);
static_assert(std::is_same_v<common_reference_t<B const &, D &>, B const &>);
static_assert(std::is_same_v<common_reference_t<B &, D &, B &, D &>, B &>);

static_assert(std::is_same_v<common_reference_t<B &&, D &&>, B &&>);
static_assert(std::is_same_v<common_reference_t<B const &&, D &&>, B const &&>);
static_assert(std::is_same_v<common_reference_t<B &&, D const &&>, B const &&>);

static_assert(std::is_same_v<common_reference_t<B &, D &&>, B const &>);
static_assert(std::is_same_v<common_reference_t<B &, D const &&>, B const &>);
static_assert(std::is_same_v<common_reference_t<B const &, D &&>, B const &>);

static_assert(std::is_same_v<common_reference_t<B &&, D &>, B const &>);
static_assert(std::is_same_v<common_reference_t<B &&, D const &>, B const &>);
static_assert(std::is_same_v<common_reference_t<B const &&, D &>, B const &>);

static_assert(std::is_same_v<common_reference_t<int, short>, int>);
static_assert(std::is_same_v<common_reference_t<int, short &>, int>);
static_assert(std::is_same_v<common_reference_t<int &, short &>, int>);
static_assert(std::is_same_v<common_reference_t<int &, short>, int>);

// tricky volatile reference case
static_assert(std::is_same_v<common_reference_t<int &&, int volatile &>, int>);
static_assert(std::is_same_v<common_reference_t<int volatile &, int &&>, int>);
static_assert(std::is_same_v<common_reference_t<int const volatile &&, int volatile &&>, int const volatile &&>);
static_assert(std::is_same_v<common_reference_t<int &&, int const &, int volatile &>, int const volatile &>);

// Array types?? Yup!
static_assert(std::is_same_v<common_reference_t<int (&)[10], int (&&)[10]>, int const(&)[10]>);
static_assert(std::is_same_v<common_reference_t<int const (&)[10], int volatile (&)[10]>, int const volatile(&)[10]>);
static_assert(std::is_same_v<common_reference_t<int (&)[10], int (&)[11]>, int *>);

// Some tests with noncopyable types
static_assert(std::is_same_v<
   common_reference_t<noncopyable const &, noncopyable>,
   noncopyable
>);

static_assert(std::is_same_v<
   common_reference_t<noncopyable2 const &, noncopyable>,
   noncopyable
>);

static_assert(std::is_same_v<
   common_reference_t<noncopyable const &, noncopyable2>,
   noncopyable
>);

struct X2 {};
struct Y2 {};
struct Z2 {
   explicit Z2(X2);
   explicit Z2(Y2);
};

namespace cjdb {
template<>
struct common_type<X2, Y2>
{
   using type = Z2;
};
template<>
struct common_type<Y2, X2>
{
   using type = Z2;
};
} // namespace cjdb

static_assert(std::is_same_v<
   common_reference_t<X2 &, Y2 const &>,
   Z2
>);

static_assert(std::is_same_v<common_reference_t<void, void>, void>);
static_assert(std::is_same_v<common_type_t<void, void>, void>);
static_assert(std::is_same_v<common_type_t<std::reference_wrapper<int>, int>, int>);

// Test cases taken from libc++
//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
namespace libcpp_tests
{
   struct E {};

   template<class T>
   struct X { explicit X(T const&){} };

   template<class T>
   struct S { explicit S(T const&){} };
}
namespace cjdb {
   template<typename T>
   struct common_type<T, libcpp_tests::S<T>> {
      using type = libcpp_tests::S<T>;
   };
   template<typename T>
   struct common_type<libcpp_tests::S<T>, T> {
      using type = libcpp_tests::S<T>;
   };
} // namespace cjdb
namespace libcpp_tests
{
   template<class T, class U>
   struct no_common_type : std::true_type {};

   template<class T, class U>
   requires requires { typename common_type_t<T, U>; }
   struct no_common_type<T, U> : std::false_type {};

   template <typename T, typename U>
   constexpr auto no_common_type_v = no_common_type<T, U>::value;

    static_assert((std::is_same_v<common_type_t<int>, int>));
    static_assert((std::is_same_v<common_type_t<char>, char>));
    static_assert((std::is_same_v<common_type_t<int>,   int>));
    static_assert((std::is_same_v<common_type_t<char>, char>));

    static_assert((std::is_same_v<common_type_t<               int>, int>));
    static_assert((std::is_same_v<common_type_t<const          int>, int>));
    static_assert((std::is_same_v<common_type_t<      volatile int>, int>));
    static_assert((std::is_same_v<common_type_t<const volatile int>, int>));

    static_assert((std::is_same_v<common_type_t<int,           int>, int>));
    static_assert((std::is_same_v<common_type_t<int,     const int>, int>));

    static_assert((std::is_same_v<common_type_t<long,       const int>, long>));
    static_assert((std::is_same_v<common_type_t<const long,       int>, long>));
    static_assert((std::is_same_v<common_type_t<long,    volatile int>, long>));
    static_assert((std::is_same_v<common_type_t<volatile long,    int>, long>));
    static_assert((std::is_same_v<common_type_t<const long, const int>, long>));

    static_assert((std::is_same_v<common_type_t<double, char>, double>));
    static_assert((std::is_same_v<common_type_t<short, char>, int>));
    static_assert((std::is_same_v<common_type_t<double, char>, double>));
    static_assert((std::is_same_v<common_type_t<short, char>, int>));

    static_assert((std::is_same_v<common_type_t<double, char, long long>, double>));
    static_assert((std::is_same_v<common_type_t<unsigned, char, long long>, long long>));
    static_assert((std::is_same_v<common_type_t<double, char, long long>, double>));
    static_assert((std::is_same_v<common_type_t<unsigned, char, long long>, long long>));

    static_assert((std::is_same_v<common_type_t<               void>, void>));
    static_assert((std::is_same_v<common_type_t<const          void>, void>));
    static_assert((std::is_same_v<common_type_t<      volatile void>, void>));
    static_assert((std::is_same_v<common_type_t<const volatile void>, void>));

    static_assert((std::is_same_v<common_type_t<void,       const void>, void>));
    static_assert((std::is_same_v<common_type_t<const void,       void>, void>));
    static_assert((std::is_same_v<common_type_t<void,    volatile void>, void>));
    static_assert((std::is_same_v<common_type_t<volatile void,    void>, void>));
    static_assert((std::is_same_v<common_type_t<const void, const void>, void>));

    static_assert((no_common_type_v<void, int>));
    static_assert((no_common_type_v<int, void>));
    static_assert((no_common_type_v<int, E>));
    static_assert((no_common_type_v<int, X<int> >));

    static_assert((std::is_same_v<common_type_t<int, S<int> >, S<int> >));
    static_assert((std::is_same_v<common_type_t<int, S<int>, S<int> >, S<int> >));
    static_assert((std::is_same_v<common_type_t<int, int, S<int> >, S<int> >));
}

// libstdc++ tests
//
// Copyright (C) 2009-2016 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.
namespace cjdb {
   using test_type1 = int;
   using test_type2 = int&;
   using test_type3 = double;
   using test_type4 = float;
   using test_type5 = void;
   using test_type6 = void const;

   template struct common_type<test_type1>;
   template struct common_type<test_type1, test_type2>;
   template struct common_type<test_type1, test_type2, test_type3>;
   template struct common_type<test_type1, test_type2, test_type3, test_type4>;

   template struct common_type<test_type5>;
   template struct common_type<test_type5, test_type6>;
} // namespace cjdb

namespace libstdcpp_tests {
   template<typename T, typename Expected>
   constexpr auto is_type = false;

   template<Trait T, typename Expected>
      requires cjdb::same_as<cjdb::_t<T>, Expected>
   constexpr auto is_type<T, Expected> = true;

   // Inspection types:

   struct S {};

   struct B {};
   struct D : B {};

   struct F1 {
      operator void*(); // NOLINT(google-explicit-constructor)
   };
   struct F2 {
      operator void*(); // NOLINT(google-explicit-constructor)
   };

   struct G1 {
      operator const void*(); // NOLINT(google-explicit-constructor)
   };
   struct G2 {
      operator volatile void*(); // NOLINT(google-explicit-constructor)
   };

   template<typename T>
   struct ImplicitTo {
      operator T(); // NOLINT(google-explicit-constructor)
   };

   template<typename T>
   struct ExplicitTo {
      explicit operator T();
   };

   template<typename T>
   struct PrivateImplicitTo
   {
   private:
      operator T(); // NOLINT(google-explicit-constructor)
   };

   [[maybe_unused]] auto lmd1 = [](int, double) {};
   [[maybe_unused]] auto lmd2 = [](int, double) {};

   struct Abstract { // NOLINT(cppcoreguidelines-special-member-functions)
      virtual ~Abstract() = 0;
   };

   enum class ScEn;

   enum UnscEn : int;

   struct Ukn;

   union U {
      int i;
   };

   union U2 {
      long i;
   };

   union UConv1 {
      operator Abstract*(); // NOLINT(google-explicit-constructor)
   };

   union UConv2 {
      operator Abstract*(); // NOLINT(google-explicit-constructor)
   };
}

namespace libstdcpp_tests {
   static_assert(is_type<common_type<int, int>, int>);
   static_assert(is_type<common_type<ScEn, ScEn>, ScEn>);
   static_assert(is_type<common_type<UnscEn, UnscEn>, UnscEn>);
   static_assert(is_type<common_type<UnscEn, int>, int>);
   static_assert(is_type<common_type<int, int, int>, int>);
   static_assert(is_type<common_type<int, int, int, int>, int>);
   static_assert(is_type<common_type<int, int, int, int, int>, int>);
   static_assert(is_type<common_type<S, S>, S>);
   static_assert(is_type<common_type<const S, const S>, S>);
   static_assert(is_type<common_type<std::initializer_list<int>,
         std::initializer_list<int>>, std::initializer_list<int>>);
   static_assert(is_type<common_type<B, D>, B>);
   static_assert(is_type<common_type<D, B>, B>);
   static_assert(is_type<common_type<F1, F2>, void*>);
   static_assert(is_type<common_type<F2, F1>, void*>);
   static_assert(is_type<common_type<G1, G2>, const volatile void*>);
   static_assert(is_type<common_type<G2, G1>, const volatile void*>);
   static_assert(is_type<common_type<int*, const volatile int*>,
         const volatile int*>);
   static_assert(is_type<common_type<void*, const volatile int*>,
         const volatile void*>);
   static_assert(is_type<common_type<void, void>, void>);
   static_assert(is_type<common_type<const void, const void>, void>);
   static_assert(is_type<common_type<int&, int&&>, int>);
   static_assert(is_type<common_type<int&, int&>, int>);
   static_assert(is_type<common_type<int&&, int&&>, int>);
   static_assert(is_type<common_type<int&&, const int&&>, int>);
   static_assert(is_type<common_type<U&, const U&&>, U>);
   static_assert(is_type<common_type<U&, U&>, U>);
   static_assert(is_type<common_type<U&&, U&&>, U>);
   static_assert(is_type<common_type<int B::*, int D::*>, int D::*>);
   static_assert(is_type<common_type<int D::*, int B::*>, int D::*>);
   static_assert(is_type<common_type<const int B::*, volatile int D::*>, const volatile int D::*>);
   static_assert(is_type<common_type<int (B::*)(), int (D::*)()>, int (D::*)()>);
   static_assert(is_type<common_type<int (B::*)() const, int (D::*)() const>, int (D::*)() const>);
   static_assert(is_type<common_type<int[3], int[3]>, int*>);
   static_assert(is_type<common_type<int[1], const int[3]>, const int*>);
   static_assert(is_type<common_type<void(), void()>, void(*)()>);
   static_assert(is_type<common_type<void(&)(), void(&)()>, void(*)()>);
   static_assert(is_type<common_type<void(&)(), void(&&)()>, void(*)()>);
   static_assert(is_type<common_type<void(&&)(), void(&)()>, void(*)()>);
   static_assert(is_type<common_type<void(&&)(), void(&&)()>, void(*)()>);
   static_assert(is_type<common_type<ImplicitTo<int>, int>, int>);
   static_assert(is_type<common_type<ImplicitTo<int>, ImplicitTo<int>>, ImplicitTo<int>>);
   static_assert(is_type<common_type<ImplicitTo<int>, int, ImplicitTo<int>>, int>);
   static_assert(is_type<common_type<ExplicitTo<int>, ExplicitTo<int>>, ExplicitTo<int>>);
   static_assert(is_type<common_type<decltype(lmd1), decltype(lmd1)>,
         decltype(lmd1)>);
   static_assert(is_type<common_type<decltype(lmd1)&, decltype(lmd1)&>,
         decltype(lmd1)>);
   static_assert(is_type<common_type<decltype(lmd1)&, decltype(lmd2)&>,
         void(*)(int, double)>);
   static_assert(is_type<common_type<decltype(nullptr), void*>, void*>);
   static_assert(is_type<common_type<decltype(nullptr), int*>, int*>);
   static_assert(is_type<common_type<const decltype(nullptr)&, int*>, int*>);
   static_assert(is_type<common_type<decltype(nullptr), const volatile int*>, const volatile int*>);
   static_assert(is_type<common_type<decltype(nullptr), int (B::*)()>, int (B::*)()>);
   static_assert(is_type<common_type<decltype(nullptr), int (B::*)() const>, int (B::*)() const>);
   static_assert(is_type<common_type<decltype(nullptr), const int B::*>, const int B::*>);
   static_assert(is_type<common_type<Abstract&, Abstract&>, Abstract>);
   static_assert(is_type<common_type<Ukn&, Ukn&>, Ukn>);
   static_assert(is_type<common_type<ImplicitTo<B&>, B&>, B>);
   static_assert(is_type<common_type<ImplicitTo<B&>&, B&&>, B>);
   static_assert(is_type<common_type<UConv1, const Abstract*&>, const Abstract*>);
   static_assert(is_type<common_type<UConv1, UConv2>, Abstract*>);
   static_assert(is_type<common_type<UConv1&, UConv2&>, Abstract*>);

   static_assert(is_type<common_type<Abstract&&, Abstract&&>, Abstract>);
   static_assert(is_type<common_type<const Abstract&&, const Abstract&&>, Abstract>);
   static_assert(is_type<common_type<volatile Abstract&&, volatile Abstract&&>, Abstract>);
   static_assert(is_type<common_type<Ukn&&, Ukn&&>, Ukn>);
   static_assert(is_type<common_type<const Ukn&&, const Ukn&&>,
         Ukn>);
   static_assert(is_type<common_type<volatile Ukn&&, volatile Ukn&&>,
         Ukn>);

#if 0 // Ditto ill-formed NDR
   static_assert(is_type<common_type<X1, X2>, RX12>);
   static_assert(is_type<common_type<X2, X1>, RX21>);

   static_assert(is_type<common_type<X1, X2, X1>, Y1>);
   static_assert(is_type<common_type<X2, X1, X1>, Y3>);

   static_assert(is_type<common_type<X1, X1, X2>, RX12>);
   static_assert(is_type<common_type<X1, X1, X2, X1>, Y1>);
#endif

   static_assert(not has_trait<common_type<>>);
   static_assert(not has_trait<common_type<int, S>>);
   static_assert(not has_trait<common_type<U, S>>);
   static_assert(not has_trait<common_type<U, U2>>);
   // See https://cplusplus.github.io/LWG/lwg-active.html#2763 and P0435
   //static_assert(not has_trait<common_type<const ImplicitTo<int>, int>>);
   // Unsure about these two:
   //static_assert(not has_trait<common_type<PrivateImplicitTo<int>, int>>);
   //static_assert(not has_trait<common_type<const PrivateImplicitTo<int>,
   //      int>>);
   static_assert(not has_trait<common_type<int, Ukn>>);
   static_assert(not has_trait<common_type<int, Abstract>>);
   static_assert(not has_trait<common_type<Ukn, Abstract>>);
   static_assert(not has_trait<common_type<int, void>>);
   static_assert(not has_trait<common_type<int, const volatile void>>);
   static_assert(not has_trait<common_type<Abstract, void>>);
   static_assert(not has_trait<common_type<Ukn, void>>);
   static_assert(not has_trait<common_type<int[4], void>>);
   static_assert(not has_trait<common_type<ScEn, void>>);
   static_assert(not has_trait<common_type<UnscEn, void>>);
   static_assert(not has_trait<common_type<U, void>>);
   static_assert(not has_trait<common_type<std::initializer_list<int>,
         void>>);
   static_assert(not has_trait<common_type<int, int, int, S>>);
   static_assert(not has_trait<common_type<int, int, S, int>>);
   static_assert(not has_trait<common_type<int, S, int, int>>);
   static_assert(not has_trait<common_type<S, int, int, int>>);
   static_assert(not has_trait<common_type<int, int, void, int, int>>);
   static_assert(not has_trait<common_type<B, S>>);
   static_assert(not has_trait<common_type<int, B, S>>);
   static_assert(not has_trait<common_type<B, int, S>>);
   static_assert(not has_trait<common_type<B, S, int>>);
   static_assert(not has_trait<common_type<int*, double*>>);
   static_assert(not has_trait<common_type<void*, void(*)(...)>>);
   static_assert(not has_trait<common_type<void(*)(), void(*)(...)>>);
   static_assert(not has_trait<common_type<void(*)(), void(S::*)()>>);
   static_assert(not has_trait<common_type<void(S::*)() const,
         void(S::*)()>>);
   static_assert(not has_trait<common_type<int S::*, long S::*>>);
   static_assert(not has_trait<common_type<int S::*, void(S::*)()>>);
   static_assert(not has_trait<common_type<int (B::*)(),
         int (D::*)() const>>);
   static_assert(not has_trait<common_type<int (B::*)() const,
         int (D::*)()>>);
   static_assert(not has_trait<common_type<int, ExplicitTo<int>>>);
   static_assert(not has_trait<common_type<ImplicitTo<int>,
                  ExplicitTo<int>>>);
   static_assert(not has_trait<common_type<ScEn, int>>);
   static_assert(not has_trait<common_type<ScEn, UnscEn>>);
   static_assert(not has_trait<common_type<U, S, Abstract, void, D,
         int (B::*)(), int[5]>>);
   static_assert(not has_trait<common_type<UConv1, Abstract&&>>);
   static_assert(not has_trait<common_type<std::initializer_list<int>,
                  std::initializer_list<long>>>);

   void test(int i)
   {
      [[maybe_unused]] auto local_lmd1 = [=](int, double) { return i + i; };
      [[maybe_unused]] auto local_lmd2 = [=](int, double) { return i - i; }; // NOLINT(misc-redundant-expression)

      static_assert(is_type<common_type<decltype(local_lmd1),
                  decltype(local_lmd1)>, decltype(local_lmd1)>);
      static_assert(is_type<common_type<decltype(local_lmd1)&,
                  decltype(local_lmd1)>, decltype(local_lmd1)>);
      static_assert(is_type<common_type<decltype(local_lmd1)&,
               decltype(local_lmd1)&>, decltype(local_lmd1)>);

      static_assert(not has_trait<common_type<decltype(local_lmd1),
            decltype(lmd1)>>);
      static_assert(not has_trait<common_type<decltype(local_lmd1)&,
            decltype(lmd1)&>>);
      static_assert(not has_trait<common_type<decltype(local_lmd1),
            decltype(local_lmd2)>>);
      static_assert(not has_trait<common_type<decltype(local_lmd1)&,
            decltype(local_lmd2)&>>);
   }

   template<typename... Args>
   constexpr
   std::array<common_type_t<Args...>,
      sizeof...(Args)>
   make_array(Args&&... args)
   {
      using CT = common_type_t<Args...>;
      return std::array<CT, sizeof...(Args)>{static_cast<CT>
         (std::forward<Args>(args))...};
   }

   void test01()
   {
      constexpr auto a1 = make_array(0);
      constexpr auto a2 = make_array(0, 1.2);
      constexpr auto a3 = make_array(5, true, 3.1415f, 'c');

      int i{};
      double d{1.2};
      float f{3.1415f};

      [[maybe_unused]] auto b1 = make_array(i);
      [[maybe_unused]] auto b2 = make_array(i, 1.2);
      [[maybe_unused]] auto b3 = make_array(i, d);
      [[maybe_unused]] auto b4 = make_array(0, d);
      [[maybe_unused]] auto b5 = make_array(i, true, f, 'c');

      static_assert(std::is_same_v<decltype(a1), const std::array<int, 1>>);
      static_assert(std::is_same_v<decltype(a2), const std::array<double, 2>>);
      static_assert(std::is_same_v<decltype(a3), const std::array<float, 4>>);

      static_assert(std::is_same_v<decltype(b1), std::array<int, 1>>);
      static_assert(std::is_same_v<decltype(b2), std::array<double, 2>>);
      static_assert(std::is_same_v<decltype(b3), std::array<double, 2>>);
      static_assert(std::is_same_v<decltype(b4), std::array<double, 2>>);
      static_assert(std::is_same_v<decltype(b5), std::array<float, 4>>);
   }

   #define JOIN( X, Y ) DO_JOIN( X, Y )
   #define DO_JOIN( X, Y ) DO_JOIN2(X,Y)
   #define DO_JOIN2( X, Y ) X##Y

   #define COMMON_TYPE_TEST_1(type1, uid) \
      typedef common_type_t<type1> JOIN(test_t,uid); \
      CHECK( (std::is_same_v<JOIN(test_t,uid), JOIN(test_t,uid)>) ); \
      typedef common_type_t<const type1> JOIN(test_t,JOIN(uid,c)); \
      CHECK( (std::is_same_v<JOIN(test_t,JOIN(uid,c)), \
                  JOIN(test_t,JOIN(uid,c))>) ); \
      typedef common_type_t<volatile type1> JOIN(test_t,JOIN(uid,v)); \
      CHECK( (std::is_same_v<JOIN(test_t,JOIN(uid,v)), \
                  JOIN(test_t,JOIN(uid,v))>) ); \
      typedef common_type_t<const volatile type1> JOIN(test_t,JOIN(uid,cv)); \
      CHECK( (std::is_same_v<JOIN(test_t,JOIN(uid,cv)), \
                  JOIN(test_t,JOIN(uid,cv))>) ); \
      typedef common_type_t<type1 &> JOIN(test_t,JOIN(uid,l)); \
      CHECK( (std::is_same_v<JOIN(test_t,JOIN(uid,l)), \
                  JOIN(test_t,JOIN(uid,l))>) ); \
      typedef common_type_t<const type1 &> JOIN(test_t,JOIN(uid,lc)); \
      CHECK( (std::is_same_v<JOIN(test_t,JOIN(uid,lc)), \
                  JOIN(test_t,JOIN(uid,lc))>) ); \
      typedef common_type_t<volatile type1 &> JOIN(test_t,JOIN(uid,lv)); \
      CHECK( (std::is_same_v<JOIN(test_t,JOIN(uid,lv)), \
                  JOIN(test_t,JOIN(uid,lv))>) ); \
      typedef common_type_t<const volatile type1 &> JOIN(test_t,JOIN(uid,lcv)); \
      CHECK( (std::is_same_v<JOIN(test_t,JOIN(uid,lcv)), \
                  JOIN(test_t,JOIN(uid,lcv))>) ); \
      typedef common_type_t<type1 &&> JOIN(test_t,JOIN(uid,r)); \
      CHECK( (std::is_same_v<JOIN(test_t,JOIN(uid,r)), \
                  JOIN(test_t,JOIN(uid,r))>) ); \
      typedef common_type_t<const type1 &&> JOIN(test_t,JOIN(uid,rc)); \
      CHECK( (std::is_same_v<JOIN(test_t,JOIN(uid,rc)), \
                  JOIN(test_t,JOIN(uid,rc))>) ); \
      typedef common_type_t<volatile type1 &&> JOIN(test_t,JOIN(uid,rv)); \
      CHECK( (std::is_same_v<JOIN(test_t,JOIN(uid,rv)), \
                  JOIN(test_t,JOIN(uid,rv))>) ); \
      typedef common_type_t<const volatile type1 &&> JOIN(test_t,JOIN(uid,rcv)); \
      CHECK( (std::is_same_v<JOIN(test_t,JOIN(uid,rcv)), \
                  JOIN(test_t,JOIN(uid,rcv))>) )

   struct AA { };
   struct BB : AA { };

   void typedefs_test01() // NOLINT(readability-function-size)
   {
      // Positive tests.
      COMMON_TYPE_TEST_1(int, 1);
      COMMON_TYPE_TEST_1(double, 2);
      COMMON_TYPE_TEST_1(AA, 3);
      COMMON_TYPE_TEST_1(BB, 4);
   }

   #define COMMON_TYPE_TEST_2_IMPL(type1, type2, type3, uid) \
      typedef common_type_t<type1, type2>     JOIN(JOIN(test, uid),_t1); \
      typedef common_type_t<type2, type1>     JOIN(JOIN(test, uid),_t2); \
      CHECK( (std::is_same_v<JOIN(JOIN(test, uid),_t1), type3>) ); \
      CHECK( (std::is_same_v<JOIN(JOIN(test, uid),_t2), type3>) )

   #define NO_CV

   #define COMMON_TYPE_TEST_2(cv_qual, type1, type2, type3, uid) \
      COMMON_TYPE_TEST_2_IMPL(cv_qual type1, type2, type3, uid); \
      COMMON_TYPE_TEST_2_IMPL(cv_qual type1 &, type2, type3, JOIN(uid,l)); \
      COMMON_TYPE_TEST_2_IMPL(cv_qual type1 &&, type2, type3, JOIN(uid,r))

   #define COMMON_TYPE_TEST_ALL_2(type1, type2, type3, uid) \
      COMMON_TYPE_TEST_2(NO_CV, type1, type2, type3, uid); \
      COMMON_TYPE_TEST_2(const, type1, type2, type3, uid); \
      COMMON_TYPE_TEST_2(volatile, type1, type2, type3, uid); \
      COMMON_TYPE_TEST_2(const volatile, type1, type2, type3, uid)

   void typedefs_test02() // NOLINT(readability-function-size)
   {
      COMMON_TYPE_TEST_ALL_2(int, int, int, 1);
      COMMON_TYPE_TEST_ALL_2(int, double, double, 2);
      COMMON_TYPE_TEST_2(NO_CV, AA, AA, AA, 3);
      COMMON_TYPE_TEST_2(const, AA, AA, AA, 4);
      COMMON_TYPE_TEST_2(NO_CV, BB, AA, AA, 5);
   }

   void typedefs_1()
   {
      typedefs_test01();
      typedefs_test02();
   }

   // 2009-11-12  Paolo Carlini  <paolo.carlini@oracle.com>
   // DR 1255.
   static_assert(std::is_same_v<common_type_t<void>, void>);
   static_assert(std::is_same_v<common_type_t<const void>, void>);
   static_assert(std::is_same_v<common_type_t<volatile void>, void>);
   static_assert(std::is_same_v<common_type_t<const volatile void>, void>);

   static_assert(std::is_same_v<common_type_t<void, void>, void>);
   static_assert(std::is_same_v<common_type_t<void, const void>, void>);
   static_assert(std::is_same_v<common_type_t<void, volatile void>, void>);
   static_assert(std::is_same_v<common_type_t<void, const volatile void>, void>);
   static_assert(std::is_same_v<common_type_t<const void, void>, void>);
   static_assert(std::is_same_v<common_type_t<const void, const void>, void>);
   static_assert(std::is_same_v<common_type_t<const void, volatile void>, void>);
   static_assert(std::is_same_v<common_type_t<const void, const volatile void>, void>);
   static_assert(std::is_same_v<common_type_t<volatile void, void>, void>);
   static_assert(std::is_same_v<common_type_t<volatile void, volatile void>, void>);
   static_assert(std::is_same_v<common_type_t<volatile void, const void>, void>);
   static_assert(std::is_same_v<common_type_t<volatile void, const volatile void>, void>);
   static_assert(std::is_same_v<common_type_t<const volatile void, void>, void>);
   static_assert(std::is_same_v<common_type_t<const volatile void, const void>, void>);
   static_assert(std::is_same_v<common_type_t<const volatile void, volatile void>, void>);
   static_assert(std::is_same_v<common_type_t<const volatile void, const volatile void>, void>);
}

// https://github.com/ericniebler/stl2/issues/338
struct MyIntRef {
  MyIntRef(int &); // NOLINT(google-explicit-constructor)
};
using T = common_reference_t<int&, MyIntRef>;
static_assert(std::is_same_v<common_reference_t<int&, MyIntRef>, MyIntRef>);
static_assert(std::is_same_v<common_reference_t<int, int, int>, int>);

TEST_CASE("common_reference") {
   ::libstdcpp_tests::typedefs_1();
}
