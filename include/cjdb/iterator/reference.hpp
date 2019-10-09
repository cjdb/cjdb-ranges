// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_ITERATOR_REFERENCE_HPP
#define CJDB_ITERATOR_REFERENCE_HPP

#include "cjdb/detail/iterator/reference.hpp"
#include "cjdb/detail/iterator/iter_move.hpp"
#include "cjdb/type_traits/type_traits.hpp"
#include <utility>

namespace cjdb {
	template<detail_iterator_reference::dereferenceable T>
	using iter_reference_t = decltype(*std::declval<T&>());

	template<typename T>
	requires detail_iter_move::iter_move_can_reference<T>
	using iter_rvalue_reference_t = decltype(ranges::iter_move(std::declval<T&>()));
} // namespace cjdb

#endif // CJDB_ITERATOR_REFERENCE_HPP
