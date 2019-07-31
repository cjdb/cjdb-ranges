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
#include "cjdb/concepts/core/convertible_to.hpp"

#include "cjdb/type_traits/expose_type.hpp"

template<typename From, typename To>
constexpr void models_ConvertibleTo()
{
   static_assert(cjdb::convertible_to<From, To>);
   static_assert(cjdb::convertible_to<From, To const>);
   static_assert(cjdb::convertible_to<From, To const&>);

   static_assert(cjdb::convertible_to<From const, To>);
   static_assert(cjdb::convertible_to<From const, To const>);
   static_assert(cjdb::convertible_to<From const, To const&>);

   static_assert(cjdb::convertible_to<From&, To>);
   static_assert(cjdb::convertible_to<From&, To const>);

   if constexpr (std::is_base_of_v<To, From>) { // NOLINT(readability-braces-around-statements)
      static_assert(cjdb::convertible_to<From&, To&>);
   }

   static_assert(cjdb::convertible_to<From&, To const&>);

   static_assert(cjdb::convertible_to<From const&, To>);
   static_assert(cjdb::convertible_to<From const&, To const>);
   static_assert(cjdb::convertible_to<From const&, To const&>);
}

int main()
{
   {
      static_assert(cjdb::convertible_to<void, void>);
      models_ConvertibleTo<int, int>();
   }
   {
      models_ConvertibleTo<int, float>();
      models_ConvertibleTo<float, int>();
   }
   {
      struct implicitly_constructible_from_int {
         implicitly_constructible_from_int(int); // NOLINT(google-explicit-constructor)
      };
      models_ConvertibleTo<int, implicitly_constructible_from_int>();

      struct implicitly_convertible_to_int {
         operator int();       // NOLINT(google-explicit-constructor)
         operator int() const; // NOLINT(google-explicit-constructor)
      };
      models_ConvertibleTo<implicitly_convertible_to_int, int>();

      struct implicitly_convertible_to_and_from_int {
         implicitly_convertible_to_and_from_int(int); // NOLINT(google-explicit-constructor)
         operator int();                              // NOLINT(google-explicit-constructor)
         operator int() const;                        // NOLINT(google-explicit-constructor)
      };
      models_ConvertibleTo<int, implicitly_convertible_to_and_from_int>();
      models_ConvertibleTo<implicitly_convertible_to_and_from_int, int>();
   }
   {
      struct base {};
      models_ConvertibleTo<base, base>();

      struct public_derived : public base {};
      models_ConvertibleTo<public_derived, base>();
      static_assert(not cjdb::convertible_to<base, public_derived>);

      struct protected_derived : protected base {};
      static_assert(not cjdb::convertible_to<protected_derived, base>);
      static_assert(not cjdb::convertible_to<protected_derived, public_derived>);
      static_assert(not cjdb::convertible_to<base, protected_derived>);

      struct private_derived : private base {};
      static_assert(not cjdb::convertible_to<private_derived, base>);
      static_assert(not cjdb::convertible_to<private_derived, protected_derived>);
      static_assert(not cjdb::convertible_to<private_derived, public_derived>);
      static_assert(not cjdb::convertible_to<base, private_derived>);
   }
}
