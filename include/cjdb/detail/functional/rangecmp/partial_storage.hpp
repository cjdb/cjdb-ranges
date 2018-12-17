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
#ifndef CJDB_FUNCTIONAL_RANGECMP_PARTIAL_STORAGE_HPP
#define CJDB_FUNCTIONAL_RANGECMP_PARTIAL_STORAGE_HPP

namespace cjdb::detail_partial_storage {
   /// \brief Helper type to determine if a `partial_foo` stores a pointer-to-lvalue or an lvalue.
   ///
   /// If a user constructs a `partial_foo` with an lvalue, then the type of `partial_storage` is
   /// pointer-to-`const T`. This makes `partial_foo<T&>` cheap to copy.
   ///
   /// If a user constructs a `partial_foo` with an rvalue, then the type of `partial_storage` is
   /// `T`. This makes `partial_foo<T&&>` potentially expensive to copy, but ensures lifetime
   /// safety.
   ///
   template<class T>
   struct partial_storage {
      using type = remove_reference_t<T> const*;
   };

   template<class T>
   requires is_rvalue_reference_v<T>
   struct partial_storage<T> {
      using type = remove_reference_t<T>;
   };

   template<class T>
   using partial_storage_t = _t<partial_storage<T>>;

   template<class T>
   class partial_function_storage {
   public:
      /// \brief Constructs `partial_function_storage`.
      ///
      /// \note This constructor participates in overload resolution if, and only if, T is an lvalue
      ///       reference.
      ///
      constexpr explicit partial_function_storage(T const& value) noexcept
      requires is_lvalue_reference_v<T>
         : value_{std::addressof(value)}
      {}

      /// \brief Constructs `partial_function_storage`.
      /// \note This constructor participates in overload resolution if, and only if, T is an rvalue
      ///       reference.
      ///
      constexpr explicit partial_function_storage(remove_reference_t<T> value) noexcept
      requires is_rvalue_reference_v<T>
         : value_{std::move(value)}
      {}

      /// \brief Returns the value stored.
      ///
      constexpr auto const& value() const noexcept
      {
         if constexpr (is_lvalue_reference_v<T>) {
            return *value_;
         }
         else {
            return value_;
         }
      }
   private:
      partial_storage_t<T> value_;
   };
} // namespace cjdb::detail_partial_storage

#endif // CJDB_FUNCTIONAL_RANGECMP_PARTIAL_STORAGE_HPP
