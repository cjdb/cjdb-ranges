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
#ifndef CJDB_TEST_CONCEPTS_COMPARISON_BOOLEAN_HPP
#define CJDB_TEST_CONCEPTS_COMPARISON_BOOLEAN_HPP

// TODO: refactor so that there aren't so many classes.
namespace cjdb_test {
   class boolean {
   public:
      boolean() = default;

      constexpr boolean(bool const b) noexcept
         : result_{b}
      {}

      constexpr boolean& operator=(bool const b) noexcept
      {
         result_ = b;
         return *this;
      }

      constexpr boolean operator not() const noexcept
      { return result_; }

      friend constexpr bool operator and(boolean const x, boolean const y) noexcept
      { return static_cast<bool>(x) and static_cast<bool>(y); }

      friend constexpr bool operator and(bool const x, boolean const y) noexcept
      { return x and static_cast<bool>(y); }

      friend constexpr bool operator and(boolean const y, bool const x) noexcept
      { return x and y; }

      friend constexpr bool operator or(boolean const x, boolean const y) noexcept
      { return static_cast<bool>(x) or static_cast<bool>(y); }

      friend constexpr bool operator or(bool const x, boolean const y) noexcept
      { return x or static_cast<bool>(y); }

      friend constexpr bool operator or(boolean const y, bool const x) noexcept
      { return x or y; }

      friend constexpr boolean operator==(boolean const x, boolean const y) noexcept
      { return static_cast<bool>(x) == static_cast<bool>(y); }

      friend constexpr boolean operator==(bool const x, boolean const y) noexcept
      { return boolean{x} == y; }

      friend constexpr boolean operator==(boolean const y, bool const x) noexcept
      { return boolean{x} == y; }

      friend constexpr boolean operator!=(boolean const x, boolean const y) noexcept
      { return not (x == y); }

      friend constexpr boolean operator!=(bool const x, boolean const y) noexcept
      { return not (x == y); }

      friend constexpr boolean operator!=(boolean const y, bool const x) noexcept
      { return not (x == y); }

      constexpr operator bool() const noexcept
      {
         return result_;
      }
   private:
      bool result_ = false;
   };

   class explicitly_constructible_boolean {
   public:
      explicitly_constructible_boolean() = default;

      constexpr explicit explicitly_constructible_boolean(bool const b) noexcept
         : result_{b}
      {}

      constexpr explicitly_constructible_boolean& operator=(bool const b) noexcept
      {
         result_ = b;
         return *this;
      }

      constexpr bool operator not() const noexcept
      { return result_; }

      friend constexpr bool operator and(explicitly_constructible_boolean const x, explicitly_constructible_boolean const y) noexcept
      { return static_cast<bool>(x) and static_cast<bool>(y); }

      friend constexpr bool operator and(bool const x, explicitly_constructible_boolean const y) noexcept
      { return x and static_cast<bool>(y); }

      friend constexpr bool operator and(explicitly_constructible_boolean const y, bool const x) noexcept
      { return x and y; }

      friend constexpr bool operator or(explicitly_constructible_boolean const x, explicitly_constructible_boolean const y) noexcept
      { return static_cast<bool>(x) or static_cast<bool>(y); }

      friend constexpr bool operator or(bool const x, explicitly_constructible_boolean const y) noexcept
      { return x or static_cast<bool>(y); }

      friend constexpr bool operator or(explicitly_constructible_boolean const y, bool const x) noexcept
      { return x or y; }

      friend constexpr bool operator==(explicitly_constructible_boolean const x, explicitly_constructible_boolean const y) noexcept
      { return static_cast<bool>(x) == static_cast<bool>(y); }

      friend constexpr bool operator==(bool const x, explicitly_constructible_boolean const y) noexcept
      { return explicitly_constructible_boolean{x} == y; }

      friend constexpr bool operator==(explicitly_constructible_boolean const y, bool const x) noexcept
      { return explicitly_constructible_boolean{x} == y; }

