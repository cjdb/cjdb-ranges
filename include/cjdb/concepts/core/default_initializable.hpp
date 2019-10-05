// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_CORE_DEFAULTCONSTRUCTIBLE_HPP
#define CJDB_CONCEPTS_CORE_DEFAULTCONSTRUCTIBLE_HPP

#include "cjdb/concepts/core/constructible_from.hpp"

namespace cjdb {
	/// \see [concepts.defaultconstructible]
	///
	template<class T>
	concept default_initializable = constructible_from<T>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_DEFAULTCONSTRUCTIBLE_HPP
