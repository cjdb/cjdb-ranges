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
#ifndef CJDB_TEST_CONCEPTS_COMPARISON_STRICT_TOTALLY_ORDERED_HPP
#define CJDB_TEST_CONCEPTS_COMPARISON_STRICT_TOTALLY_ORDERED_HPP

#include "boolean.hpp"
#include "cjdb/concepts/core/same.hpp"

namespace cjdb_test {
   class strict_totally_ordered1 {
   public:
      strict_totally_ordered1() = default;

      template<cjdb::Same<int> T>
      constexpr strict_totally_ordered1(T x)
         : x{x}
      {}

      constexpr friend bool
      operator<(strict_totally_ordered1 x, strict_totally_ordered1 y) noexcept
      { return x.x < y.x; }

      constexpr friend bool
      operator>(strict_totally_ordered1 x, strict_totally_ordered1 y) noexcept
      { return y < x; }

      constexpr friend bool
      operator<=(strict_totally_ordered1 x, strict_totally_ordered1 y) noexcept
      { return not (y < x); }

      constexpr friend bool
      operator>=(strict_totally_ordered1 x, strict_totally_ordered1 y) noexcept
      { return not (x < y); }

      constexpr friend bool
      operator==(strict_totally_ordered1 x, strict_totally_ordered1 y) noexcept
      { return x.x == y.x; }

      constexpr friend bool
      operator!=(strict_totally_ordered1 x, strict_totally_ordered1 y) noexcept
      { return not (x == y); }
   private:
      int x = 0;
   };

   class strict_totally_ordered2 {
   public:
      constexpr friend boolean
      operator<(strict_totally_ordered2 x, strict_totally_ordered2 y) noexcept
      { return x.x < y.x; }

      constexpr friend boolean
      operator>(strict_totally_ordered2 x, strict_totally_ordered2 y) noexcept
      { return y < x; }

      constexpr friend boolean
      operator<=(strict_totally_ordered2 x, strict_totally_ordered2 y) noexcept
      { return not (y < x); }

      constexpr friend boolean
      operator>=(strict_totally_ordered2 x, strict_totally_ordered2 y) noexcept
      { return not (x < y); }

      constexpr friend boolean
      operator==(strict_totally_ordered2 x, strict_totally_ordered2 y) noexcept
      { return x.x == y.x; }

      constexpr friend boolean
      operator!=(strict_totally_ordered2 x, strict_totally_ordered2 y) noexcept
      { return not (x == y); }

      constexpr operator strict_totally_ordered1() const noexcept
      { return {x}; }
   private:
      int x = 0;
   };

   class strict_totally_ordered3 {
   public:
      constexpr friend boolean
      operator<(strict_totally_ordered3 x, strict_totally_ordered3 y) noexcept
      { return x.x < y.x; }

      constexpr friend boolean
      operator>(strict_totally_ordered3 x, strict_totally_ordered3 y) noexcept
      { return y < x; }

      constexpr friend boolean
      operator<=(strict_totally_ordered3 y, strict_totally_ordered3 x) noexcept
      { return not (x < y); }

      constexpr friend boolean
      operator>=(strict_totally_ordered3 x, strict_totally_ordered3 y) noexcept
      { return not (x < y); }

      constexpr friend boolean
      operator==(strict_totally_ordered3 x, strict_totally_ordered3 y) noexcept
      { return x.x == y.x; }

      constexpr friend boolean
      operator!=(strict_totally_ordered3 x, strict_totally_ordered3 y) noexcept
      { return not (x == y); }
   private:
      int x = 0;
   };

   class not_strict_totally_ordered_no_lt {
   public:
      constexpr friend bool
      operator>(not_strict_totally_ordered_no_lt x, not_strict_totally_ordered_no_lt y) noexcept
      { return y.x < x.x; }

      constexpr friend bool
      operator<=(not_strict_totally_ordered_no_lt y, not_strict_totally_ordered_no_lt x) noexcept
      { return not (y > x); }

      constexpr friend bool
      operator>=(not_strict_totally_ordered_no_lt x, not_strict_totally_ordered_no_lt y) noexcept
      { return not (y > x); }

      constexpr friend bool
      operator==(not_strict_totally_ordered_no_lt x, not_strict_totally_ordered_no_lt y) noexcept
      { return x.x == y.x; }

      constexpr friend bool
      operator!=(not_strict_totally_ordered_no_lt x, not_strict_totally_ordered_no_lt y) noexcept
      { return not (x == y); }
   private:
      int x = 0;
   };

   class not_strict_totally_ordered_no_gt {
   public:
      constexpr friend bool
      operator<(not_strict_totally_ordered_no_gt x, not_strict_totally_ordered_no_gt y) noexcept
      { return x.x < y.x; }

      constexpr friend bool
      operator<=(not_strict_totally_ordered_no_gt y, not_strict_totally_ordered_no_gt x) noexcept
      { return not (x < y); }

      constexpr friend bool
      operator>=(not_strict_totally_ordered_no_gt x, not_strict_totally_ordered_no_gt y) noexcept
      { return not (x < y); }

      constexpr friend bool
      operator==(not_strict_totally_ordered_no_gt x, not_strict_totally_ordered_no_gt y) noexcept
      { return x.x == y.x; }

