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

#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb::detail_same {
   /// \brief Concept equivalent of is_same_v to enable same_as<T, U> subsuming same_as<U, T> and vice
   ///        versa.
   ///
   template<class T, class U>
   concept is_same = is_same_v<T, U>;
} // namespace cjdb::detail_same

#endif // CJDB_DETAIL_CONCEPTS_CORE_SAME_HPP
