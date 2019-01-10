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
#ifndef CJDB_CONCEPTS_NUMERIC_NUMBER_HPP
#define CJDB_CONCEPTS_NUMERIC_NUMBER_HPP

#include "cjdb/concepts/core/same.hpp"
#include "cjdb/concepts/object/regular.hpp"
#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb {
   template <typename T>
   concept Number =
      Regular<T> and
      requires(remove_reference_t<T> const& t1, remove_reference_t<T> n) {
         {n += t1} -> Same<T>&;
         {t1 + t1} -> T;

         {n -= t1} -> Same<T>&;
         {t1 - t1} -> T;

         {n *= t1} -> Same<T>&;
         {t1 * t1} -> T;

         {n /= t1} -> Same<T>&;
         {t1 / t1} -> T;

         {+t1} -> T;
         {-t1} -> T;

         T{0}; // axiom: T{0} == 0 and T{} == 0
         

         // axiom(std::remove_reference_t<T> const& t2) {
         //    [[assert: n == t2]];
         //
         //    requires (n += t1) == (t1 + t2);
         //    operator+ obeys the mathematical properties of addition
         //
         //    requires (n -= t1) == (t2 - t1);
         //    operator- obeys the mathematical properties of subtraction
         //
         //    requires (n *= t1) == (t1 * t2);
         //    operator* obeys the mathematical properties of multiplication
         //
         //    requires (n /= t1) == (t2 / t1);
         //    operator/ obeys the mathematical properties of division
         // }
      };
} // namespace cjdb

#endif // CJDB_CONCEPTS_NUMERIC_NUMBER_HPP