      friend constexpr bool operator!=(explicitly_constructible_boolean const x, explicitly_constructible_boolean const y) noexcept
      { return not (x == y); }

      friend constexpr bool operator!=(bool const x, explicitly_constructible_boolean const y) noexcept
      { return not (x == y); }

      friend constexpr bool operator!=(explicitly_constructible_boolean const y, bool const x) noexcept
      { return not (x == y); }

      constexpr operator bool() const noexcept
      {
         return result_;
      }
   private:
      bool result_ = false;
   };

   class explicitly_convertible_boolean {
   public:
      explicitly_convertible_boolean() = default;

      constexpr explicitly_convertible_boolean(bool const b) noexcept
         : result_{b}
      {}

      constexpr explicitly_convertible_boolean& operator=(bool const b) noexcept
      {
         result_ = b;
         return *this;
      }

      constexpr bool operator not() const noexcept
      { return result_; }

      friend constexpr bool operator and(explicitly_convertible_boolean const x, explicitly_convertible_boolean const y) noexcept
      { return static_cast<bool>(x) and static_cast<bool>(y); }

      friend constexpr bool operator and(bool const x, explicitly_convertible_boolean const y) noexcept
      { return x and static_cast<bool>(y); }

      friend constexpr bool operator and(explicitly_convertible_boolean const y, bool const x) noexcept
      { return x and y; }

      friend constexpr bool operator or(explicitly_convertible_boolean const x, explicitly_convertible_boolean const y) noexcept
      { return static_cast<bool>(x) or static_cast<bool>(y); }

      friend constexpr bool operator or(bool const x, explicitly_convertible_boolean const y) noexcept
      { return x or static_cast<bool>(y); }

      friend constexpr bool operator or(explicitly_convertible_boolean const y, bool const x) noexcept
      { return x or y; }

      friend constexpr bool operator==(explicitly_convertible_boolean const x, explicitly_convertible_boolean const y) noexcept
      { return static_cast<bool>(x) == static_cast<bool>(y); }

      friend constexpr bool operator==(bool const x, explicitly_convertible_boolean const y) noexcept
      { return explicitly_convertible_boolean{x} == y; }

      friend constexpr bool operator==(explicitly_convertible_boolean const y, bool const x) noexcept
      { return explicitly_convertible_boolean{x} == y; }

      friend constexpr bool operator!=(explicitly_convertible_boolean const x, explicitly_convertible_boolean const y) noexcept
      { return not (x == y); }

      friend constexpr bool operator!=(bool const x, explicitly_convertible_boolean const y) noexcept
      { return not (x == y); }

      friend constexpr bool operator!=(explicitly_convertible_boolean const y, bool const x) noexcept
      { return not (x == y); }

      constexpr explicit operator bool() const noexcept
      {
         return result_;
      }
   private:
      bool result_ = false;
   };

   class bad_not_boolean {
   public:
      bad_not_boolean() = default;

      constexpr bad_not_boolean(bool const b) noexcept
         : result_{b}
      {}

      constexpr bad_not_boolean& operator=(bool const b) noexcept
      {
         result_ = b;
         return *this;
      }

      constexpr void operator not() const noexcept {}

      friend constexpr bool operator and(bad_not_boolean const x, bad_not_boolean const y) noexcept
      { return static_cast<bool>(x) and static_cast<bool>(y); }

      friend constexpr bool operator and(bool const x, bad_not_boolean const y) noexcept
      { return x and static_cast<bool>(y); }

      friend constexpr bool operator and(bad_not_boolean const y, bool const x) noexcept
      { return x and y; }

      friend constexpr bool operator or(bad_not_boolean const x, bad_not_boolean const y) noexcept
      { return static_cast<bool>(x) or static_cast<bool>(y); }

      friend constexpr bool operator or(bool const x, bad_not_boolean const y) noexcept
      { return x or static_cast<bool>(y); }

      friend constexpr bool operator or(bad_not_boolean const y, bool const x) noexcept
      { return x or y; }

      friend constexpr bool operator==(bad_not_boolean const x, bad_not_boolean const y) noexcept
      { return static_cast<bool>(x) == static_cast<bool>(y); }

