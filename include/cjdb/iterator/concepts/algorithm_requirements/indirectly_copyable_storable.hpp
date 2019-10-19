// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_ITERATOR_CONCEPTS_ALGORITHM_INDIRECTLY_COPYABLE_STORABLE_HPP
#define CJDB_ITERATOR_CONCEPTS_ALGORITHM_INDIRECTLY_COPYABLE_STORABLE_HPP

#include "cjdb/concepts/core/assignable_from.hpp"
#include "cjdb/concepts/core/constructible_from.hpp"
#include "cjdb/concepts/object/copyable.hpp"
#include "cjdb/detail/iterator/iter_move.hpp"
#include "cjdb/detail/iterator/readable_traits.hpp"
#include "cjdb/iterator/concepts/writable.hpp"
#include "cjdb/iterator/reference.hpp"

namespace cjdb {
	/// \brief The `indirectly_­copyable_­storable` concept augments `indirectly_­copyable` with
	///        additional requirements enabling the transfer to be performed through an intermediate
	///        object of the `readable` type's value type.
	///
	/// It also requires the capability to make copies of values.
	/// \pre **Axiom:**
	/// Let `i` be a dereferenceable value of type `In`. `In` and `Out` model
	/// `indirectly_­copyable_­storable<In, Out>` only if after the initialization of the object `obj`
	/// in
	/// ```cpp
	/// iter_value_t<In> obj(*i);
	/// ```
	/// `obj` is equal to the value previously denoted by `*i`. If `iter_­reference_­t<In>` is an
	/// rvalue reference type, the resulting state of the value denoted by `*i` is valid but
	/// unspecified ([lib.types.movedfrom]).
	/// \note Algorithms in this library check the axioms using `CJDB_ASSERT` when the pre-conditions
	///       are satisfied. This will negatively impact debug performance, but may lead to improved
	///       performance in certain optimised builds.
	///
	template<typename In, typename Out>
	concept indirectly_copyable_storable =
		indirectly_copyable<In, Out> and
		writable<Out, const iter_value_t<In>&> and
		copyable<iter_value_t<In>> and
		constructible_from<iter_value_t<In>, iter_reference_t<In>> and
		assignable_from<iter_value_t<In>&, iter_reference_t<In>>;
} // namespace cjdb

#endif // CJDB_ITERATOR_CONCEPTS_ALGORITHM_INDIRECTLY_COPYABLE_STORABLE_HPP
