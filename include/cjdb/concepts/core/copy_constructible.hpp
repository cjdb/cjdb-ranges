// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_CORE_COPYCONSTRUCTIBLE_HPP
#define CJDB_CONCEPTS_CORE_COPYCONSTRUCTIBLE_HPP

#include "cjdb/concepts/core/constructible_from.hpp"
#include "cjdb/concepts/core/move_constructible.hpp"

namespace cjdb {
	/// If `T` is an object type, then let `v` be an lvalue of type (possibly `const`) `T` or an
	/// rvalue of type `const T`. `copy_constructible<T>` is satisfied only if
	///    - After the definition `T u = v;`, `u` is equal to `v`.
	///    - `T(v)` is equal to `v`.
	/// \see [concepts.copyconstructible]
	///
	template<class T>
	concept copy_constructible =
		move_constructible<T> and
		constructible_from<T, T&> and
		convertible_to<T&, T> and
		constructible_from<T, T const&> and
		convertible_to<T const&, T> and
		constructible_from<T, T const> and
		convertible_to<T const, T>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_COPYCONSTRUCTIBLE_HPP