      friend constexpr bool operator==(bool const x, bad_not_boolean const y) noexcept
      { return bad_not_boolean{x} == y; }

      friend constexpr bool operator==(bad_not_boolean const y, bool const x) noexcept
      { return bad_not_boolean{x} == y; }

      friend constexpr bool operator!=(bad_not_boolean const x, bad_not_boolean const y) noexcept
      { return not (x == y); }

      friend constexpr bool operator!=(bool const x, bad_not_boolean const y) noexcept
      { return not (x == y); }

      friend constexpr bool operator!=(bad_not_boolean const y, bool const x) noexcept
      { return not (x == y); }

      constexpr operator bool() const noexcept
      {
         return result_;
      }
   private:
      bool result_ = false;
   };

   class bad_and_boolean1 {
   public:
      bad_and_boolean1() = default;

      constexpr bad_and_boolean1(bool const b) noexcept
         : result_{b}
      {}

      constexpr bad_and_boolean1& operator=(bool const b) noexcept
      {
         result_ = b;
         return *this;
      }

      constexpr bool operator not() const noexcept
      { return result_; }

      friend constexpr bad_and_boolean1 operator and(bad_and_boolean1 const x, bad_and_boolean1 const y) noexcept
      { return static_cast<bool>(x) and static_cast<bool>(y); }

      friend constexpr bool operator and(bool const x, bad_and_boolean1 const y) noexcept
      { return x and static_cast<bool>(y); }

      friend constexpr bool operator and(bad_and_boolean1 const y, bool const x) noexcept
      { return x and y; }

      friend constexpr bool operator or(bad_and_boolean1 const x, bad_and_boolean1 const y) noexcept
      { return static_cast<bool>(x) or static_cast<bool>(y); }

      friend constexpr bool operator or(bool const x, bad_and_boolean1 const y) noexcept
      { return x or static_cast<bool>(y); }

      friend constexpr bool operator or(bad_and_boolean1 const y, bool const x) noexcept
      { return x or y; }

      friend constexpr bool operator==(bad_and_boolean1 const x, bad_and_boolean1 const y) noexcept
      { return static_cast<bool>(x) == static_cast<bool>(y); }

      friend constexpr bool operator==(bool const x, bad_and_boolean1 const y) noexcept
      { return bad_and_boolean1{x} == y; }

      friend constexpr bool operator==(bad_and_boolean1 const y, bool const x) noexcept
      { return bad_and_boolean1{x} == y; }

      friend constexpr bool operator!=(bad_and_boolean1 const x, bad_and_boolean1 const y) noexcept
      { return not (x == y); }

      friend constexpr bool operator!=(bool const x, bad_and_boolean1 const y) noexcept
      { return not (x == y); }

      friend constexpr bool operator!=(bad_and_boolean1 const y, bool const x) noexcept
      { return not (x == y); }

      constexpr operator bool() const noexcept
      {
         return result_;
      }
   private:
      bool result_ = false;
   };

   class bad_and_boolean2 {
   public:
      bad_and_boolean2() = default;

      constexpr bad_and_boolean2(bool const b) noexcept
         : result_{b}
      {}

      constexpr bad_and_boolean2& operator=(bool const b) noexcept
      {
         result_ = b;
         return *this;
      }

      constexpr bool operator not() const noexcept
      { return result_; }

      friend constexpr bool operator and(bad_and_boolean2 const x, bad_and_boolean2 const y) noexcept
      { return static_cast<bool>(x) and static_cast<bool>(y); }

      friend constexpr bad_and_boolean2 operator and(bool const x, bad_and_boolean2 const y) noexcept
      { return x and static_cast<bool>(y); }

      friend constexpr bool operator and(bad_and_boolean2 const y, bool const x) noexcept
      { return x and y; }

      friend constexpr bool operator or(bad_and_boolean2 const x, bad_and_boolean2 const y) noexcept
      { return static_cast<bool>(x) or static_cast<bool>(y); }

