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
#ifndef CJDB_CONCEPTS_CORE_DEFAULTCONSTRUCTIBLE_HPP
#define CJDB_CONCEPTS_CORE_DEFAULTCONSTRUCTIBLE_HPP

#include "cjdb/concepts/core/constructible_from.hpp"

namespace cjdb {
   /// \see [concepts.defaultconstructible]
   ///
   template<class T>
   concept default_initializable = constructible_from<T>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_DEFAULTCONSTRUCTIBLE_HPP
