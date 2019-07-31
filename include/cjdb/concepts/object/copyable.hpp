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
#ifndef CJDB_CONCEPTS_OBJECT_COPYABLE_HPP
#define CJDB_CONCEPTS_OBJECT_COPYABLE_HPP

#include "cjdb/concepts/core/assignable_from.hpp"
#include "cjdb/concepts/core/copy_constructible.hpp"
#include "cjdb/concepts/object/movable.hpp"

namespace cjdb {
   template<class T>
   concept copyable = copy_constructible<T> and movable<T> and assignable_from<T&, const T&>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_OBJECT_COPYABLE_HPP