      friend constexpr bool operator or(bool const x, bad_and_boolean2 const y) noexcept
      { return x or static_cast<bool>(y); }

      friend constexpr bool operator or(bad_and_boolean2 const y, bool const x) noexcept
      { return x or y; }

      friend constexpr bool operator==(bad_and_boolean2 const x, bad_and_boolean2 const y) noexcept
      { return static_cast<bool>(x) == static_cast<bool>(y); }

      friend constexpr bool operator==(bool const x, bad_and_boolean2 const y) noexcept
      { return bad_and_boolean2{x} == y; }

      friend constexpr bool operator==(bad_and_boolean2 const y, bool const x) noexcept
      { return bad_and_boolean2{x} == y; }

      friend constexpr bool operator!=(bad_and_boolean2 const x, bad_and_boolean2 const y) noexcept
      { return not (x == y); }

      friend constexpr bool operator!=(bool const x, bad_and_boolean2 const y) noexcept
      { return not (x == y); }

      friend constexpr bool operator!=(bad_and_boolean2 const y, bool const x) noexcept
      { return not (x == y); }

      constexpr operator bool() const noexcept
      {
         return result_;
      }
   private:
      bool result_ = false;
   };

   class bad_and_boolean3 {
   public:
      bad_and_boolean3() = default;

      constexpr bad_and_boolean3(bool const b) noexcept
         : result_{b}
      {}

      constexpr bad_and_boolean3& operator=(bool const b) noexcept
      {
         result_ = b;
         return *this;
      }

      constexpr bool operator not() const noexcept
      { return result_; }

      friend constexpr bool operator and(bad_and_boolean3 const x, bad_and_boolean3 const y) noexcept
      { return static_cast<bool>(x) and static_cast<bool>(y); }

      friend constexpr bool operator and(bool const x, bad_and_boolean3 const y) noexcept
      { return x and static_cast<bool>(y); }

      friend constexpr bad_and_boolean3 operator and(bad_and_boolean3 const y, bool const x) noexcept
      { return x and y; }

      friend constexpr bool operator or(bad_and_boolean3 const x, bad_and_boolean3 const y) noexcept
      { return static_cast<bool>(x) or static_cast<bool>(y); }

      friend constexpr bool operator or(bool const x, bad_and_boolean3 const y) noexcept
      { return x or static_cast<bool>(y); }

      friend constexpr bool operator or(bad_and_boolean3 const y, bool const x) noexcept
      { return x or y; }

      friend constexpr bool operator==(bad_and_boolean3 const x, bad_and_boolean3 const y) noexcept
      { return static_cast<bool>(x) == static_cast<bool>(y); }

      friend constexpr bool operator==(bool const x, bad_and_boolean3 const y) noexcept
      { return bad_and_boolean3{x} == y; }

      friend constexpr bool operator==(bad_and_boolean3 const y, bool const x) noexcept
      { return bad_and_boolean3{x} == y; }

      friend constexpr bool operator!=(bad_and_boolean3 const x, bad_and_boolean3 const y) noexcept
      { return not (x == y); }

      friend constexpr bool operator!=(bool const x, bad_and_boolean3 const y) noexcept
      { return not (x == y); }

      friend constexpr bool operator!=(bad_and_boolean3 const y, bool const x) noexcept
      { return not (x == y); }

      constexpr operator bool() const noexcept
      {
         return result_;
      }
   private:
      bool result_ = false;
   };

   class bad_or_boolean1 {
   public:
      bad_or_boolean1() = default;

      constexpr bad_or_boolean1(bool const b) noexcept
         : result_{b}
      {}

      constexpr bad_or_boolean1& operator=(bool const b) noexcept
      {
         result_ = b;
         return *this;
      }

      constexpr bool operator not() const noexcept
      { return result_; }

      friend constexpr bool operator and(bad_or_boolean1 const x, bad_or_boolean1 const y) noexcept
      { return static_cast<bool>(x) and static_cast<bool>(y); }

