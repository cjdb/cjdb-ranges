// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_CORE_CONVERTIBLE_TO_HPP
#define CJDB_CONCEPTS_CORE_CONVERTIBLE_TO_HPP

#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb {
	/// \brief The `convertible_to` concept requires an expression of a particular type and value
	///        category to be both implicitly and explicitly convertible to some other type.
	///
	/// The implicit and explicit conversions are required to produce equal results.
	///
	/// Let `test` be the invented function:
	///
	/// ```cpp
	/// To test(From (&f)()) {
	///    return f();
	/// }
	/// ```
	/// and let `f` be a function with no arguments and return type `From` such that `f()` is
	/// equality-preserving.
	/// `convertible_to<From, To>` is satisfied only if:
	///     - `To` is not an object or reference-to-object type, or `static_­cast<To>(f())` is equal
	///       to `test(f)`.
	///     - `From` is not a reference-to-object type, or
	///        - If `From` is an rvalue reference to a non const-qualified type, the resulting state
	///          of the object referenced by `f()` after either above expression is valid but
	///          unspecified.
	///        - Otherwise, the object referred to by `f()` is not modified by either above
	///          expression.
	/// \see [concept.convertibleto]
	/// \see [lib.types.movedfrom]
	///
	template<class From, class To>
	concept convertible_to =
		is_convertible_v<From, To> and
		requires(From (&f)()) {
			static_cast<To>(f());
		};
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_CONVERTIBLE_TO_HPP
