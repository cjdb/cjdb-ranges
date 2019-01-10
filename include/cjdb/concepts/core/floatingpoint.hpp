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
#ifndef CJDB_CONCEPTS_CORE_FLOATINGPOINT_HPP
#define CJDB_CONCEPTS_CORE_FLOATINGPOINT_HPP

#include "cjdb/concepts/same.hpp"

namespace cjdb {
   template<class T>
   concept FloatingPoint =
      Same<T, float> or
      Same<T, double> or
      Same<T, long double>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_FLOATINGPOINT_HPP