      friend constexpr bool operator and(bool const x, bad_or_boolean1 const y) noexcept
      { return x and static_cast<bool>(y); }

      friend constexpr bool operator and(bad_or_boolean1 const y, bool const x) noexcept
      { return x and y; }

      friend constexpr bad_or_boolean1 operator or(bad_or_boolean1 const x, bad_or_boolean1 const y) noexcept
      { return static_cast<bool>(x) or static_cast<bool>(y); }

      friend constexpr bool operator or(bool const x, bad_or_boolean1 const y) noexcept
      { return x or static_cast<bool>(y); }

      friend constexpr bool operator or(bad_or_boolean1 const y, bool const x) noexcept
      { return x or y; }

      friend constexpr bool operator==(bad_or_boolean1 const x, bad_or_boolean1 const y) noexcept
      { return static_cast<bool>(x) == static_cast<bool>(y); }

      friend constexpr bool operator==(bool const x, bad_or_boolean1 const y) noexcept
      { return bad_or_boolean1{x} == y; }

      friend constexpr bool operator==(bad_or_boolean1 const y, bool const x) noexcept
      { return bad_or_boolean1{x} == y; }

      friend constexpr bool operator!=(bad_or_boolean1 const x, bad_or_boolean1 const y) noexcept
      { return not (x == y); }

      friend constexpr bool operator!=(bool const x, bad_or_boolean1 const y) noexcept
      { return not (x == y); }

      friend constexpr bool operator!=(bad_or_boolean1 const y, bool const x) noexcept
      { return not (x == y); }

      constexpr operator bool() const noexcept
      {
         return result_;
      }
   private:
      bool result_ = false;
   };

   class bad_or_boolean2 {
   public:
      bad_or_boolean2() = default;

      constexpr bad_or_boolean2(bool const b) noexcept
         : result_{b}
      {}

      constexpr bad_or_boolean2& operator=(bool const b) noexcept
      {
         result_ = b;
         return *this;
      }

      constexpr bool operator not() const noexcept
      { return result_; }

      friend constexpr bool operator and(bad_or_boolean2 const x, bad_or_boolean2 const y) noexcept
      { return static_cast<bool>(x) and static_cast<bool>(y); }

      friend constexpr bool operator and(bool const x, bad_or_boolean2 const y) noexcept
      { return x and static_cast<bool>(y); }

      friend constexpr bool operator and(bad_or_boolean2 const y, bool const x) noexcept
      { return x and y; }

      friend constexpr bool operator or(bad_or_boolean2 const x, bad_or_boolean2 const y) noexcept
      { return static_cast<bool>(x) or static_cast<bool>(y); }

      friend constexpr bad_or_boolean2 operator or(bool const x, bad_or_boolean2 const y) noexcept
      { return x or static_cast<bool>(y); }

      friend constexpr bool operator or(bad_or_boolean2 const y, bool const x) noexcept
      { return x or y; }

      friend constexpr bool operator==(bad_or_boolean2 const x, bad_or_boolean2 const y) noexcept
      { return static_cast<bool>(x) == static_cast<bool>(y); }

      friend constexpr bool operator==(bool const x, bad_or_boolean2 const y) noexcept
      { return bad_or_boolean2{x} == y; }

      friend constexpr bool operator==(bad_or_boolean2 const y, bool const x) noexcept
      { return bad_or_boolean2{x} == y; }

      friend constexpr bool operator!=(bad_or_boolean2 const x, bad_or_boolean2 const y) noexcept
      { return not (x == y); }

      friend constexpr bool operator!=(bool const x, bad_or_boolean2 const y) noexcept
      { return not (x == y); }

      friend constexpr bool operator!=(bad_or_boolean2 const y, bool const x) noexcept
      { return not (x == y); }

      constexpr operator bool() const noexcept
      {
         return result_;
      }
   private:
      bool result_ = false;
   };

   class bad_or_boolean3 {
   public:
      bad_or_boolean3() = default;

      constexpr bad_or_boolean3(bool const b) noexcept
         : result_{b}
      {}

