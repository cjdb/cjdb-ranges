// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_TYPE_TRAITS_INJECT_CONST_HPP
#define CJDB_DETAIL_TYPE_TRAITS_INJECT_CONST_HPP

#include <type_traits>

namespace cjdb::detail_inject_const {
	template<typename T>
	struct inject_const : std::add_const<T> {};

	template<typename T>
	struct inject_const<T&> {
		using type = T const&;
	};

	template<typename T>
	struct inject_const<T&&> {
		using type = T const&&;
	};

	template<typename T>
	struct inject_const<T*> {
		using type = T const*;
	};

	template<typename T>
	using inject_const_t = typename inject_const<T>::type;
} // namespace cjdb::detail_inject_const

#endif // CJDB_DETAIL_TYPE_TRAITS_INJECT_CONST_HPP
