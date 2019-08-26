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
#include "cjdb/concepts/core/integral.hpp"

#include "cjdb/type_traits/expose_type.hpp"

template<class I>
constexpr void models_Integral() noexcept
{
   static_assert(cjdb::integral<I>);
   static_assert(cjdb::integral<I const>);
   static_assert(cjdb::integral<I volatile>);
   static_assert(cjdb::integral<I const volatile>);

   static_assert(not cjdb::integral<I*>);
   static_assert(not cjdb::integral<I const*>);
   static_assert(not cjdb::integral<I volatile*>);
   static_assert(not cjdb::integral<I const volatile*>);

   static_assert(not cjdb::integral<I&>);
   static_assert(not cjdb::integral<I const&>);
   static_assert(not cjdb::integral<I volatile&>);
   static_assert(not cjdb::integral<I const volatile&>);

   static_assert(not cjdb::integral<std::remove_reference_t<I>&&>);
   static_assert(not cjdb::integral<std::remove_reference_t<I> const&&>);
   static_assert(not cjdb::integral<std::remove_reference_t<I> volatile&&>);
   static_assert(not cjdb::integral<std::remove_reference_t<I> const volatile&&>);
}

template<cjdb::signed_integral I>
constexpr void models_SignedIntegral() noexcept
{
   models_Integral<I>();

   static_assert(cjdb::signed_integral<I>);
   static_assert(cjdb::signed_integral<I const>);
   static_assert(cjdb::signed_integral<I volatile>);
   static_assert(cjdb::signed_integral<I const volatile>);

   static_assert(not cjdb::signed_integral<I*>);
   static_assert(not cjdb::signed_integral<I const*>);
   static_assert(not cjdb::signed_integral<I volatile*>);
   static_assert(not cjdb::signed_integral<I const volatile*>);

   static_assert(not cjdb::signed_integral<I&>);
   static_assert(not cjdb::signed_integral<I const&>);
   static_assert(not cjdb::signed_integral<I volatile&>);
   static_assert(not cjdb::signed_integral<I const volatile&>);

   static_assert(not cjdb::signed_integral<std::remove_reference_t<I>&&>);
   static_assert(not cjdb::signed_integral<std::remove_reference_t<I> const&&>);
   static_assert(not cjdb::signed_integral<std::remove_reference_t<I> volatile&&>);
   static_assert(not cjdb::signed_integral<std::remove_reference_t<I> const volatile&&>);
}

template<cjdb::unsigned_integral I>
constexpr void models_UnsignedIntegral() noexcept
{
   models_Integral<I>();

   static_assert(cjdb::unsigned_integral<I>);
   static_assert(cjdb::unsigned_integral<I const>);
   static_assert(cjdb::unsigned_integral<I volatile>);
   static_assert(cjdb::unsigned_integral<I const volatile>);

   static_assert(not cjdb::unsigned_integral<I*>);
   static_assert(not cjdb::unsigned_integral<I const*>);
   static_assert(not cjdb::unsigned_integral<I volatile*>);
   static_assert(not cjdb::unsigned_integral<I const volatile*>);

   static_assert(not cjdb::unsigned_integral<I&>);
   static_assert(not cjdb::unsigned_integral<I const&>);
   static_assert(not cjdb::unsigned_integral<I volatile&>);
   static_assert(not cjdb::unsigned_integral<I const volatile&>);

   static_assert(not cjdb::unsigned_integral<std::remove_reference_t<I>&&>);
   static_assert(not cjdb::unsigned_integral<std::remove_reference_t<I> const&&>);
   static_assert(not cjdb::unsigned_integral<std::remove_reference_t<I> volatile&&>);
   static_assert(not cjdb::unsigned_integral<std::remove_reference_t<I> const volatile&&>);
}

template<class T>
constexpr void models_none() noexcept
{
   static_assert(not cjdb::integral<T>);
   static_assert(not cjdb::signed_integral<T>);
   static_assert(not cjdb::unsigned_integral<T>);
}

int main()
{
   models_Integral<bool>();
   models_Integral<char>();
   models_Integral<char16_t>();
   models_Integral<char32_t>();
   models_Integral<wchar_t>();

   models_SignedIntegral<signed char>();
   static_assert(not cjdb::unsigned_integral<signed char>);

   models_UnsignedIntegral<unsigned char>();
   static_assert(not cjdb::signed_integral<unsigned char>);

   models_SignedIntegral<short>();
   static_assert(not cjdb::unsigned_integral<short>);

   models_UnsignedIntegral<unsigned short>();
   static_assert(not cjdb::signed_integral<unsigned short>);

   models_SignedIntegral<int>();
   static_assert(not cjdb::unsigned_integral<int>);

   models_UnsignedIntegral<unsigned int>();
   static_assert(not cjdb::signed_integral<unsigned int>);

   models_SignedIntegral<long>();
   static_assert(not cjdb::unsigned_integral<long>);

   models_UnsignedIntegral<unsigned long>();
   static_assert(not cjdb::signed_integral<unsigned long>);

   models_SignedIntegral<long long>();
   static_assert(not cjdb::unsigned_integral<long long>);

   models_UnsignedIntegral<unsigned long long>();
   static_assert(not cjdb::signed_integral<unsigned long long>);

   models_none<float>();
   models_none<double>();
   models_none<long double>();

   struct S {};
   models_none<S>();
}
