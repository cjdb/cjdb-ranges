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
} // namespace cjdb_test

#endif // CJDB_TEST_CONCEPTS_COMPARISON_BOOLEAN_HPP
