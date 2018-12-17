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
#ifndef CJDB_DETAIL_FUNCTIONAL_RANGECMP_NOT_EQUAL_TO_HPP
#define CJDB_DETAIL_FUNCTIONAL_RANGECMP_NOT_EQUAL_TO_HPP

#include "cjdb/detail/concepts/comparison/equalitycomparable.hpp"
#include "cjdb/detail/functional/rangecmp/equal_to.hpp"
#include "cjdb/detail/type_traits/type_traits.hpp"
#include <utility>

namespace cjdb::ranges {
   /// \brief Function object for performing comparisons. Applies operator!=.
   ///
   struct not_equal_to {
      /// \returns `true` if `t` is not equal to `u`, `false` otherwise.
      ///
      template<class T, EqualityComparableWith<T> U>
      constexpr bool operator()(T&& t, U&& u) const
      CJDB_NOEXCEPT_RETURN(
         not equal_to{}(std::forward<T>(t), std::forward<U>(u))
      )

      using is_transparent = true_type;
   };

   /// \brief
   /// \note This is an extension.
   ///
   template<EqualityComparable T>
   using not_equal_to_unary = detail_equality_unary::equality_unary<T, not_equal_to>{};
} // namespace cjdb::ranges

#endif // CJDB_DETAIL_FUNCTIONAL_RANGECMP_NOT_EQUAL_TO_HPP
