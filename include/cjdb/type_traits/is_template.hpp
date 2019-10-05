// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TYPE_TRAITS_IS_TEMPLATE_HPP
#define CJDB_TYPE_TRAITS_IS_TEMPLATE_HPP

#include "cjdb/concepts/core/same_as.hpp"

namespace cjdb {
   template<template<class...> class Expected, class T>
   inline constexpr auto is_template_impl = false;

   template<template<class...> class Expected, template<class...> class Actual, class... Ts>
   requires same_as<Expected<Ts...>, Actual<Ts...>>
   inline constexpr auto is_template_impl<Expected, Actual<Ts...>> = true;

   template<template<class...> class Template, class T>
   inline constexpr auto is_template = is_template_impl<Template, T>;
} // namespace cjdb

#endif // CJDB_TYPE_TRAITS_IS_TEMPLATE_HPP
