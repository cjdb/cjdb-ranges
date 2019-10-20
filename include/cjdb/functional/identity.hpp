// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_FUNCTIONAL_IDENTITY_HPP
#define CJDB_FUNCTIONAL_IDENTITY_HPP

#include <functional>
#include <type_traits>

namespace cjdb {
	/// \brief Function object type that takes an object of any type and value category, and returns
	///        the object with the same value category.
	///
	/// This function object is useful for generic programming when wanting to establish a default
	/// operation.
	///
	struct identity {
		template<class T>
		constexpr T&& operator()(T&& t) const noexcept
		{ return std::forward<T>(t); }

		using is_transparent = std::true_type;
	};
} // namespace cjdb

#endif // CJDB_FUNCTIONAL_IDENTITY_HPP
