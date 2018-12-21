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
#include "cjdb/concepts/core/assignable.hpp"

#include <memory>
#include <mutex>
#include <vector>

template<typename T1, typename T2 = T1>
void models_Assignable()
{
   static_assert(not cjdb::Assignable<T1, T2>);
   static_assert(not cjdb::Assignable<T1, T2 const>);
   static_assert(not cjdb::Assignable<T1, T2&>);
   static_assert(not cjdb::Assignable<T1, T2 const&>);
   static_assert(not cjdb::Assignable<T1, T2&&>);
   static_assert(not cjdb::Assignable<T1, T2 const&&>);

   static_assert(cjdb::Assignable<T1&, T2>);
   static_assert(cjdb::Assignable<T1&, T2 const>);
   static_assert(cjdb::Assignable<T1&, T2&>);
   static_assert(cjdb::Assignable<T1&, T2 const&>);
   static_assert(cjdb::Assignable<T1&, T2&&>);
   static_assert(cjdb::Assignable<T1&, T2 const&&>);

   static_assert(not cjdb::Assignable<T1 const&, T2>);
   static_assert(not cjdb::Assignable<T1 const&, T2 const>);
   static_assert(not cjdb::Assignable<T1 const&, T2&>);
   static_assert(not cjdb::Assignable<T1 const&, T2 const&>);
   static_assert(not cjdb::Assignable<T1 const&, T2&&>);
   static_assert(not cjdb::Assignable<T1 const&, T2 const&&>);

   static_assert(not cjdb::Assignable<T1&&, T2>);
   static_assert(not cjdb::Assignable<T1&&, T2 const>);
   static_assert(not cjdb::Assignable<T1&&, T2&>);
   static_assert(not cjdb::Assignable<T1&&, T2 const&>);
   static_assert(not cjdb::Assignable<T1&&, T2&&>);
   static_assert(not cjdb::Assignable<T1&&, T2 const&&>);

   static_assert(not cjdb::Assignable<T1 const&&, T2>);
   static_assert(not cjdb::Assignable<T1 const&&, T2 const>);
   static_assert(not cjdb::Assignable<T1 const&&, T2&>);
   static_assert(not cjdb::Assignable<T1 const&&, T2 const&>);
   static_assert(not cjdb::Assignable<T1 const&&, T2&&>);
   static_assert(not cjdb::Assignable<T1 const&&, T2 const&&>);
}

struct real_assignable {
   real_assignable(int); // NOLINT(google-explicit-constructor)
   real_assignable& operator=(int);
};

template<template<class> class TQual, template<class> class QQual>
struct cjdb::basic_common_reference<real_assignable, int, TQual, QQual> {
   using type = real_assignable;
};

template<template<class> class TQual, template<class> class QQual>
struct cjdb::basic_common_reference<int, real_assignable, TQual, QQual> {
   using type = real_assignable;
};

int main()
{
   models_Assignable<int>();
   models_Assignable<double>();
   models_Assignable<std::vector<int>>();
   models_Assignable<std::vector<double>>();

   struct default_assignable {};
   models_Assignable<default_assignable>();

   models_Assignable<int, double>();
   models_Assignable<double, int>();

   struct fake_assignable {
      fake_assignable& operator=(int);
   };
   models_Assignable<fake_assignable>();
   static_assert(not cjdb::Assignable<fake_assignable&, int>);

   models_Assignable<real_assignable>();
   models_Assignable<real_assignable, int>();

   static_assert(not cjdb::Assignable<int, std::vector<int>>);
   static_assert(not cjdb::Assignable<std::vector<int>, int>);
   static_assert(not cjdb::Assignable<std::vector<int>, std::vector<double>>);
}
