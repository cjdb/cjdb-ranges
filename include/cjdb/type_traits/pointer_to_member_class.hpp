// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TYPE_TRAITS_POINTER_TO_MEMBER_CLASS_HPP
#define CJDB_TYPE_TRAITS_POINTER_TO_MEMBER_CLASS_HPP

#include "cjdb/type_traits/expose_type.hpp"

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

#endif // CJDB_TYPE_TRAITS_POINTER_TO_MEMBER_CLASS_HPP
