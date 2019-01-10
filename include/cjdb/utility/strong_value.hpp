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
#ifndef CJDB_UTILITY_STRONG_VALUE_HPP
#define CJDB_UTILITY_STRONG_VALUE_HPP

#include "cjdb/concepts/comparison/equalitycomparable.hpp"
#include "cjdb/concepts/comparison/stricttotallyordered.hpp"
#include "cjdb/concepts/core/constructible.hpp"
#include "cjdb/concepts/core/convertibleto.hpp"
#include "cjdb/concepts/core/defaultconstructible.hpp"
#include "cjdb/concepts/numeric/integer.hpp"
#include "cjdb/concepts/numeric/number.hpp"
#include "cjdb/concepts/object/copyable.hpp"
#include "cjdb/concepts/object/movable.hpp"
#include "cjdb/type_traits/type_traits.hpp"
#include <utility>

namespace cjdb {
   template<DefaultConstructible Value, typename>
   class strong_value {
   public:
      constexpr strong_value() = default;

      constexpr explicit strong_value(Value value) noexcept(std::is_nothrow_move_constructible_v<Value>)
      requires Movable<Value>
         : value_(std::move(value))
      {}

      constexpr explicit strong_value(Value const& value)
      noexcept(std::is_nothrow_copy_constructible_v<Value>)
      requires Copyable<Value>
         : value_(value)
      {}

      template<typename... Args>
      requires Constructible<Value, Args...>
      constexpr explicit strong_value(Args&&... args)
      noexcept(std::is_nothrow_constructible_v<Value, Args...>)
         : value_(std::forward<Args>(args)...)
      {}

      constexpr strong_value& operator=(Value&& value) noexcept(std::is_nothrow_move_assignable_v<Value>)
      requires Movable<Value>
      { return assign_impl(*this, std::move(value)); }

      constexpr strong_value& operator=(Value const& value)
      noexcept(std::is_nothrow_copy_assignable_v<Value>)
      requires Copyable<Value>
      { return assign_impl(*this, value); }

      template<ConvertibleTo<Value> T>
      constexpr strong_value& operator=(T&& value) noexcept(std::is_nothrow_assignable_v<Value&, T>)
      { return assign_impl(*this, static_cast<Value>(std::forward<T>(value))); }

      constexpr strong_value& operator+=(strong_value const& other)
      requires Number<Value>
      {
         value_ += other.value_;
         return *this;
      }

      constexpr strong_value& operator-=(strong_value const& other)
      requires Number<Value>
      { return value_ += -other; }

      constexpr strong_value& operator*=(strong_value const& other)
      requires Number<Value>
      {
         value_ *= other.value_;
         return *this;
      }

      constexpr strong_value& operator/=(strong_value const& other)
      requires Number<Value>
      {
         value_ /= other.value_;
         return *this;
      }

      constexpr strong_value& operator%=(strong_value const& other)
      requires Integer<Value>
      {
         value_ %= other.value_;
         return *this;
      }

      constexpr strong_value operator+() const noexcept(std::is_nothrow_copy_constructible_v<Value>)
      requires Number<Value>
      { return *this; }

      constexpr strong_value operator-() const noexcept(std::is_nothrow_copy_constructible_v<Value>)
      requires Number<Value>
      { return strong_value{-value_}; }

      template<class ConvertTo>
      requires ConvertibleTo<Value, remove_reference_t<ConvertTo>>
      constexpr explicit operator ConvertTo() noexcept
      { return value_; }

      template<class ConvertTo>
      requires ConvertibleTo<Value, remove_cvref_t<ConvertTo>>
      constexpr explicit operator ConvertTo() const noexcept
      { return value_; }

      constexpr friend bool operator==(strong_value const& x, strong_value const& y) noexcept
      requires EqualityComparable<Value>
      { return x.value_ == y.value_; }

      constexpr friend bool operator!=(strong_value const& x, strong_value const& y) noexcept
      requires EqualityComparable<Value>
      { return not (x == y); }

      constexpr friend bool operator<(strong_value const& x, strong_value const& y) noexcept
      requires StrictTotallyOrdered<Value>
      { return x < y; }

      constexpr friend bool operator>(strong_value const& x, strong_value const& y) noexcept
      requires StrictTotallyOrdered<Value>
      { return y < x; }

      constexpr friend bool operator<=(strong_value const& x, strong_value const& y) noexcept
      requires StrictTotallyOrdered<Value>
      { return not (y < x); }

      constexpr friend bool operator>=(strong_value const& x, strong_value const& y) noexcept
      requires StrictTotallyOrdered<Value>
      { return not (x < y); }

      constexpr friend strong_value operator+(strong_value const& x, strong_value y)
      noexcept(std::is_nothrow_copy_constructible_v<Value>)
      requires Number<Value>
      {
         y += x;
         return y;
      }

      constexpr friend strong_value operator-(strong_value const& x, strong_value y)
      noexcept(std::is_nothrow_copy_constructible_v<Value>)
      requires Number<Value>
      {
         y -= x;
         return y;
      }

      constexpr friend strong_value operator*(strong_value const& x, strong_value y)
      noexcept(std::is_nothrow_copy_constructible_v<Value>)
      requires Number<Value>
      {
         y *= x;
         return y;
      }

      constexpr friend strong_value operator/(strong_value const& x, strong_value y)
      noexcept(std::is_nothrow_copy_constructible_v<Value>)
      requires Number<Value>
      {
         y /= x;
         return y;
      }

      constexpr friend strong_value operator%(strong_value const& x, strong_value y)
      noexcept(std::is_nothrow_copy_constructible_v<Value>)
      requires Integer<Value>
      {
         y %= x;
         return y;
      }
   private:
      Value value_{};

      template<typename Self, typename T>
      constexpr strong_value& assign_impl(Self& self, T&& value)
      {
         self.value_ = std::forward<T>(value);
         return self;
      }
   };
} // namespace cjdb

#endif // CJDB_UTILITY_STRONG_VALUE_HPP
