// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_ITERATOR_CONCEPTS_ALGORITHM_INDIRECTLY_COPYABLE_HPP
#define CJDB_ITERATOR_CONCEPTS_ALGORITHM_INDIRECTLY_COPYABLE_HPP

#include "cjdb/detail/iterator/iter_move.hpp"
#include "cjdb/iterator/concepts/readable.hpp"
#include "cjdb/iterator/concepts/writable.hpp"

namespace cjdb {
	/// \brief The `indirectly_­copyable` concept specifies the relationship between a `readable` type
	///        and a `writable` type between which values may be copied.
	///
	template<typename In, typename Out>
	concept indirectly_copyable = readable<In> and writable<Out, iter_reference_t<In>>;
} // namespace cjdb

#endif // CJDB_ITERATOR_CONCEPTS_ALGORITHM_INDIRECTLY_COPYABLE_HPP
