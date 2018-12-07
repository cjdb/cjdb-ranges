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
#ifndef CJDB_DETAIL_CONCEPTS_CORE_SAME_HPP
#define CJDB_DETAIL_CONCEPTS_CORE_SAME_HPP

#include "cjdb/detail/type_traits/type_traits.hpp"

namespace cjdb {
   namespace detail_same {
      /// \brief Concept equivalent of is_same_v to enable Same<T, U> subsuming Same<U, T> and vice
      ///        versa.
      ///
      template<class T, class U>
      concept is_same = is_same_v<T, U>;
   }

   /// \brief Checks if two types are exactly the same (including cv-qualifiers and ref-qualifiers).
   /// \note `Same<T, U>` subsumes `Same<U, T>` and vice versa.
   /// \see [concept.same]
   ///
   template<class T, class U>
   concept Same = detail_same::is_same<T, U> and detail_same::is_same<U, T>;
} // namespace cjdb

#endif // CJDB_DETAIL_CONCEPTS_CORE_SAME_HPP
