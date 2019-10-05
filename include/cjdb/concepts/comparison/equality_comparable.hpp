// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_COMPARISON_EQUALITYCOMPARABLE_HPP
#define CJDB_CONCEPTS_COMPARISON_EQUALITYCOMPARABLE_HPP

#include "cjdb/concepts/core/common_reference_with.hpp"
#include "cjdb/detail/concepts/core/equality_comparable.hpp"

namespace cjdb {
	template<class T>
	concept equality_comparable =
		detail_weakly_equality_comparable::weakly_equality_comparable_with<T, T>;

	template<class T, class U>
	concept equality_comparable_with =
		equality_comparable<T> and
		equality_comparable<U> and
		common_reference_with<remove_reference_t<T> const&, remove_reference_t<U> const&> and
		equality_comparable<common_reference_t<remove_reference_t<T> const&, remove_reference_t<U> const&>> and
		detail_weakly_equality_comparable::weakly_equality_comparable_with<T, U>;
		// axiom(remove_reference_t<T> const t, remove_reference_t<U> const u) {
		//    using C = common_reference_t<remove_reference_t<T> const&, remove_reference_t<U> const&>;
		//    bool(t == u) == bool(C(t) == C(u));
		// }
} // namespace cjdb

#endif // CJDB_CONCEPTS_COMPARISON_EQUALITYCOMPARABLE_HPP