      constexpr friend bool
      operator!=(not_strict_totally_ordered_no_gt x, not_strict_totally_ordered_no_gt y) noexcept
      { return not (x == y); }
   private:
      int x = 0;
   };

   class not_strict_totally_ordered_no_le {
   public:
      constexpr friend bool
      operator<(not_strict_totally_ordered_no_le x, not_strict_totally_ordered_no_le y) noexcept
      { return x.x < y.x; }

      constexpr friend bool
      operator>(not_strict_totally_ordered_no_le x, not_strict_totally_ordered_no_le y) noexcept
      { return y < x; }

      constexpr friend bool
      operator>=(not_strict_totally_ordered_no_le x, not_strict_totally_ordered_no_le y) noexcept
      { return not (x < y); }

      constexpr friend bool
      operator==(not_strict_totally_ordered_no_le x, not_strict_totally_ordered_no_le y) noexcept
      { return x.x == y.x; }

      constexpr friend bool
      operator!=(not_strict_totally_ordered_no_le x, not_strict_totally_ordered_no_le y) noexcept
      { return not (x == y); }
   private:
      int x = 0;
   };

   class not_strict_totally_ordered_no_ge {
   public:
      constexpr friend bool
      operator<(not_strict_totally_ordered_no_ge x, not_strict_totally_ordered_no_ge y) noexcept
      { return x.x < y.x; }

      constexpr friend bool
      operator>(not_strict_totally_ordered_no_ge x, not_strict_totally_ordered_no_ge y) noexcept
      { return y < x; }

      constexpr friend bool
      operator<=(not_strict_totally_ordered_no_ge y, not_strict_totally_ordered_no_ge x) noexcept
      { return not (x < y); }

      constexpr friend bool
      operator==(not_strict_totally_ordered_no_ge x, not_strict_totally_ordered_no_ge y) noexcept
      { return x.x == y.x; }

      constexpr friend bool
      operator!=(not_strict_totally_ordered_no_ge x, not_strict_totally_ordered_no_ge y) noexcept
      { return not (x == y); }
   private:
      int x = 0;
   };

   class not_strict_totally_ordered_no_eq {
   public:
      constexpr friend bool
      operator<(not_strict_totally_ordered_no_eq x, not_strict_totally_ordered_no_eq y) noexcept
      { return x.x < y.x; }

      constexpr friend bool
      operator>(not_strict_totally_ordered_no_eq x, not_strict_totally_ordered_no_eq y) noexcept
      { return y < x; }

      constexpr friend bool
      operator<=(not_strict_totally_ordered_no_eq y, not_strict_totally_ordered_no_eq x) noexcept
      { return not (x < y); }

      constexpr friend bool
      operator>=(not_strict_totally_ordered_no_eq x, not_strict_totally_ordered_no_eq y) noexcept
      { return not (x < y); }

      constexpr friend bool
      operator!=(not_strict_totally_ordered_no_eq x, not_strict_totally_ordered_no_eq y) noexcept
      { return x.x != y.x; }
   private:
      int x = 0;
   };

   class not_strict_totally_ordered_no_ne {
   public:
      constexpr friend bool
      operator<(not_strict_totally_ordered_no_ne x, not_strict_totally_ordered_no_ne y) noexcept
      { return x.x < y.x; }

      constexpr friend bool
      operator>(not_strict_totally_ordered_no_ne x, not_strict_totally_ordered_no_ne y) noexcept
      { return y < x; }

      constexpr friend bool
      operator<=(not_strict_totally_ordered_no_ne y, not_strict_totally_ordered_no_ne x) noexcept
      { return not (x < y); }

      constexpr friend bool
      operator>=(not_strict_totally_ordered_no_ne x, not_strict_totally_ordered_no_ne y) noexcept
      { return not (x < y); }

      constexpr friend bool
      operator==(not_strict_totally_ordered_no_ne x, not_strict_totally_ordered_no_ne y) noexcept
      { return x.x == y.x; }
   private:
      int x = 0;
   };

   class not_strict_totally_ordered_wrong_return {
   public:
      constexpr friend bad_equality_boolean
      operator<(not_strict_totally_ordered_wrong_return x, not_strict_totally_ordered_wrong_return y) noexcept
      { return x.x < y.x; }

      constexpr friend bad_equality_boolean
      operator>(not_strict_totally_ordered_wrong_return x, not_strict_totally_ordered_wrong_return y) noexcept
      { return y < x; }

      constexpr friend bad_equality_boolean
      operator<=(not_strict_totally_ordered_wrong_return y, not_strict_totally_ordered_wrong_return x) noexcept
      { return not (x < y); }

      constexpr friend bad_equality_boolean
      operator>=(not_strict_totally_ordered_wrong_return x, not_strict_totally_ordered_wrong_return y) noexcept
      { return not (x < y); }

      constexpr friend bad_equality_boolean
      operator==(not_strict_totally_ordered_wrong_return x, not_strict_totally_ordered_wrong_return y) noexcept
      { return x.x == y.x; }

      constexpr friend bad_equality_boolean
      operator!=(not_strict_totally_ordered_wrong_return x, not_strict_totally_ordered_wrong_return y) noexcept
      { return not (x == y); }
   private:
      int x = 0;
   };
} // namespace cjdb_test

#endif // CJDB_TEST_CONCEPTS_COMPARISON_STRICT_TOTALLY_ORDERED_HPP
