// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_OBJECT_MOVABLE_HPP
#define CJDB_CONCEPTS_OBJECT_MOVABLE_HPP

#include "cjdb/concepts/core/assignable_from.hpp"
#include "cjdb/concepts/core/move_constructible.hpp"
#include "cjdb/concepts/core/swappable.hpp"
#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb {
	template<class T>
	concept movable =
		is_object_v<T> and
		move_constructible<T> and
		assignable_from<T&, T> and
		swappable<T>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_OBJECT_MOVABLE_HPP
