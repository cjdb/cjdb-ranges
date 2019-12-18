// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-.0 WITH LLVM-exception
//
#ifndef CJDB_RANGE_CONCEPTS_SAFE_RANGE_HPP
#define CJDB_RANGE_CONCEPTS_SAFE_RANGE_HPP

#include "cjdb/range/concepts/range.hpp"
#include <type_traits>

namespace cjdb::ranges {
	/// \brief Acts as the opt-in mechanism for `safe_range` when a range `R` is considered "safe" even
	///        when `R` might not be an lvalue reference.
	/// \note Pursuant to [namespace.std], users may specialize `enable_­safe_­range` for cv-unqualified
	///       program-defined types. Such specializations shall be usable in constant expressions
	///       ([expr.const]) and have type `const bool`.
	///
	template<typename>
	inline constexpr auto enable_safe_range = false;

	/// \brief Given an expression `E` such that `decltype((E))` is `T`, `T` models `safe_­range` only
	///        if the validity of iterators obtained from the object denoted by `E` is not tied to the
	///        lifetime of that object.
	///
	/// Each specialization `S` of class template `subrange` ([range.subrange]) models `safe_­range`
	/// because
	///    * `enable_­safe_­range<S>` is specialized to have the value `true`, and
	///    * `S`'s iterators do not have validity tied to the lifetime of an `S` object because they
	///       are “borrowed” from some other range.
	///
	/// \note Since the validity of iterators is not tied to the lifetime of an object whose type
	///       models `safe_­range`, a function can accept arguments of such a type by value and return
	///       iterators obtained from it without danger of dangling.
	///
	template<typename T>
	concept safe_range =
		range<T> and (std::is_lvalue_reference_v<T> or enable_safe_range<std::remove_cvref_t<T>>);
} // namespace cjdb::ranges

#endif // CJDB_RANGE_CONCEPTS_SAFE_RANGE_HPP
