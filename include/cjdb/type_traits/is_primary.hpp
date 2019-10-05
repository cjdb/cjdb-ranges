// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TYPE_TRATIS_IS_PRIMARY_HPP
#define CJDB_TYPE_TRATIS_IS_PRIMARY_HPP

#include "cjdb/concepts/core/same_as.hpp"
#include <utility>

namespace cjdb {
	template<class T>
	concept is_primary = requires {
		typename T::detail_primary;
		requires same_as<typename T::detail_primary, T>;
	};
} // namespace cjdb

#endif // CJDB_TYPE_TRATIS_IS_PRIMARY_HPP
