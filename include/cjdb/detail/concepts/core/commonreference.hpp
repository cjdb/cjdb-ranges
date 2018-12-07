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
#ifndef CJDB_DETAIL_CONCEPTS_CORE_COMMONREFERENCE_HPP
#define CJDB_DETAIL_CONCEPTS_CORE_COMMONREFERENCE_HPP

#include "cjdb/detail/concepts/core/convertibleto.hpp"
#include "cjdb/detail/concepts/core/same.hpp"
#include "cjdb/detail/type_traits/common_reference.hpp"

namespace cjdb {
   /// \brief For two types `T` and `U`, if `common_­reference_­t<T, U>` is well-formed and denotes a
   ///        type `C` such that both `ConvertibleTo<T, C>` and `ConvertibleTo<U, C>` are satisfied,
   ///        then `T` and `U` share a _common reference type_, `C`.
   ///
   /// Let `C` be common_­reference_­t<T, U>. Let `t` be a function whose return type is `T`, and let
   /// `u` be a function whose return type is `U`. `CommonReference<T, U>` is satisfied only if:
   ///   - `C(t())` equals `C(t())` if and only if `t()` is an equality-preserving expression.
   ///   - `C(u())` equals `C(u())` if and only if `u()` is an equality-preserving expression.
   ///
   /// \note `C` could be the same as `T`, or `U`, or it could be a different type. `C` may be a
   ///       reference type.
   /// \note Users can customize the behavior of `CommonReference` by specializing the
   ///       `basic_­common_­reference` class template.
   /// \see [concept.commonref]
   /// \see [concepts.equality]
   /// \see [meta.trans.other]
   ///
   template<class T, class U>
   concept CommonReference =
      Same<common_reference_t<T, U>, common_reference_t<U, T>> and
      ConvertibleTo<T, common_reference_t<T, U>> and
      ConvertibleTo<U, common_reference_t<T, U>>;
} // namespace cjdb

#endif // CJDB_DETAIL_CONCEPTS_CORE_COMMONREFERENCE_HPP
