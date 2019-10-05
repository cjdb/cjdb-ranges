// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_FUNCTIONAL_INVOKE_HPP
#define CJDB_FUNCTIONAL_INVOKE_HPP

#include "cjdb/detail/functional/invoke.hpp"

namespace cjdb {
	/// \brief An entity used to call function-like entities generically.
	/// \note cjdb::invoke is a niebloid.
	/// \see [func.invoke]
	///
	constexpr inline auto invoke = detail_invoke::invoke_fn{};
} // namespace cjdb

#endif // CJDB_FUNCTIONAL_INVOKE_HPP
