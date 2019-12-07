// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_ITERATOR_CONCEPTS_ALGORITHM_INDIRECTLY_MOVABLE_HPP
#define CJDB_ITERATOR_CONCEPTS_ALGORITHM_INDIRECTLY_MOVABLE_HPP

#include "cjdb/detail/iterator/iter_move.hpp"
#include "cjdb/iterator/concepts/indirectly_readable.hpp"
#include "cjdb/iterator/concepts/indirectly_writable.hpp"

namespace cjdb {
	/// \brief The `indirectly_­movable` concept specifies the relationship between a `readable` type
	///        and a `writable` type between which values may be moved.
	///
	template<typename In, typename Out>
	concept indirectly_movable =
		indirectly_readable<In> and indirectly_writable<Out, iter_rvalue_reference_t<In>>;
} // namespace cjdb

#endif // CJDB_ITERATOR_CONCEPTS_ALGORITHM_INDIRECTLY_MOVABLE_HPP
