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
#ifndef CJDB_TYPE_TRAITS_IS_TEMPLATE_HPP
#define CJDB_TYPE_TRAITS_IS_TEMPLATE_HPP

#include "cjdb/concepts/core/same_as.hpp"

namespace cjdb {
   template<template<class...> class Expected, class T>
   constexpr auto is_template_impl = false;

   template<template<class...> class Expected, template<class...> class Actual, class... Ts>
   requires same_as<Expected<Ts...>, Actual<Ts...>>
   constexpr auto is_template_impl<Expected, Actual<Ts...>> = true;

   template<template<class...> class Template, class T>
   constexpr auto is_template = is_template_impl<Template, T>;
} // namespace cjdb

#endif // CJDB_TYPE_TRAITS_IS_TEMPLATE_HPP
