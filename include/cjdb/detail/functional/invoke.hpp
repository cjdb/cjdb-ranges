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
#ifndef CJDB_DETAIL_FUNCTIONAL_INVOKE_HPP
#define CJDB_DETAIL_FUNCTIONAL_INVOKE_HPP

#include "cjdb/detail/type_traits/is_template.hpp"
#include "cjdb/detail/type_traits/pointer_to_member_class.hpp"
#include "cjdb/detail/type_traits/type_traits.hpp"
#include <utility>

namespace cjdb {
   namespace detail_invoke {
      /// \brief Implementation of [func.require], which specifies all of the rules for `invoke`.
      /// \see [func.require]
      ///
      struct invoke_fn {
         /// \brief `(t1.*f)(t2,..., tN)` when `f` is a pointer to a member function of a class `T`
         ///        and `is_base_of_v<T, remove_reference_t<decltype(t1)>>` is true.
         /// \see [func.require]/1.1
         ///
         template<class F, class T1, class... Args>
         requires
            is_member_function_pointer_v<F> and
            is_base_of_v<pointer_to_member_class_t<F>, remove_reference_t<T1>> and
            requires(F&& f, T1&& t1, Args&&... args) {
               (std::forward<T1>(t1).*std::forward<F>(f))(std::forward<Args>(args)...);
            }
         constexpr invoke_result_t<F, T1, Args...> operator()(F&& f, T1&& t1, Args&&... args) const
         noexcept(is_nothrow_invocable_v<F, T1, Args...>)
         {
            return (std::forward<T1>(t1).*std::forward<F>(f))(std::forward<Args>(args)...);
         }

         /// \brief `(t1.get().*f)(t2, ..., tN)` when `f` is a pointer to a member function of a
         ///        class `T` and `remove_cvref_t<decltype(t1)>` is a specialization of
         ///        `reference_wrapper`.
         /// \see [func.require]/1.2
         ///
         template<class F, class T1, class... Args>
         requires
            is_member_function_pointer_v<F> and
            is_template<std::reference_wrapper, remove_cvref_t<T1>> and
            requires(F&& f, T1&& t1, Args&&... args) {
               (std::forward<T1>(t1).get().*std::forward<F>(f))(std::forward<Args>(args)...);
            }
         constexpr invoke_result_t<F, T1, Args...> operator()(F&& f, T1&& t1, Args&&... args) const
         noexcept(is_nothrow_invocable_v<F, T1, Args...>)
         {
            return (std::forward<T1>(t1).get().*std::forward<F>(f))(std::forward<Args>(args)...);
         }

         /// \brief `((*t1).*f)(t2, ..., tN)` when `f` is a pointer to a member function of a class
         ///        `T` and `t1` does not satisfy the previous two items.
         /// \see [func.require]/3
         ///
         template<class F, class T1, class... Args>
         requires
            is_member_function_pointer_v<F> and
            requires(F&& f, T1&& t1, Args&&... args) {
               ((*std::forward<T1>(t1)).*std::forward<F>(f))(std::forward<Args>(args)...);
            }
         constexpr invoke_result_t<F, T1, Args...> operator()(F&& f, T1&& t1, Args&&... args) const
         noexcept(is_nothrow_invocable_v<F, T1, Args...>)
         {
            return ((*std::forward<T1>(t1)).*std::forward<F>(f))(std::forward<Args>(args)...);
         }

         /// \brief `t1.*f` when `N == 1` and `f` is a pointer to data member of a class `T` and
         ///        `is_base_of_v<T, remove_reference_t<decltype(t1)>>`is true.
         /// \see [func.require]/4
         ///
         template<class F, class T1>
         requires (
            is_member_object_pointer_v<F> and
            is_base_of_v<pointer_to_member_class_t<F>, remove_reference_t<T1>> and
            requires(F&& f, T1&& t1) {
               std::forward<T1>(t1).*f;
            }
         )
         constexpr invoke_result_t<F, T1> operator()(F&& f, T1&& t1) const
         noexcept(is_nothrow_invocable_v<F, T1>)
         {
            return std::forward<T1>(t1).*f;
         }

         /// \brief `t1.get().*f` when `N == 1` and `f` is a pointer to data member of a class `T`
         ///        and `remove_cvref_t<decltype(t1)>` is a specialization of `reference_wrapper`.
         /// \see [func.require]/5
         ///
         template<class F, class T1>
         requires
            is_member_function_pointer_v<F> and
            is_template<std::reference_wrapper, remove_cvref_t<T1>> and
            requires(F&& f, T1&& t1) {
               std::forward<T1>(t1).get().*f;
            }
         constexpr invoke_result_t<F, T1> operator()(F&& f, T1&& t1) const
         noexcept(is_nothrow_invocable_v<F, T1>)
         {
            return std::forward<T1>(t1).get().*f;
         }

         /// \brief `(*t1).*f` when `N == 1` and `f` is a pointer to data member of a class `T` and
         ///        `t1` does not satisfy the previous two items.
         /// \see [func.require]/6
         ///
         template<class F, class T1>
         requires
            is_member_object_pointer_v<F> and
            requires(F&& f, T1&& t1) {
               (*std::forward<T1>(t1)).*f;
            }
         constexpr invoke_result_t<F, T1> operator()(F&& f, T1&& t1) const
         noexcept(is_nothrow_invocable_v<F, T1>)
         {
            return (*std::forward<T1>(t1)).*f;
         }

         /// \brief `f(t1, t2, ..., tN)` in all other cases.
         /// \see [func.require]/7
         ///
         template<class F, class... Args>
         requires requires(F&& f, Args&&... args) {
            std::forward<F>(f)(std::forward<Args>(args)...);
         }
         constexpr invoke_result_t<F, Args...> operator()(F&& f, Args&&... args) const
         noexcept(is_nothrow_invocable_v<F, Args...>)
         {
            return std::forward<F>(f)(std::forward<Args>(args)...);
         }
      };
   } // namespace detail_invoke

   /// \brief An entity used to call function-like entities generically.
   /// \note cjdb::invoke is an ADL-immune function.
   /// \see [func.invoke]
   ///
   constexpr inline auto invoke = detail_invoke::invoke_fn{};
} // namespace cjdb

#endif // CJDB_DETAIL_FUNCTIONAL_INVOKE_HPP
