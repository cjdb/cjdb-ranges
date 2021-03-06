// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_CORE_COMMON_REFERENCE_WITH_HPP
#define CJDB_CONCEPTS_CORE_COMMON_REFERENCE_WITH_HPP

#include "cjdb/concepts/core/convertible_to.hpp"
#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/type_traits/common_reference.hpp"

namespace cjdb {
	/// \brief For two types `T` and `U`, if `common_­reference_­t<T, U>` is well-formed and denotes a
	///        type `C` such that both `convertible_to<T, C>` and `convertible_to<U, C>` are satisfied,
	///        then `T` and `U` share a _common reference type_, `C`.
	///
	/// Let `C` be common_­reference_­t<T, U>. Let `t` be a function whose return type is `T`, and let
	/// `u` be a function whose return type is `U`. `common_reference_with<T, U>` is satisfied only if:
	///   - `C(t())` equals `C(t())` if and only if `t()` is an equality-preserving expression.
	///   - `C(u())` equals `C(u())` if and only if `u()` is an equality-preserving expression.
	///
	/// \note `C` could be the same as `T`, or `U`, or it could be a different type. `C` may be a
	///       reference type.
	/// \note Users can customize the behavior of `common_reference_with` by specializing the
	///       `basic_­common_­reference` class template.
	/// \see [concept.commonref]
	/// \see [concepts.equality]
	/// \see [meta.trans.other]
	///
	template<class T, class U>
	concept common_reference_with =
		same_as<common_reference_t<T, U>, common_reference_t<U, T>> and
		convertible_to<T, common_reference_t<T, U>> and
		convertible_to<U, common_reference_t<T, U>>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_COMMON_REFERENCE_WITH_HPP
