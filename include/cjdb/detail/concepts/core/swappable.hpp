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
#ifndef CJDB_DETAIL_CONCEPTS_CORE_SWAPPABLE_HPP
#define CJDB_DETAIL_CONCEPTS_CORE_SWAPPABLE_HPP

#include "cjdb/concepts/core/assignable.hpp"
#include "cjdb/concepts/core/commonreference.hpp"
#include "cjdb/concepts/core/moveconstructible.hpp"
#include "cjdb/concepts/core/same.hpp"
#include "cjdb/type_traits/type_traits.hpp"
#include <utility>

#include "cjdb/detail/define.hpp"

namespace cjdb::ranges::detail_swap {
   /// \note Deleted to inhibit ADL.
   /// \see [concept.swappable]/2.1
   ///
   template<class T> void swap(T&, T&) = delete;

   /// \note Deleted to inhibit ADL.
   ///
   template<class T, std::size_t N> void swap(T(&)[N], T(&)[N]) = delete;

   /// \brief Determines if a type has a swap function that can be found by ADL.
   ///
   template<class T1, class T2>
   constexpr auto is_customised = false;

   template<class T1, class T2>
   requires
      is_class_v<remove_cvref_t<T1>> and
      is_class_v<remove_cvref_t<T2>> and
      requires(T1&& t1, T2&& t2) {
         swap(static_cast<T1&&>(t1), static_cast<T2&&>(t2));
      }
   constexpr auto is_customised<T1, T2> = true;

   /// \brief Implementation for ranges::swap.
   /// \see [concept.swappable]
   ///
   class swap_fn {
      template<class T1, class T2>
      static constexpr T1 exachange(T1& t1, T2&& t2)
      noexcept(is_nothrow_move_constructible_v<T1> and is_nothrow_assignable_v<T1&, T2>)
      {
         auto temp = std::move(t1);
         t1 = static_cast<T2&&>(t2);
         return temp;
      }
   public:
      template<class T1, class T2>
      requires is_customised<T1, T2>
      constexpr void operator()(T1&& t1, T2&& t2) const
      CJDB_NOEXCEPT_RETURN(
         (void)swap(std::forward<T1>(t1), std::forward<T2>(t2))
      )

      template<class T1, class T2, std::size_t N>
      requires
         (not is_customised<T1(&)[N], T2(&)[N]>) and
         (extent_v<T1> == extent_v<T2>) and
         requires(T1(& t1)[N], T2(& t2)[N]) {
            std::declval<swap_fn const&>()(t1[0], t2[1]);
         }
      constexpr void operator()(T1(& t1)[N], T2(& t2)[N]) const
      noexcept(noexcept(std::declval<swap_fn const&>()(t1[0], t2[0])))
      {
         for (auto i = std::size_t{}; i < N; ++i) {
            (*this)(t1[i], t2[i]);
         }
      }

      template<class T>
      requires
         (not is_customised<T&, T&>) and
         MoveConstructible<T> and
         Assignable<T&, T>
      constexpr void operator()(T& x, T& y) const
      CJDB_NOEXCEPT_RETURN(
         (void)(y = swap_fn::exachange(x, std::move(y)))
      )
   };
} // namespace cjdb::ranges::detail_swap

#include "cjdb/detail/undef.hpp"

#endif // CJDB_DETAIL_CONCEPTS_CORE_SWAPPABLE_HPP