      constexpr bad_or_boolean3& operator=(bool const b) noexcept
      {
         result_ = b;
         return *this;
      }

      constexpr bool operator not() const noexcept
      { return result_; }

      friend constexpr bool operator and(bad_or_boolean3 const x, bad_or_boolean3 const y) noexcept
      { return static_cast<bool>(x) and static_cast<bool>(y); }

      friend constexpr bool operator and(bool const x, bad_or_boolean3 const y) noexcept
      { return x and static_cast<bool>(y); }

      friend constexpr bool operator and(bad_or_boolean3 const y, bool const x) noexcept
      { return x and y; }

      friend constexpr bool operator or(bad_or_boolean3 const x, bad_or_boolean3 const y) noexcept
      { return static_cast<bool>(x) or static_cast<bool>(y); }

      friend constexpr bool operator or(bool const x, bad_or_boolean3 const y) noexcept
      { return x or static_cast<bool>(y); }

      friend constexpr bad_or_boolean3 operator or(bad_or_boolean3 const y, bool const x) noexcept
      { return x or y; }

      friend constexpr bool operator==(bad_or_boolean3 const x, bad_or_boolean3 const y) noexcept
      { return static_cast<bool>(x) == static_cast<bool>(y); }

      friend constexpr bool operator==(bool const x, bad_or_boolean3 const y) noexcept
      { return bad_or_boolean3{x} == y; }

      friend constexpr bool operator==(bad_or_boolean3 const y, bool const x) noexcept
      { return bad_or_boolean3{x} == y; }

      friend constexpr bool operator!=(bad_or_boolean3 const x, bad_or_boolean3 const y) noexcept
      { return not (x == y); }

      friend constexpr bool operator!=(bool const x, bad_or_boolean3 const y) noexcept
      { return not (x == y); }

      friend constexpr bool operator!=(bad_or_boolean3 const y, bool const x) noexcept
      { return not (x == y); }

      constexpr operator bool() const noexcept
      {
         return result_;
      }
   private:
      bool result_ = false;
   };

   //==
   class bad_equality_boolean {
   public:
      bad_equality_boolean() = default;

      constexpr bad_equality_boolean(bool const b) noexcept
         : result_{b}
      {}

      constexpr bad_equality_boolean& operator=(bool const b) noexcept
      {
         result_ = b;
         return *this;
      }

      constexpr bool operator not() const noexcept
      { return result_; }

      friend constexpr bool operator and(bad_equality_boolean const x, bad_equality_boolean const y) noexcept
      { return static_cast<bool>(x) and static_cast<bool>(y); }

      friend constexpr bool operator and(bool const x, bad_equality_boolean const y) noexcept
      { return x and static_cast<bool>(y); }

      friend constexpr bool operator and(bad_equality_boolean const y, bool const x) noexcept
      { return x and y; }

      friend constexpr bool operator or(bad_equality_boolean const x, bad_equality_boolean const y) noexcept
      { return static_cast<bool>(x) or static_cast<bool>(y); }

      friend constexpr bool operator or(bool const x, bad_equality_boolean const y) noexcept
      { return x or static_cast<bool>(y); }

      friend constexpr bool operator or(bad_equality_boolean const y, bool const x) noexcept
      { return x or y; }

      friend constexpr void operator==(bad_equality_boolean const, bad_equality_boolean const) noexcept {}
      friend constexpr void operator==(bool const, bad_equality_boolean const) noexcept {}
      friend constexpr void operator==(bad_equality_boolean const, bool const) noexcept {}

      friend constexpr void operator!=(bad_equality_boolean const, bad_equality_boolean const) noexcept {}
      friend constexpr void operator!=(bool const, bad_equality_boolean const) noexcept {}
      friend constexpr void operator!=(bad_equality_boolean const, bool const) noexcept {}

      constexpr operator bool() const noexcept
      {
         return result_;
      }
   private:
      bool result_ = false;
   };
} // namespace cjdb_test

#endif // CJDB_TEST_CONCEPTS_COMPARISON_BOOLEAN_HPP
