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
#ifndef CJDB_CONCEPTS_CORE_CONSTRUCTIBLE_HPP
#define CJDB_CONCEPTS_CORE_CONSTRUCTIBLE_HPP

#include "cjdb/concepts/core/destructible.hpp"
#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb {
   /// \brief The `constructible_from` concept constrains the initialization of a variable of a given
   ///        type with a particular set of argument types.
   /// \see [concepts.constructible]
   ///
   template<class T, class... Args>
   concept constructible_from = destructible<T> and is_constructible_v<T, Args...>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_CONSTRUCTIBLE_HPP
