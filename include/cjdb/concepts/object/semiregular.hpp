// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_OBJECT_SEMIREGULAR_HPP
#define CJDB_CONCEPTS_OBJECT_SEMIREGULAR_HPP

#include "cjdb/concepts/core/default_initializable.hpp"
#include "cjdb/concepts/object/copyable.hpp"

namespace cjdb {
	template<class T>
	concept semiregular = copyable<T> and default_initializable<T>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_OBJECT_SEMIREGULAR_HPP
