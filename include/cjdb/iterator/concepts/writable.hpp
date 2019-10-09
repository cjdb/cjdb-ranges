// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_ITERATOR_CONCEPTS_WRITABLE_HPP
#define CJDB_ITERATOR_CONCEPTS_WRITABLE_HPP

#include "cjdb/concepts/core/common_reference_with.hpp"
#include "cjdb/detail/iterator/iterator_traits.hpp"
#include "cjdb/iterator/reference.hpp"

namespace cjdb {
	/// \brief The `writable` concept specifies the requirements for writing a value into an
	///        iterator's referenced object.
	///
	/// Let `E` be an an expression such that `decltype((E))` is `T`, and let `o` be a
	/// dereferenceable object of type `Out`. `Out` and `T` model `writable<Out, T>` only if:
	///
	///  * If `Out` and `T` model `readable<Out> and same_­as<iter_­value_­t<Out>, decay_­t<T>>`, then
	///    `*o` after any above assignment is equal to the value of `E` before the assignment.
	///
	/// After evaluating any above assignment expression, `o` is not required to be dereferenceable.
	///
	/// If `E` is an xvalue ([basic.lval]), the resulting state of the object it denotes is valid but
	/// unspecified ([lib.types.movedfrom]).
	///
	/// \note The only valid use of an `operator*` is on the left side of the assignment statement.
	///       Assignment through the same value of the writable type happens only once.
	/// \note `writable` has the awkward `const_­cast` expressions to reject iterators with prvalue
	///       non-proxy reference types that permit rvalue assignment but do not also permit const
	///       rvalue assignment. Consequently, an iterator type `I` that returns `std​::​string` by
	///       value does not model `writable<I, std​::​string>`.
	///
	template<class Out, class T>
	concept writable = requires(Out&& o, T&& t) {
		*o = std::forward<T>(t);                     // not required to be equality-preserving
		*std::forward<Out>(o) = std::forward<T>(t);  // not required to be equality-preserving
		const_cast<iter_reference_t<Out> const&&>(*o) = std::forward<T>(t);                    // not required to be equality-preserving
		const_cast<iter_reference_t<Out> const&&>(*std::forward<Out>(o)) = std::forward<T>(t); // not required to be equality-preserving
	};
} // namespace cjdb

#endif // CJDB_ITERATOR_CONCEPTS_WRITABLE_HPP
