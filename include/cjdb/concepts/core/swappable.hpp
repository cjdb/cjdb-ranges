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
#ifndef CJDB_CONCEPTS_CORE_SWAPPABLE_HPP
#define CJDB_CONCEPTS_CORE_SWAPPABLE_HPP

#include "cjdb/detail/concepts/core/swappable.hpp"

namespace cjdb {
   namespace ranges {
      constexpr auto swap = detail_swap::swap_fn{};
   } // namespace ranges

   /// \see [concept.swappable]
   ///
   template<class T>
   concept Swappable = requires(T& a, T& b) { ranges::swap(a, b); };

   /// \see [concept.swappable]
   ///
   template<class T, class U>
   concept SwappableWith =
      CommonReference<T, U> and
      requires(T&& t, U&& u) {
         ranges::swap(std::forward<T>(t), std::forward<T>(t));
         ranges::swap(std::forward<U>(u), std::forward<U>(u));
         ranges::swap(std::forward<T>(t), std::forward<U>(u));
         ranges::swap(std::forward<U>(u), std::forward<T>(t));
      };
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_SWAPPABLE_HPP
