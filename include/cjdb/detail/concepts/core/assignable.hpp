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
#ifndef CJDB_DETAIL_CONCEPTS_CORE_ASSIGNABLE_HPP
#define CJDB_DETAIL_CONCEPTS_CORE_ASSIGNABLE_HPP

#include "cjdb/detail/concepts/core/commonreference.hpp"
#include "cjdb/detail/concepts/core/same.hpp"
#include "cjdb/detail/type_traits/type_traits.hpp"

namespace cjdb {
   /// \see [concepts.assignable]
   ///
   template<class LHS, class RHS>
   concept Assignable =
      is_lvalue_reference_v<LHS> and
      CommonReference<const remove_reference_t<LHS>&, const remove_reference_t<RHS>&> and
      requires(LHS lhs, RHS&& rhs) {
         lhs = std::forward<RHS>(rhs);
         requires Same<decltype(lhs = std::forward<RHS>(rhs)), LHS>;
      };
} // namespace cjdb

#endif // CJDB_DETAIL_CONCEPTS_CORE_ASSIGNABLE_HPP
