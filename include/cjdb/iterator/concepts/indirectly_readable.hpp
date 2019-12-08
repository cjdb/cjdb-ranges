// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_ITERATOR_CONCEPTS_INDIRECTLY_READABLE_HPP
#define CJDB_ITERATOR_CONCEPTS_INDIRECTLY_READABLE_HPP

#include "cjdb/detail/iterator/indirectly_readable.hpp"
#include <type_traits>

namespace cjdb {
	/// \brief Types that are indirectly readable by applying `operator*` model the
	///        `indirectly_­readable` concept, including pointers, smart pointers, and iterators.
	/// \pre **Axiom:**
	///      Given a value `i` of type `I`, `I` models `indirectly_­readable` only if the expression
	///      `*i` is equality-preserving.
	/// \note The expression `*i` is indirectly required to be valid via the exposition-only
	///       dereferenceable concept ([iterator.synopsis]).
	///
	template<typename In>
	concept indirectly_readable =
		detail_indirectly_readable::indirectly_readable_impl<std::remove_cvref_t<In>>;
} // namespace cjdb

#endif // CJDB_ITERATOR_CONCEPTS_INDIRECTLY_READABLE_HPP
