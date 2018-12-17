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
#ifndef CJDB_DETAIL_FUNCTIONAL_RANGECMP_GREATER_EQUAL_HPP
#define CJDB_DETAIL_FUNCTIONAL_RANGECMP_GREATER_EQUAL_HPP

#include "cjdb/concepts/comparison/stricttotallyordered.hpp"
#include "cjdb/functional/rangecmp/less.hpp"
#include "cjdb/type_traits/type_traits.hpp"
#include <utility>

#include "cjdb/detail/define.hpp"

namespace cjdb::ranges {
   /// \brief Function object for performing comparisons. Applies operator>=.
   ///
   struct greater_equal {
      /// \returns `true` if `t` is not less than `u`, `false` otherwise.
      ///
      template<class T, StrictTotallyOrderedWith<T> U>
      constexpr bool operator()(T&& t, U&& u) const
      CJDB_NOEXCEPT_RETURN(
         not less{}(std::forward<T>(t), std::forward<U>(u))
      )

      using is_transparent = true_type;
   };
} // namespace cjdb::ranges

#include "cjdb/detail/undef.hpp"

#endif // CJDB_DETAIL_FUNCTIONAL_RANGECMP_GREATER_EQUAL_HPP
