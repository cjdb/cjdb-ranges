// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_ITERATOR_CONCEPTS_INCREMENTABLE_HPP
#define CJDB_ITERATOR_CONCEPTS_INCREMENTABLE_HPP

#include "cjdb/concepts/core/default_initializable.hpp"
#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/concepts/object/movable.hpp"
#include "cjdb/concepts/object/regular.hpp"
#include "cjdb/detail/iterator/incrementable_traits.hpp"
#include "cjdb/detail/iterator/integer_like.hpp"

namespace cjdb {
	/// \brief The `weakly_­incrementable` concept specifies the requirements on types that can be
	///        incremented with the pre- and post-increment operators. The increment operations are
	///        not required to be equality-preserving, nor is the type required to be
	///        `equality_­comparable`.
	///
	/// \pre **Axiom:**
	/// Let `i` be an object of type `I`. When `i` is in the domain of both pre- and post-increment,
	/// `i` is said to be _incrementable_. `I` models `weakly_­incrementable<I>` only if
	///    * The expressions `++i` and `i++` have the same domain.
	///    * If `i` is incrementable, then both `++i` and `i++` advance `i` to the next element.
	///    * If `i` is incrementable, then `std::addressof(++i)` is equal to `std::addressof(i)`.
	///
	/// \note This library currently dictates that `is_signed_integer_like` is equivalent to
	///       `signed_integral`.
	/// \note For `weakly_­incrementable` types, `a` equals `b` does not imply that `++a` equals
	///       `++b`. (Equality does not guarantee the substitution property or referential
	///       transparency.) Algorithms on weakly incrementable types should never attempt to pass
	///       through the same incrementable value twice. They should be single-pass algorithms.
	///       These algorithms can be used with istreams as the source of the input data through the
	///       `istream_­iterator` class template.
	///
	template<typename I>
	concept weakly_incrementable =
		default_initializable<I> and
		movable<I> and
		requires(I i) {
			typename iter_difference_t<I>;
			requires detail_integer_like::is_signed_integer_like<iter_difference_t<I>>;
			{ ++i } -> same_as<I&>;   // not required to be equality-preserving
			i++;                      // not required to be equality-preserving
		};

	/// \brief The incrementable concept specifies requirements on types that can be incremented with
	///        the pre- and post-increment operators. The increment operations are required to be
	///        equality-preserving, and the type is required to be `equality_­comparable`.
	/// \pre **Axiom:**
	/// Let `a` and `b` be incrementable objects of type `I`. `I` models incrementable only if
	///    * If `bool(a == b)` then `bool(a++ == b)`.
	///    * If `bool(a == b)` then `bool(((void)a++, a) == ++b)`.
	/// \note This supersedes the annotations on the increment expressions in the definition of
	///       `weakly_­incrementable`.
	/// \note Algorithms in this library check the axioms using `CJDB_ASSERT` when the pre-conditions
	///       are satisfied. This will negatively impact debug performance, but may lead to improved
	///       performance in certain optimised builds.
	///
	template<typename I>
	concept incrementable =
		regular<I> and
		weakly_incrementable<I> and
		requires(I i) {
			{ i++ } -> same_as<I>;
		};
} // namespace cjdb

#endif // CJDB_ITERATOR_CONCEPTS_INCREMENTABLE_HPP
