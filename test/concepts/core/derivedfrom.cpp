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
#include "cjdb/concepts/core/derivedfrom.hpp"

struct Base1 {};
struct Derived1 : Base1 {};
struct Derived2 : Base1 {};

struct Base2 : private Base1 {};
struct Derived3 : Base2 {};

struct Base3 : protected Base2 {};
struct Derived4 : Base3 {};
struct Derived5 : Derived4 {};

int main()
{
   { // Base1 is the subject.
      static_assert(cjdb::DerivedFrom<Base1, Base1>);
      static_assert(not cjdb::DerivedFrom<Base1, Base2>);
      static_assert(not cjdb::DerivedFrom<Base1, Base3>);

      static_assert(not cjdb::DerivedFrom<Base1, Derived1>);
      static_assert(not cjdb::DerivedFrom<Base1, Derived2>);
      static_assert(not cjdb::DerivedFrom<Base1, Derived3>);
      static_assert(not cjdb::DerivedFrom<Base1, Derived4>);
   }

   { // Derived1 is the subject.
      static_assert(cjdb::DerivedFrom<Derived1, Base1>);
      static_assert(not cjdb::DerivedFrom<Derived1, Base2>);
      static_assert(not cjdb::DerivedFrom<Derived1, Base3>);

      static_assert(cjdb::DerivedFrom<Derived1, Derived1>);
      static_assert(not cjdb::DerivedFrom<Derived1, Derived2>);
      static_assert(not cjdb::DerivedFrom<Derived1, Derived3>);
      static_assert(not cjdb::DerivedFrom<Derived1, Derived4>);
   }

   { // Derived2 is the subject.
      static_assert(cjdb::DerivedFrom<Derived2, Base1>);
      static_assert(not cjdb::DerivedFrom<Derived2, Base2>);
      static_assert(not cjdb::DerivedFrom<Derived2, Base3>);

      static_assert(not cjdb::DerivedFrom<Derived2, Derived1>);
      static_assert(    cjdb::DerivedFrom<Derived2, Derived2>);
      static_assert(not cjdb::DerivedFrom<Derived2, Derived3>);
      static_assert(not cjdb::DerivedFrom<Derived2, Derived4>);
   }

   { // Base2 is the subject.
      static_assert(not cjdb::DerivedFrom<Base2, Base1>);
      static_assert(    cjdb::DerivedFrom<Base2, Base2>);
      static_assert(not cjdb::DerivedFrom<Base2, Base3>);

      static_assert(not cjdb::DerivedFrom<Base2, Derived1>);
      static_assert(not cjdb::DerivedFrom<Base2, Derived2>);
      static_assert(not cjdb::DerivedFrom<Base2, Derived3>);
      static_assert(not cjdb::DerivedFrom<Base2, Derived4>);
   }

   { // Derived3 is the subject.
      static_assert(not cjdb::DerivedFrom<Derived3, Base1>);
      static_assert(    cjdb::DerivedFrom<Derived3, Base2>);
      static_assert(not cjdb::DerivedFrom<Derived3, Base3>);

      static_assert(not cjdb::DerivedFrom<Derived3, Derived1>);
      static_assert(not cjdb::DerivedFrom<Derived3, Derived2>);
      static_assert(    cjdb::DerivedFrom<Derived3, Derived3>);
      static_assert(not cjdb::DerivedFrom<Derived3, Derived4>);
   }

   { // Base3 is the subject.
      static_assert(not cjdb::DerivedFrom<Base3, Base1>);
      static_assert(not cjdb::DerivedFrom<Base3, Base2>);
      static_assert(    cjdb::DerivedFrom<Base3, Base3>);

      static_assert(not cjdb::DerivedFrom<Base3, Derived1>);
      static_assert(not cjdb::DerivedFrom<Base3, Derived2>);
      static_assert(not cjdb::DerivedFrom<Base3, Derived3>);
      static_assert(not cjdb::DerivedFrom<Base3, Derived4>);
   }

   { // Derived4 is the subject.
      static_assert(not cjdb::DerivedFrom<Derived4, Base1>);
      static_assert(not cjdb::DerivedFrom<Derived4, Base2>);
      static_assert(    cjdb::DerivedFrom<Derived4, Base3>);

      static_assert(not cjdb::DerivedFrom<Derived4, Derived1>);
      static_assert(not cjdb::DerivedFrom<Derived4, Derived2>);
      static_assert(not cjdb::DerivedFrom<Derived4, Derived3>);
      static_assert(    cjdb::DerivedFrom<Derived4, Derived4>);
   }

   { // Derived5 is the subject.
      static_assert(not cjdb::DerivedFrom<Derived5, Base1>);
      static_assert(not cjdb::DerivedFrom<Derived5, Base2>);
      static_assert(    cjdb::DerivedFrom<Derived5, Base3>);

      static_assert(not cjdb::DerivedFrom<Derived5, Derived1>);
      static_assert(not cjdb::DerivedFrom<Derived5, Derived2>);
      static_assert(not cjdb::DerivedFrom<Derived5, Derived3>);
      static_assert(    cjdb::DerivedFrom<Derived5, Derived4>);
      static_assert(    cjdb::DerivedFrom<Derived5, Derived5>);
   }
}
