// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-.0 WITH LLVM-exception
//
#ifndef CJDB_RANGE_CONCEPTS_SIZED_RANGE_HPP
#define CJDB_RANGE_CONCEPTS_SIZED_RANGE_HPP

#include "cjdb/range/access/size.hpp"
#include "cjdb/range/concepts/range.hpp"
#include <type_traits>

namespace cjdb::ranges {
	/// \brief The `sized_range` concept specifies the requirements of a range type that knows its size
	///        in constant time with the `size` function.
	///
	/// \pre *Axiom*:
	///   Given an lvalue `t` of type `remove_­reference_­t<T>`, `T` models `sized_range` only if
	///      * `ranges​::​size(t)` is O(1), does not modify `t`, and is equal to `ranges​::​distance(t)`,
	///        and
	///      * if `iterator_t<T>` models forward_iterator`, `ranges​::​size(t)` is well-defined
	///        regardless of the evaluation of `ranges​::​begin(t)`.
	/// \note `ranges​::​size(t)` is otherwise not required to be well-defined after evaluating
	///       `ranges​::​begin(t)`. For example, `ranges​::​size(t)` might be well-defined for a
	///       `sized_range` whose iterator type does not model `forward_iterator` only if evaluated
	///       before the first call to `ranges​::​begin(t)`.
	/// \note The complexity requirement for the evaluation of `ranges​::​size` is non-amortized, unlike
	///       the case for the complexity of the evaluations of `ranges​::​begin` and `ranges​::​end` in
	///       the `range` concept.
	///
	template<typename T>
	concept sized_range = range<T> and requires(T& t) { ranges::size(t); };
} // namespace cjdb::ranges

#endif // CJDB_RANGE_CONCEPTS_SIZED_RANGE_HPP
