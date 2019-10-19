// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_UTILITY_SWAP_HPP
#define CJDB_DETAIL_UTILITY_SWAP_HPP

#include "cjdb/concepts/core/assignable_from.hpp"
#include "cjdb/concepts/core/common_reference_with.hpp"
#include "cjdb/concepts/core/move_constructible.hpp"
#include "cjdb/concepts/core/same_as.hpp"
#include <type_traits>
#include <utility>

#include "cjdb/detail/define.hpp"

namespace cjdb::ranges::detail_swap {
	/// \note Deleted to inhibit ADL.
	/// \see [concept.swappable]/2.1
	///
	template<class T>
	void swap(T&, T&) = delete;

	/// \note Deleted to inhibit ADL.
	///
	template<class T, std::size_t N>
	void swap(T(&)[N], T(&)[N]) = delete; // NOLINT(modernize-avoid-c-arrays)

	/// \brief Determines if a type has a swap function that can be found by ADL.
	///
	template<class T, class U>
	concept unqualified_swappable =
		std::is_class_v<std::remove_cvref_t<T>> and
		std::is_class_v<std::remove_cvref_t<U>> and
		requires(T&& t, U&& u) {
			swap(std::forward<T>(t), std::forward<U>(u));
		};

	class swap_fn;

	template<typename T, typename U, std::size_t N>
	concept swappable_arrays =
		not unqualified_swappable<T(&)[N], U(&)[N]> and // NOLINT(modernize-avoid-c-arrays)
		std::extent_v<T> == std::extent_v<U> and
		requires(T(& t)[N], U(& u)[N]) { // NOLINT(modernize-avoid-c-arrays)
			std::declval<swap_fn const&>()(t[0], u[1]);
		};

	template<typename T>
	concept exchangeable =
		not unqualified_swappable<T&, T&> and
		move_constructible<T> and
		assignable_from<T&, T>;

   /// \brief Implementation for ranges::swap.
   /// \see [concept.swappable]
   ///
   class swap_fn {
      template<class T, class U>
      static constexpr T exachange(T& t, U&& u)
      noexcept(is_nothrow_move_constructible_v<T> and is_nothrow_assignable_v<T&, U>)
      {
         auto temp = std::move(t);
         t = static_cast<U&&>(u);
         return temp;
      }
   public:
      template<class T, class U>
      requires unqualified_swappable<T, U>
      constexpr void operator()(T&& t, U&& u) const
      CJDB_NOEXCEPT_RETURN(
         (void)swap(std::forward<T>(t), std::forward<U>(u))
      )

      template<class T, class U, std::size_t N>
      requires swappable_arrays<T, U, N>
      constexpr void operator()(T(& t)[N], U(& u)[N]) const // NOLINT(modernize-avoid-c-arrays)
      noexcept(noexcept(std::declval<swap_fn const&>()(t[0], u[0])))
      {
         for (auto i = std::size_t{}; i < N; ++i) {
            (*this)(t[i], u[i]);
         }
      }

      template<exchangeable T>
      constexpr void operator()(T& x, T& y) const
      CJDB_NOEXCEPT_RETURN(
         (void)(y = swap_fn::exachange(x, std::move(y)))
      )
   };
} // namespace cjdb::ranges::detail_swap

#include "cjdb/detail/undef.hpp"

#endif // CJDB_DETAIL_UTILITY_SWAP_HPP
