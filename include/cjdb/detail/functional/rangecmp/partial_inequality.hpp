// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_FUNCTIONAL_RANGECMP_PARTIAL_INEQUALITY_HPP
#define CJDB_FUNCTIONAL_RANGECMP_PARTIAL_INEQUALITY_HPP

#include "cjdb/concepts/comparison/totally_ordered.hpp"
#include "cjdb/type_traits/type_traits.hpp"
#include <utility>

namespace cjdb::detail_partial_inequality {
   /// \brief Abstraction of `partial_less` and friends.
   ///
   /// `partial_inequality` is a partial function: that is, we provide a one value now, and others
   /// when the function is invoked. In keeping up with the 'you don't pay for what you don't use'
   /// idiom employed by the C++ International Standard, `partial_inequality` only stores a value if
   /// it is constructed with an rvalue (this is to prevent issues with lifetime management).
   ///
   /// If `partial_inequality` is constructed using an lvalue, that lvalue is _referenced_ by the
   /// partial function. Users must be careful to ensure that use of the partial function does not
   /// exceed the lifetime of the original object.
   ///
   template<totally_ordered T, class Op>
   class partial_inequality : private detail_partial_storage::partial_function_storage<T> {
      using base = detail_partial_storage::partial_function_storage<T>;
   public:
      using base::base;
      using base::value;

      /// \breif Applies the inequality operation.
      /// \tparam U A type that is strict-totally-ordered with T.
      /// \param other The object to be compared with.
      /// \returns `invoke(Op{}, value(), other)`
      ///
      template<totally_ordered_with<T> U>
      constexpr bool operator()(U&& other) const noexcept
      {
         return invoke(Op{}, value(), std::forward<U>(other));
      }

      using is_transparent = bool_constant<is_lvalue_reference_v<T>>;
   };
} // namespace cjdb::detail_partial_inequality

#endif // CJDB_FUNCTIONAL_RANGECMP_PARTIAL_INEQUALITY_HPP
