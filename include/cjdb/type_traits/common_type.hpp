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
#ifndef CJDB_TYPE_TRAITS_COMMON_TYPE_HPP
#define CJDB_TYPE_TRAITS_COMMON_TYPE_HPP

#include "cjdb/type_traits/expose_type.hpp"
#include "cjdb/concepts/core/convertible_to.hpp"
#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/type_traits/type_traits.hpp"
#include <utility>

namespace cjdb {
   template<class... T>
   struct common_type {};

   template<class... T>
   using common_type_t = _t<common_type<T... >>;

   template<class T>
   struct common_type<T> : common_type<T, T>
   {};

   namespace detail_common_type {
      template<class A>
      using cref =
         add_lvalue_reference_t<
            const remove_reference_t<A>
         >;

      template<class From, class To>
      struct copycv {
         using type = To;
      };

      template<class From, class To>
      struct copycv<From const, To> : add_const<To> {};

      template<class From, class To>
      struct copycv<From volatile, To> : add_volatile<To> {};

      template<class From, class To>
      struct copycv<From const volatile, To> : add_cv<To> {};

      template<class From, class To>
      using copycv_t = _t<copycv<From, To>>;

      template<class X, class Y>
      using cond_res = decltype(false ? std::declval<X(&)()>()() : std::declval<Y(&)()>()());

      template<class, class>
      struct common_type4 : common_type<> {};

      template<class D1, class D2>
      requires requires {
         typename decay_t<cond_res<cref<D1>, cref<D2>>>;
      }
      struct common_type4<D1, D2> {
         using type = decay_t<cond_res<cref<D1>, cref<D2>>>;
      };

      template<class D1, class D2>
      struct common_type3 : common_type4<D1, D2> {};

      template<class D1, class D2>
      requires requires {
         typename decay_t<decltype(false ? std::declval<D1>() : std::declval<D2>())>;
      }
      struct common_type3<D1, D2> {
         using type = decay_t<decltype(false ? std::declval<D1>() : std::declval<D2>())>;
      };
   } // namespace detail_common_type

   template<class T1, class T2>
   struct common_type<T1, T2> : detail_common_type::common_type3<decay_t<T1>, decay_t<T2>> {};

   namespace detail_common_type {
      template<class, class>
      struct common_type2 : common_type<> {};
      template<class D1, class D2>
      requires requires {
         typename common_type_t<D1, D2>;
      }
      struct common_type2<D1, D2> : common_type<D1, D2> {};
   } // namespace detail_common_type

   template<class T1, class T2>
   requires
      (not same_as<T1, decay_t<T1>>) or
      (not same_as<T2, decay_t<T2>>)
   struct common_type<T1, T2> : detail_common_type::common_type2<decay_t<T1>, decay_t<T2>>
   {};

   namespace detail_common_type {
      template<class T1, class T2, class... R>
      struct common_type5 : common_type<> {};

      template<class T1, class T2, class... R>
      requires requires {
         typename common_type_t<T1, T2>;
         typename common_type_t<R...>;
      }
      struct common_type5<T1, T2, R...> : common_type<common_type_t<T1, T2>, common_type_t<R...>> {
      };
   } // detail_common_type

   template <typename T1, typename T2, typename... R>
   requires (sizeof...(R) > 0)
   struct common_type<T1, T2, R...> : detail_common_type::common_type5<T1, T2, R...> {};
} // namespace cjdb

#endif // CJDB_TYPE_TRAITS_COMMON_TYPE_HPP
