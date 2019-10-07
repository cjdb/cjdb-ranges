// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_ITERATOR_REFERENCE_HPP
#define CJDB_DETAIL_ITERATOR_REFERENCE_HPP

namespace cjdb::detail_iterator_reference {
	template<typename T>
	using with_reference = T&;

	template<typename T>
	concept can_reference = requires {
		typename with_reference<T>;
	};

	template<typename T>
	concept dereferenceable = requires(T& t) {
		{ *t } -> can_reference; // not required to be equality-preserving
	};
} // namespace cjdb::detail_iterator_reference

#endif // CJDB_DETAIL_ITERATOR_REFERENCE_HPP
