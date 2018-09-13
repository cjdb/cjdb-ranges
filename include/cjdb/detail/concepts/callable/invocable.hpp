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
#ifndef CJDB_DETAIL_CONCEPTS_CALLABLE_INVOCABLE_HPP
#define CJDB_DETAIL_CONCEPTS_CALLABLE_INVOCABLE_HPP

#include "cjdb/detail/functional/invoke.hpp"
#include <utility>

namespace cjdb {
   /// \brief The `Invocable` concept specifies a relationship between a callable type `F` and a set
   ///        of argument types `Args...` which can be evaluated by the library function `invoke`.
   /// \note  A function that generates random numbers can satisfy `Invocable`, since the `invoke`
   ///        function call expression is not required to be equality-preserving.
   /// \see [concept.invocable]
   ///
   template<class F, class... Args>
   concept Invocable = requires(F&& f, Args&&... args) {
      invoke(std::forward<F>(f), std::forward<Args>(args)...); // not required to be equality-preserving
   };
} // namespace cjdb

#endif // CJDB_DETAIL_CONCEPTS_CALLABLE_INVOCABLE_HPP
