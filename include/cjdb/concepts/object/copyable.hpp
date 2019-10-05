// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_OBJECT_COPYABLE_HPP
#define CJDB_CONCEPTS_OBJECT_COPYABLE_HPP

#include "cjdb/concepts/core/assignable_from.hpp"
#include "cjdb/concepts/core/copy_constructible.hpp"
#include "cjdb/concepts/object/movable.hpp"

namespace cjdb {
	template<class T>
	concept copyable = copy_constructible<T> and movable<T> and assignable_from<T&, T const&>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_OBJECT_COPYABLE_HPP
