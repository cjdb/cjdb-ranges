//
//  Copyright Codeplay Software, Ltd.
//  Author: Christopher Di Bella
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
#ifndef CJDB_CONCEPTS_NUMERIC_INTEGER_HPP
#define CJDB_CONCEPTS_NUMERIC_INTEGER_HPP

#include "cjdb/concepts/comparison/stricttotallyordered.hpp"
#include "cjdb/concepts/core/same.hpp"
#include "cjdb/concepts/numeric/orderednumber.hpp"
#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb {
   template <typename I>
   concept Integer = OrderedNumber<I> and
      StrictTotallyOrdered<signed char> and
      StrictTotallyOrdered<short> and
      StrictTotallyOrdered<int> and
      StrictTotallyOrdered<long> and
      StrictTotallyOrdered<long long> and
      requires(remove_reference_t<I> const& i1, remove_reference_t<I> i) {
         {i %= i1} -> Same<I>&;
         {i1 % i1} -> I;

         {++i} -> Same<I>&;
         i++; requires Same<decltype(i++), I>;

         {--i} -> Same<I>&;
         i--; requires Same<decltype(i--), I>;

         // axiom(std::remove_reference_t<I> const& i2) {
         //    [[assert: i == i2]];
         //    requires (i %= i1) == (i2 % i1);
         //    operator% obeys the mathematical properties of modular arithmetic
         // };

         // axiom(std::remove_reference_t<I> i2) {
         //    [[assert: i == i2]];
         //    i2++ == i;
         //    i2 == i + 1;
         //    ++i == i2;
         //    i2-- == i;
         //    i2 == i - 1;
         //    --i == i2;
         // };
      };
} // namespace cjdb

#endif // CJDB_CONCEPTS_NUMERIC_INTEGER_HPP