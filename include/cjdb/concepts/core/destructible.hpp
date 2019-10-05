// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_CORE_DESTRUCTIBLE_HPP
#define CJDB_CONCEPTS_CORE_DESTRUCTIBLE_HPP

#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb {
	/// \brief The `destructible` concept specifies properties of all types, instances of which can
	///        be destroyed at the end of their lifetime, or reference types.
	/// \note Unlike the _Cpp17Destructible_ requirements, this concept forbids destructors
	///       that are potentially throwing, even if a particular invocation of the destructor does
	///       not actually throw.
	/// \see [concepts.destructible]
	/// \see Table 29
	///
	template<class T>
	concept destructible = is_nothrow_destructible_v<T>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_DESTRUCTIBLE_HPP
