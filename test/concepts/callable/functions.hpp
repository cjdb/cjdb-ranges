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
#ifndef CJDB_TEST_CONCEPTS_CALLABLE_FUNCTIONS_HPP

namespace regular_invocable {
   struct A {
      int i = 13;
      constexpr int f() const noexcept { return 42; };
      constexpr int g(int i) { return 2 * i + 1; }
      constexpr int h(int j) && { return i * j; };
   };

   constexpr int f() noexcept { return 13; }
   constexpr int g(int i) { return 2 * i + 1; }
} // namespace regular_invocable

namespace predicate {
   struct l2r_sorted {
      template<class T>
      constexpr bool operator()(T const& a, T const& b, T const& c) const noexcept
      {
         return a <= b and b <= c;
      }
   };

   struct not_a_predicate {
      constexpr void operator()() const noexcept {}
   };
} // namespace predicate

namespace relation {
   struct less {
      template<class T1, class T2>
      constexpr bool operator()(T1 const& x, T2 const& y) const noexcept
      {
         return x < y;
      }
   };

   constexpr int greater(int x, int y) noexcept
   {
      return less{}(y, x);
   }
} // namespace relation

namespace relation {} // namespace relation
namespace strict_weak_order {} // namespace strict_weak_order

#endif // CJDB_TEST_CONCEPTS_CALLABLE_FUNCTIONS_HPP
