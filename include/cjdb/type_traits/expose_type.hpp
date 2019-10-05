// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TYPE_TRAITS_TYPE_HPP
#define CJDB_TYPE_TRAITS_TYPE_HPP

namespace cjdb {
   template <typename T>
   requires requires { typename T::type; }
   using _t = typename T::type;
} // namespace cjdb

#endif // CJDB_TYPE_TRAITS_TYPE_HPP
