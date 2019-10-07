// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TYPE_TRATIS_IS_PRIMARY_HPP
#define CJDB_TYPE_TRATIS_IS_PRIMARY_HPP

#include "cjdb/concepts/core/derived_from.hpp"
#include "cjdb/detail/type_traits/primary_template.hpp"
#include "cjdb/type_traits/type_traits.hpp"
#include <utility>

namespace cjdb {
	template<typename T>
	inline constexpr auto is_primary =
		is_base_of_v<detail_primary_template::primary_template, T> and
		not derived_from<T, detail_primary_template::primary_template>;
} // namespace cjdb

#endif // CJDB_TYPE_TRATIS_IS_PRIMARY_HPP
