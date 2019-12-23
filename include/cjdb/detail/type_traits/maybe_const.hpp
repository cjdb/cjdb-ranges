// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_TYPE_TRAITS_MAYBE_CONST_HPP
#define CJDB_DETAIL_TYPE_TRAITS_MAYBE_CONST_HPP

#include "cjdb/type_traits/expose_type.hpp"
#include <type_traits>

namespace cjdb::detail_maybe_const {
	template<bool is_const, typename T>
	struct maybe_const : std::conditional<is_const, std::add_const_t<T>, T> {};

	template<bool is_const, typename T>
	using maybe_const_t = _t<maybe_const<is_const, T>>;
} // namespace cjdb::detail_maybe_const

#endif // CJDB_DETAIL_TYPE_TRAITS_MAYBE_CONST_HPP
