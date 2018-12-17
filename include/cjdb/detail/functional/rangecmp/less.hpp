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
#ifndef CJDB_DETAIL_FUNCTIONAL_RANGECMP_LESS_HPP
#define CJDB_DETAIL_FUNCTIONAL_RANGECMP_LESS_HPP

#include "cjdb/detail/concepts/comparison/strictotallyordered.hpp"
#include "cjdb/detail/type_traits/type_traits.hpp"
#include <utility>

namespace cjdb::ranges {
   /// \brief Function object for performing comparisons. Applies operator<.
   ///
   struct less {
      /// \returns `true` if `t` is less than `u`, `false` otherwise.
      ///
      template<class T, StrictTotallyOrderedWith<T> U>
      constexpr bool operator()(T&& t, U&& u) const
      CJDB_NOEXCEPT_RETURN(
         static_cast<bool>(std::forward<T>(t) < std::forward<U>(u))
      )

      using is_transparent = true_type;
   };

   namespace detail_inequality_unary {
      template<StrictTotallyOrdered T, class Op>
      class inequality_unary {
      public:
         explicit constexpr equality_unary(T const& value) noexcept
            : value_{std::addressof(value)}
         {}

         equality_unary(equality_unary&&) = default;
         equality_unary& operator=(equality_unary&&) = default;

         equality_unary(equality_unary const&) = delete;
         equality_unary& operator=(equality_unary const&) = delete;

         template<StrictTotallyOrderedWith<T> U>
         constexpr bool operator()(U&& other) const noexcept
         {
            return Op{}(*value_, std::forward<U>(other));
         }

         using is_transparent = true_type;
      private:
         T const* value_;
      };

      template<StrictTotallyOrdered T, class Op>
      class inequality_unary<T&&, Op> {
      public:
         explicit constexpr equality_unary(remove_reference_t<T> t)
            : value_(std::move(t))
         {}

         template<StrictTotallyOrderedWith<T> U>
         constexpr bool operator()(U&& other) const noexcept
         {
            return Op{}(std::move(value_), std::forward<U>(other));
         }

         using is_transparent = false_type;
      private:
         T value_;
      };
   } // namespace detail_inequality_unary

   /// \brief
   /// \note This is an extension.
   ///
   template<StrictTotallyOrdered T>
   using less_unary = detail_inequality_unary::inequality_unary<T, less>{};
} // namespace cjdb::ranges

#endif // CJDB_DETAIL_FUNCTIONAL_RANGECMP_LESS_HPP
