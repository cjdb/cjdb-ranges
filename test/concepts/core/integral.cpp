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
   static_assert(cjdb::Integral<I>);
   static_assert(cjdb::Integral<I const>);
   static_assert(cjdb::Integral<I volatile>);
   static_assert(cjdb::Integral<I const volatile>);

   static_assert(not cjdb::Integral<I*>);
   static_assert(not cjdb::Integral<I const*>);
   static_assert(not cjdb::Integral<I volatile*>);
   static_assert(not cjdb::Integral<I const volatile*>);

   static_assert(not cjdb::Integral<I&>);
   static_assert(not cjdb::Integral<I const&>);
   static_assert(not cjdb::Integral<I volatile&>);
   static_assert(not cjdb::Integral<I const volatile&>);

   static_assert(not cjdb::Integral<std::remove_reference_t<I>&&>);
   static_assert(not cjdb::Integral<std::remove_reference_t<I> const&&>);
   static_assert(not cjdb::Integral<std::remove_reference_t<I> volatile&&>);
   static_assert(not cjdb::Integral<std::remove_reference_t<I> const volatile&&>);
}

template<cjdb::SignedIntegral I>
constexpr void models_SignedIntegral() noexcept
{
   models_Integral<I>();

   static_assert(cjdb::SignedIntegral<I>);
   static_assert(cjdb::SignedIntegral<I const>);
   static_assert(cjdb::SignedIntegral<I volatile>);
   static_assert(cjdb::SignedIntegral<I const volatile>);

   static_assert(not cjdb::SignedIntegral<I*>);
   static_assert(not cjdb::SignedIntegral<I const*>);
   static_assert(not cjdb::SignedIntegral<I volatile*>);
   static_assert(not cjdb::SignedIntegral<I const volatile*>);

   static_assert(not cjdb::SignedIntegral<I&>);
   static_assert(not cjdb::SignedIntegral<I const&>);
   static_assert(not cjdb::SignedIntegral<I volatile&>);
   static_assert(not cjdb::SignedIntegral<I const volatile&>);

   static_assert(not cjdb::SignedIntegral<std::remove_reference_t<I>&&>);
   static_assert(not cjdb::SignedIntegral<std::remove_reference_t<I> const&&>);
   static_assert(not cjdb::SignedIntegral<std::remove_reference_t<I> volatile&&>);
   static_assert(not cjdb::SignedIntegral<std::remove_reference_t<I> const volatile&&>);
}

template<cjdb::UnsignedIntegral I>
constexpr void models_UnsignedIntegral() noexcept
{
   models_Integral<I>();

   static_assert(cjdb::UnsignedIntegral<I>);
   static_assert(cjdb::UnsignedIntegral<I const>);
   static_assert(cjdb::UnsignedIntegral<I volatile>);
   static_assert(cjdb::UnsignedIntegral<I const volatile>);

   static_assert(not cjdb::UnsignedIntegral<I*>);
   static_assert(not cjdb::UnsignedIntegral<I const*>);
   static_assert(not cjdb::UnsignedIntegral<I volatile*>);
   static_assert(not cjdb::UnsignedIntegral<I const volatile*>);

   static_assert(not cjdb::UnsignedIntegral<I&>);
   static_assert(not cjdb::UnsignedIntegral<I const&>);
   static_assert(not cjdb::UnsignedIntegral<I volatile&>);
   static_assert(not cjdb::UnsignedIntegral<I const volatile&>);

   static_assert(not cjdb::UnsignedIntegral<std::remove_reference_t<I>&&>);
   static_assert(not cjdb::UnsignedIntegral<std::remove_reference_t<I> const&&>);
   static_assert(not cjdb::UnsignedIntegral<std::remove_reference_t<I> volatile&&>);
   static_assert(not cjdb::UnsignedIntegral<std::remove_reference_t<I> const volatile&&>);
}

template<class T>
constexpr void models_none() noexcept
{
   static_assert(not cjdb::Integral<T>);
   static_assert(not cjdb::SignedIntegral<T>);
   static_assert(not cjdb::UnsignedIntegral<T>);
}

int main()
{
   models_Integral<bool>();
   models_Integral<char>();
   models_Integral<char16_t>();
   models_Integral<char32_t>();
   models_Integral<wchar_t>();

   models_SignedIntegral<signed char>();
   static_assert(not cjdb::UnsignedIntegral<signed char>);

   models_UnsignedIntegral<unsigned char>();
   static_assert(not cjdb::SignedIntegral<unsigned char>);

   models_SignedIntegral<short>();
   static_assert(not cjdb::UnsignedIntegral<short>);

   models_UnsignedIntegral<unsigned short>();
   static_assert(not cjdb::SignedIntegral<unsigned short>);

   models_SignedIntegral<int>();
   static_assert(not cjdb::UnsignedIntegral<int>);

   models_UnsignedIntegral<unsigned int>();
   static_assert(not cjdb::SignedIntegral<unsigned int>);

   models_SignedIntegral<long>();
   static_assert(not cjdb::UnsignedIntegral<long>);

   models_UnsignedIntegral<unsigned long>();
   static_assert(not cjdb::SignedIntegral<unsigned long>);

   models_SignedIntegral<long long>();
   static_assert(not cjdb::UnsignedIntegral<long long>);

   models_UnsignedIntegral<unsigned long long>();
   static_assert(not cjdb::SignedIntegral<unsigned long long>);

   models_none<float>();
   models_none<double>();
   models_none<long double>();

   struct S {};
   models_none<S>();
}
