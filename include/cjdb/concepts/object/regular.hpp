// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_OBJECT_REGULAR_HPP
#define CJDB_CONCEPTS_OBJECT_REGULAR_HPP

#include "cjdb/concepts/comparison/equality_comparable.hpp"
#include "cjdb/concepts/object/semiregular.hpp"

namespace cjdb {
	template<class T>
	concept regular = semiregular<T> and equality_comparable<T>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_OBJECT_REGULAR_HPP
