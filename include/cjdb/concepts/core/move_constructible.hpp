// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_CORE_MOVECONSTRUCTIBLE_HPP
#define CJDB_CONCEPTS_CORE_MOVECONSTRUCTIBLE_HPP

#include "cjdb/concepts/core/constructible_from.hpp"
#include "cjdb/concepts/core/convertible_to.hpp"

namespace cjdb {
	/// If `T` is an object type, then let `rv` be an rvalue of type `T` and `u2` a distinct object
	/// of type `T` equal to `rv`. `move_constructible<T>` is satisfied only if
	///    - After the definition `T u = rv;`, `u` is equal to `u2`.
	///    - `T(rv)` is equal to `u2`.
	///    - If `T` is not `const`, `rv`'s resulting state is valid but unspecified; otherwise, it is
	///      unchanged.
	/// \see [concepts.moveconstructible]
	/// \see [lib.types.movedfrom]
	///
	template<class T>
	concept move_constructible = constructible_from<T, T> and convertible_to<T, T>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_MOVECONSTRUCTIBLE_HPP
