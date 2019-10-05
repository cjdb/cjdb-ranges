// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_CONCEPTS_CORE_IS_SAME_HPP
#define CJDB_DETAIL_CONCEPTS_CORE_IS_SAME_HPP

#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb::detail_same {
   /// \brief Concept equivalent of is_same_v to enable same_as<T, U> subsuming same_as<U, T> and vice
   ///        versa.
   ///
   template<class T, class U>
   concept is_same = is_same_v<T, U>;
} // namespace cjdb::detail_same

#endif // CJDB_DETAIL_CONCEPTS_CORE_IS_SAME_HPP
