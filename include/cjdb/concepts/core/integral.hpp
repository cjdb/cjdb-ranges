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
#ifndef CJDB_CONCEPTS_CORE_INTEGRAL_HPP
#define CJDB_CONCEPTS_CORE_INTEGRAL_HPP

#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb {
   /// \see [concepts.integral]
   ///
   template<class T>
   concept integral = is_integral_v<T>;

   /// \see [concepts.integral]
   /// \note signed_integral<T> can be satisfied even by types that are not signed integral types
   ///       (6.7.1); for example, char.
   ///
   template<class T>
   concept signed_integral = integral<T> and is_signed_v<T>;

   /// \see [concepts.integral]
   /// \note unsigned_integral<T> can be satisfied even by types that are not unsigned integral types
   ///       (6.7.1); for example, bool.
   ///
   template<class T>
   concept unsigned_integral = integral<T> and !signed_integral<T>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_INTEGRAL_HPP
