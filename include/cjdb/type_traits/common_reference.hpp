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
#ifndef CJDB_TYPE_TRAITS_COMMON_REFERENCE_HPP
#define CJDB_TYPE_TRAITS_COMMON_REFERENCE_HPP

#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/type_traits/common_type.hpp"
#include "cjdb/type_traits/expose_type.hpp"

namespace cjdb {
   template<class T1, class T2, template<class> class T1Qual, template<class> class T2Qual>
   struct basic_common_reference {};

   template<class...>
   struct common_reference {};

   template<class... T>
   using common_reference_t = _t<common_reference<T...>>;

   template<class T0>
   struct common_reference<T0> : common_reference<> {
      using type = T0;
   };

   namespace detail_common_type {
      template<class T1, class T2>
      struct common_reference5 : common_type<> {};

      template<class T1, class T2>
      requires requires {
         typename common_type_t<T1, T2>;
      }
      struct common_reference5<T1, T2> {
         using type = common_type_t<T1, T2>;
      };

      template<class T1, class T2>
      struct common_reference4 : common_reference5<T1, T2> {};

      template<class T1, class T2>
      requires requires {
         typename cond_res<T1, T2>;
      }
      struct common_reference4<T1, T2> : common_reference<> {
         using type = cond_res<T1, T2>;
      };

      template<class T1, class T2>
      struct common_reference3 : common_reference4<T1, T2> {};

      template<class A>
      struct xref {
         template<class U>
         using T = U;
      };

      template<class A>
      struct xref<A&> {
         template<class U>
         using T = std::add_lvalue_reference_t<typename xref<A>::template T<U>>;
      };

      template<class A>
      struct xref<A&&> {
         template<class U>
         using T = std::add_rvalue_reference_t<typename xref<A>::template T<U>>;
      };

      template<class A>
      struct xref<A const> {
         template<class U>
         using T = std::add_const_t<typename xref<A>::template T<U>>;
      };

      template<class A>
      struct xref<A volatile> {
         template<class U>
         using T = std::add_volatile_t<typename xref<A>::template T<U>>;
      };

      template<class A>
      struct xref<A const volatile> {
         template<class U>
         using T = std::add_cv_t<typename xref<A>::template T<U>>;
      };

      template<class T1, class T2>
      requires requires {
         typename basic_common_reference<
            remove_cvref_t<T1>,
            remove_cvref_t<T2>,
            xref<T1>::template T,
            xref<T2>::template T>::type;
      }
      struct common_reference3<T1, T2> {
         using type =
            typename basic_common_reference<
               remove_cvref_t<T1>,
               remove_cvref_t<T2>,
               xref<T1>::template T,
               xref<T2>::template T>::type;
      };

      template<class T1, class T2>
      struct common_reference2 : common_reference3<T1, T2> {};

      namespace common_ref {
         template<class A, class B,
            class X = std::remove_reference_t<A>,
            class Y = std::remove_reference_t<B>>
         struct common_ref {};
      }

      template<class A, class B>
      using common_ref_t = _t<common_ref::common_ref<A, B>>;

      namespace common_ref {
         template<class X, class Y>
         using kond_rez = cond_res<copycv_t<X, Y>&, copycv_t<Y, X>&>;

         template<class A, class B, class X, class Y>
         requires
            requires { typename kond_rez<X, Y>; } and
            std::is_reference_v<kond_rez<X, Y>>
         struct common_ref<A&, B&, X, Y> {
            using type = kond_rez<X, Y>;
         };

         template<class X, class Y>
         using C = std::add_rvalue_reference_t<std::remove_reference_t<common_ref_t<X&, Y&>>>;

         template<class A, class B, class X, class Y>
         requires
            requires { typename C<X, Y>; } and
            std::is_convertible_v<A, C<X, Y>> and
            std::is_convertible_v<B, C<X, Y>>
         struct common_ref<A&&, B&&, X, Y> {
            using type = C<X, Y>;
         };

         template<class X, class Y>
         using D = common_ref_t<X const&, Y&>;

         template<class A, class B, class X, class Y>
         requires
            requires { typename D<X, Y>; } and
            std::is_convertible_v<A, D<X, Y>>
         struct common_ref<A&&, B&, X, Y> {
            using type = D<X, Y>;
         };

         template<class A, class B, class X, class Y>
         struct common_ref<A&, B&&, X, Y> : common_ref<B&&, A&, X, Y> {};
      } // namespace common_ref

      template<class T1, class T2>
      requires requires {
         typename common_ref_t<T1, T2>;
      }
      struct common_reference2<T1, T2> {
         using type = common_ref_t<T1, T2>;
      };
   } // namespace detail_common_reference

   template<class T1, class T2>
   struct common_reference<T1, T2> : detail_common_type::common_reference2<T1, T2> {};

   template<class T1, class T2, class T3, class... Rest>
   struct common_reference<T1, T2, T3, Rest...>
      : common_reference<common_reference_t<T1, T2>, T3, Rest...> {};
} // namespace cjdb

#endif // CJDB_TYPE_TRAITS_COMMON_REFERENCE_HPP
