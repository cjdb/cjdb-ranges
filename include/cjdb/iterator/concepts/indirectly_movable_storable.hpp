// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_ITERATOR_CONCEPTS_ALGORITHM_INDIRECTLY_MOVABLE_STORABLE_HPP
#define CJDB_ITERATOR_CONCEPTS_ALGORITHM_INDIRECTLY_MOVABLE_STORABLE_HPP

#include "cjdb/concepts/core/assignable_from.hpp"
#include "cjdb/concepts/core/constructible_from.hpp"
#include "cjdb/concepts/object/movable.hpp"
#include "cjdb/detail/iterator/iter_move.hpp"
#include "cjdb/detail/iterator/indirectly_readable_traits.hpp"
#include "cjdb/iterator/concepts/indirectly_writable.hpp"
#include "cjdb/iterator/concepts/indirectly_movable.hpp"

namespace cjdb {
	/// \brief The `indirectly_­movable_­storable` concept augments `indirectly_­movable` with
	///        additional requirements enabling the transfer to be performed through an intermediate
	///        object of the `readable` type's value type.
	///
	/// \pre **Axiom:**
	/// Let `i` be a dereferenceable value of type `In`. `In` and `Out` model
	/// `indirectly_­movable_­storable<In, Out>` only if after the initialization of the object `obj`
	/// in
	/// ```cpp
	/// iter_value_t<In> obj(ranges::iter_move(i));
	/// ```
	/// `obj` is equal to the value previously denoted by `*i`. If `iter_­rvalue_­reference_­t<In>` is
	/// an rvalue reference type, the resulting state of the value denoted by `*i` is valid but
	/// unspecified ([lib.types.movedfrom]).
	///
	template<typename In, typename Out>
	concept indirectly_movable_storable =
		indirectly_movable<In, Out> and
		indirectly_writable<Out, iter_value_t<In>> and
		movable<iter_value_t<In>> and
		constructible_from<iter_value_t<In>, iter_rvalue_reference_t<In>> and
		assignable_from<iter_value_t<In>&, iter_rvalue_reference_t<In>>;
} // namespace cjdb

#endif // CJDB_ITERATOR_CONCEPTS_ALGORITHM_INDIRECTLY_MOVABLE_STORABLE_HPP
