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
#ifndef CJDB_TEST_CONCEPTS_COMPARISON_EQUALITYCOMPARABLE_HPP
#define CJDB_TEST_CONCEPTS_COMPARISON_EQUALITYCOMPARABLE_HPP

#include "boolean.hpp"
#include "cjdb/concepts/core/same_as.hpp"

namespace cjdb_test {
   struct equality_comparable4;
   struct not_equality_comparable1;

   struct equality_comparable1 {
      equality_comparable1() = default;

      template<cjdb::same_as<int> T>
      equality_comparable1(T) {}

      constexpr friend bool operator==(equality_comparable1, equality_comparable1) noexcept
      { return true; }

      constexpr friend bool operator!=(equality_comparable1 x, equality_comparable1 y) noexcept
      { return not (x == y); }

      constexpr friend bool
      operator==(equality_comparable1 const&, equality_comparable4 const&) noexcept
      { return true; }

      constexpr friend bool
      operator!=(equality_comparable1 const& x, equality_comparable4 const& y) noexcept
      { return not (x == y); }

      constexpr friend bool
      operator==(equality_comparable4 const&, equality_comparable1 const&) noexcept
      { return true; }

      constexpr friend bool
      operator!=(equality_comparable4 const& x, equality_comparable1 const& y) noexcept
      { return not (x == y); }
   };

   struct equality_comparable2 {
      constexpr int operator==(equality_comparable2) const noexcept
      { return 1; }
      constexpr friend long operator!=(equality_comparable2, equality_comparable2) noexcept
      { return 0L; }
   };

   struct equality_comparable3 {
      constexpr cjdb_test::boolean operator!=(equality_comparable3 other) const noexcept
      { return not (*this == other); }
      constexpr friend cjdb_test::boolean
      operator==(equality_comparable3, equality_comparable3) noexcept
      { return true; }

      constexpr operator equality_comparable1() const noexcept { return {}; }
      constexpr operator equality_comparable2() const noexcept { return {}; }
   };

   struct equality_comparable4 {
      constexpr bool operator==(equality_comparable4) const noexcept
      { return true; }
      constexpr bool operator!=(equality_comparable4 other) const noexcept
      { return not (*this == other); }

      constexpr operator equality_comparable1() const noexcept { return {}; }
   };

   struct not_equality_comparable1 {
      constexpr friend bool operator==(not_equality_comparable1, not_equality_comparable1) noexcept
      { return true; }
   };

   struct not_equality_comparable2 {
      constexpr friend bool operator!=(not_equality_comparable2, not_equality_comparable2) noexcept
      { return false; }
   };

   struct not_equality_comparable3 {
      constexpr friend cjdb_test::bad_equality_boolean
      operator==(not_equality_comparable3, not_equality_comparable3) noexcept
      { return true; }
      constexpr friend cjdb_test::bad_equality_boolean
      operator!=(not_equality_comparable3 x, not_equality_comparable3 y) noexcept
      { return not (x == y); }
   };
} // namespace cjdb_test

#endif // CJDB_TEST_CONCEPTS_COMPARISON_EQUALITYCOMPARABLE_HPP
