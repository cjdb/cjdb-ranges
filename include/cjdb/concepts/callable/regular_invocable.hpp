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
#ifndef CJDB_CONCEPTS_CALLABLE_REGULARINVOCABLE_HPP
#define CJDB_CONCEPTS_CALLABLE_REGULARINVOCABLE_HPP

#include "cjdb/concepts/callable/invocable.hpp"

namespace cjdb {
   /// \brief The `invoke` function call expression shall be equality-preserving and shall not
   ///        modify the function object or the arguments.
   /// \note This requirement supersedes the annotation in the definition of `invocable`.
   /// \note A random number generator does not satisfy `regular_invocable`.
   /// \note The distinction between `invocable` and `regular_invocable` is purely semantic.
   /// \see [concept.regularinvocable]
   ///
   template<class F, class... Args>
   concept regular_invocable = invocable<F, Args...>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_CALLABLE_REGULARINVOCABLE_HPP
