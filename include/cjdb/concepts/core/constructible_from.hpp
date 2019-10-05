// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_CORE_CONSTRUCTIBLE_HPP
#define CJDB_CONCEPTS_CORE_CONSTRUCTIBLE_HPP

#include "cjdb/concepts/core/destructible.hpp"
#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb {
	/// \brief The `constructible_from` concept constrains the initialization of a variable of a given
	///        type with a particular set of argument types.
	/// \see [concepts.constructible]
	///
	template<class T, class... Args>
	concept constructible_from = destructible<T> and is_constructible_v<T, Args...>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_CONSTRUCTIBLE_HPP
