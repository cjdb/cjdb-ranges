// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_CONCEPTS_CORE_EQUALITY_COMPARABLE_HPP
#define CJDB_DETAIL_CONCEPTS_CORE_EQUALITY_COMPARABLE_HPP

#include "cjdb/concepts/core/convertible_to.hpp"
#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb::detail_weakly_equality_comparable {
   template<class T, class U>
   concept weakly_equality_comparable_with = // exposition only
      requires(remove_reference_t<T> const& t, remove_reference_t<U> const& u) {
         { t == u } -> convertible_to<bool>;
         { t != u } -> convertible_to<bool>;
         { u == t } -> convertible_to<bool>;
         { u != t } -> convertible_to<bool>;

         // axiom {
         //    domain(t == u) == domain(u == t);
         //    domain(t == u) == domain(t != u);
         //    domain(t != u) == domain(u != t);
         //
         //    bool(u == t) == bool(t == u);
         //    bool(t != u) == not bool(t == u);
         //    bool(u != t) == bool(t != u);
         // }
      };
} // namespace cjdb::detail_weakly_equality_comparable

#endif // CJDB_DETAIL_CONCEPTS_CORE_EQUALITY_COMPARABLE_HPP
