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
#include "cjdb/detail/concepts/core/same.hpp"

#include "cjdb/detail/type_traits/expose_type.hpp"

struct S1 {};
struct S2 { int i; };
struct S3 { int& r; };
struct S4 { int&& r; };
struct S5 { int* p; };

class C1 {};
class C2 { [[maybe_unused]] int i; };

class C3 {
public:
   int i;
};

template <typename T1, typename T2 = T1>
class C4 {
   int t1;
   int t2;
};

template <typename T1, typename T2 = T1>
class C5 {
   [[maybe_unused]] T1 t1;
public:
   T2 t2;
};

template <typename T1, typename T2 = T1>
class C6 {
public:
   [[maybe_unused]] T1 t1;
   [[maybe_unused]] T2 t2;
};

template <typename T>
struct identity {
   using type = T;
};

using cjdb::_t;
using cjdb::Same;

template <template <typename> typename Modifier = identity>
void check_Same()
{
   static_assert(Same<_t<Modifier<int>>,        _t<Modifier<int>>>);
   static_assert(Same<_t<Modifier<S1>>,         _t<Modifier<S1>>>);
   static_assert(Same<_t<Modifier<S2>>,         _t<Modifier<S2>>>);
   static_assert(Same<_t<Modifier<S3>>,         _t<Modifier<S3>>>);
   static_assert(Same<_t<Modifier<S4>>,         _t<Modifier<S4>>>);
   static_assert(Same<_t<Modifier<S5>>,         _t<Modifier<S5>>>);
   static_assert(Same<_t<Modifier<C1>>,         _t<Modifier<C1>>>);
   static_assert(Same<_t<Modifier<C2>>,         _t<Modifier<C2>>>);
   static_assert(Same<_t<Modifier<C3>>,         _t<Modifier<C3>>>);
   static_assert(Same<_t<Modifier<C4<int>>>,    _t<Modifier<C4<int>>>>);
   static_assert(Same<_t<Modifier<C4<int&>>>,   _t<Modifier<C4<int&>>>>);
   static_assert(Same<_t<Modifier<C4<int&&>>>,  _t<Modifier<C4<int&&>>>>);
   static_assert(Same<_t<Modifier<C5<int>>>,    _t<Modifier<C5<int>>>>);
   static_assert(Same<_t<Modifier<C5<int&>>>,   _t<Modifier<C5<int&>>>>);
   static_assert(Same<_t<Modifier<C5<int&&>>>,  _t<Modifier<C5<int&&>>>>);
   static_assert(Same<_t<Modifier<C6<int>>>,    _t<Modifier<C6<int>>>>);
   static_assert(Same<_t<Modifier<C6<int&>>>,   _t<Modifier<C6<int&>>>>);
   static_assert(Same<_t<Modifier<C6<int&&>>>,  _t<Modifier<C6<int&&>>>>);
}

template <template <typename> typename Modifier1,
   template <typename> typename Modifier2 = identity>
void check_not_Same()
{
   static_assert(not Same<_t<Modifier1<int>>,       _t<Modifier2<int>>>);
   static_assert(not Same<_t<Modifier1<S1>>,        _t<Modifier2<S1>>>);
   static_assert(not Same<_t<Modifier1<S2>>,        _t<Modifier2<S2>>>);
   static_assert(not Same<_t<Modifier1<S3>>,        _t<Modifier2<S3>>>);
   static_assert(not Same<_t<Modifier1<S4>>,        _t<Modifier2<S4>>>);
   static_assert(not Same<_t<Modifier1<S5>>,        _t<Modifier2<S5>>>);
   static_assert(not Same<_t<Modifier1<C1>>,        _t<Modifier2<C1>>>);
   static_assert(not Same<_t<Modifier1<C2>>,        _t<Modifier2<C2>>>);
   static_assert(not Same<_t<Modifier1<C3>>,        _t<Modifier2<C3>>>);
   static_assert(not Same<_t<Modifier1<C4<int>>>,   _t<Modifier2<C4<int>>>>);
   static_assert(not Same<_t<Modifier1<C4<int&>>>,  _t<Modifier2<C4<int&>>>>);
   static_assert(not Same<_t<Modifier1<C4<int&&>>>, _t<Modifier2<C4<int&&>>>>);
   static_assert(not Same<_t<Modifier1<C5<int>>>,   _t<Modifier2<C5<int>>>>);
   static_assert(not Same<_t<Modifier1<C5<int&>>>,  _t<Modifier2<C5<int&>>>>);
   static_assert(not Same<_t<Modifier1<C5<int&&>>>, _t<Modifier2<C5<int&&>>>>);
   static_assert(not Same<_t<Modifier1<C6<int>>>,   _t<Modifier2<C6<int>>>>);
   static_assert(not Same<_t<Modifier1<C6<int&>>>,  _t<Modifier2<C6<int&>>>>);
   static_assert(not Same<_t<Modifier1<C6<int&&>>>, _t<Modifier2<C6<int&&>>>>);
}

template<class T, class U>
requires Same<T, U>
void f();

template<class T, class U>
requires Same<U, T> && true
int f();

static_assert(Same<int, decltype(f<int, int>())>);

int main()
{
   { // Checks Same<T, T> is true
      check_Same();
   }

   { // Checks Same<T&, T&> is true
      check_Same<std::add_lvalue_reference>();
   }

   { // Checks Same<T&&, T&&> is true
      check_Same<std::add_rvalue_reference>();
   }

   { // Checks Same<T, T&> is false
      check_not_Same<identity, std::add_lvalue_reference>();
   }

   { // Checks Same<T, T&&> is false
      check_not_Same<identity, std::add_rvalue_reference>();
   }

   { // Checks Same<T&, T> is false
      check_not_Same<std::add_lvalue_reference, identity>();
   }

   { // Checks Same<T&&, T> is false
      check_not_Same<std::add_rvalue_reference, identity>();
   }

   { // Checks Same<T&, T&&> is false
      check_not_Same<std::add_lvalue_reference, std::add_rvalue_reference>();
   }

   { // Checks Same<T&&, T&> is false
      check_not_Same<std::add_rvalue_reference, std::add_lvalue_reference>();
   }

   { // Checks Same<T1, T2> is false
      static_assert(not Same<S1, C1>);
      static_assert(not Same<C4<int>, C5<int>>);
      static_assert(not Same<C4<int>, C5<int>>);
      static_assert(not Same<C5<int, double>, C5<double, int>>);
   }
}
