// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-.0 WITH LLVM-exception
//
#ifndef CJDB_RANGE_CONCEPTS_RANGE_HPP
#define CJDB_RANGE_CONCEPTS_RANGE_HPP

namespace cjdb::ranges {
	/// \brief The range concept defines the requirements of a type that allows iteration over its
	///        elements by providing an iterator and sentinel that denote the elements of the range.
	///
	/// The required expressions `ranges::begin(t)` and `ranges::end(t)` of the range concept do not
	/// require implicit expression variations ([concepts.equality]).
	///
	/// \pre **Axiom:**
	///      Given an expression `t` such that `decltype((t))` is `T&`, `T` models `range` only if
	///         * `[ranges::begin(t), ranges::end(t))` denotes a range
	///           ([iterator.requirements.general]),
	///         * both `ranges::begin(t)` and `ranges::end(t)` are amortized constant time and
	///           non-modifying, and
	///         * if the type of `ranges::begin(t)` models `forward_­iterator`, `ranges::begin(t)` is
	///           equality-preserving.
	///
	/// \note Equality preservation of both `ranges::begin` and `ranges::end` enables passing a range
	///       whose iterator type models `forward_­iterator` to multiple algorithms and making multiple
	///       passes over the range by repeated calls to `ranges::begin` and `ranges::end`.
	///       Since `ranges::begin` is not required to be equality-preserving when the return type
	///       does not model `forward_­iterator`, repeated calls might not return equal values or might
	///       not be well-defined; `ranges::begin` should be called at most once for such a range.
	template<typename T>
	concept range =
		requires(T& t) {
			ranges::begin(t); // sometimes equality-preserving
			ranges::end(t);
		};
} // namespace cjdb::ranges

#endif // CJDB_RANGE_CONCEPTS_RANGE_HPP
