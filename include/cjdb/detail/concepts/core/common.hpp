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
#ifndef CJDB_DETAIL_CONCEPTS_CORE_COMMON_HPP
#define CJDB_DETAIL_CONCEPTS_CORE_COMMON_HPP

#include "cjdb/detail/concepts/core/commonreference.hpp"
#include "cjdb/detail/concepts/core/convertibleto.hpp"
#include "cjdb/detail/concepts/core/same.hpp"
#include "cjdb/detail/type_traits/common_reference.hpp"

namespace cjdb {
   /// \brief If `T` and `U` can both be explicitly converted to some third type, `C`, then `T` and
   ///        `U` share a _common type_, `C`.
   ///
   /// Let `C` be `common_­type_­t<T, U>`. Let `t` be a function whose return type is `T`, and let `u`
   /// be a function whose return type is `U`. `Common<T, U>` is satisfied only if:
   ///   - `C(t())` equals `C(t())` if and only if `t()` is an equality-preserving expression.
   ///   - `C(u())` equals `C(u())` if and only if `u()` is an equality-preserving expression
   ///
   /// \note `C` could be the same as `T`, or `U`, or it could be a different type. `C` might not be
   ///       unique.
   /// \note Users can customize the behavior of `Common` by specializing the `common_­type` class
   ///       template.
   /// \see [concept.common]
   /// \see [concepts.equality]
   /// \see [meta.trans.other]
   ///
   template<class T, class U>
   concept Common =
      Same<common_type_t<T, U>, common_type_t<U, T>> and
      ConvertibleTo<T, common_type_t<T, U>> and
      ConvertibleTo<U, common_type_t<T, U>> and
      CommonReference<
         std::add_lvalue_reference_t<const T>,
         std::add_lvalue_reference_t<const U>> and
      CommonReference<
         std::add_lvalue_reference_t<common_type_t<T, U>>,
         common_reference_t<
            std::add_lvalue_reference_t<const T>,
            std::add_lvalue_reference_t<const U>>>;
} // namespace cjdb

#endif // CJDB_DETAIL_CONCEPTS_CORE_COMMON_HPP
