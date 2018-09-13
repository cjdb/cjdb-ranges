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
#ifndef CJDB_DETAIL_TYPE_TRAITS_POINTER_TO_MEMBER_CLASS_HPP
#define CJDB_DETAIL_TYPE_TRAITS_POINTER_TO_MEMBER_CLASS_HPP

#include "cjdb/detail/type_traits/expose_type.hpp"

namespace cjdb {
   template<class T>
   struct pointer_to_member_class {};

   template<class T, class Class>
   struct pointer_to_member_class<T(Class::*)> {
      using type = Class;
   };

   template<class T>
   using pointer_to_member_class_t = _t<pointer_to_member_class<T>>;
} // namespace cjdb

#endif // CJDB_DETAIL_TYPE_TRAITS_POINTER_TO_MEMBER_CLASS_HPP
