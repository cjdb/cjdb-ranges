// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_CONCEPTS_CORE_SWAPPABLE_HPP
#define CJDB_DETAIL_CONCEPTS_CORE_SWAPPABLE_HPP

#include "cjdb/concepts/core/assignable_from.hpp"
#include "cjdb/concepts/core/common_reference_with.hpp"
#include "cjdb/concepts/core/move_constructible.hpp"
#include "cjdb/concepts/core/same_as.hpp"
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
   template<class T, std::size_t N> void swap(T(&)[N], T(&)[N]) = delete; // NOLINT(modernize-avoid-c-arrays)

   /// \brief Determines if a type has a swap function that can be found by ADL.
   ///
   template<class T1, class T2>
   inline constexpr auto is_customised = false;

   template<class T1, class T2>
   requires
      is_class_v<remove_cvref_t<T1>> and
      is_class_v<remove_cvref_t<T2>> and
      requires(T1&& t1, T2&& t2) {
         swap(static_cast<T1&&>(t1), static_cast<T2&&>(t2));
      }
   inline constexpr auto is_customised<T1, T2> = true;

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
         (not is_customised<T1(&)[N], T2(&)[N]>) and // NOLINT(modernize-avoid-c-arrays)
         (extent_v<T1> == extent_v<T2>) and
         requires(T1(& t1)[N], T2(& t2)[N]) { // NOLINT(modernize-avoid-c-arrays)
            std::declval<swap_fn const&>()(t1[0], t2[1]);
         }
      constexpr void operator()(T1(& t1)[N], T2(& t2)[N]) const // NOLINT(modernize-avoid-c-arrays)
      noexcept(noexcept(std::declval<swap_fn const&>()(t1[0], t2[0])))
      {
         for (auto i = std::size_t{}; i < N; ++i) {
            (*this)(t1[i], t2[i]);
         }
      }

      template<class T>
      requires
         (not is_customised<T&, T&>) and
         move_constructible<T> and
         assignable_from<T&, T>
      constexpr void operator()(T& x, T& y) const
      CJDB_NOEXCEPT_RETURN(
         (void)(y = swap_fn::exachange(x, std::move(y)))
      )
   };
} // namespace cjdb::ranges::detail_swap

#include "cjdb/detail/undef.hpp"

#endif // CJDB_DETAIL_CONCEPTS_CORE_SWAPPABLE_HPP
