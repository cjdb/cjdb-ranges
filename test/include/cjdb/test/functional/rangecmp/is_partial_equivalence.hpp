// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_PARTIAL_EQUIVALENCE_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_PARTIAL_EQUIVALENCE_HPP

#include "cjdb/test/functional/rangecmp/is_symmetric.hpp"
#include "cjdb/test/functional/rangecmp/is_transitive.hpp"

#define CHECK_IS_PARTIAL_EQUIVALENCE(r, a, b, c) \
	{                                             \
		CHECK_IS_SYMMETRIC(r, a, b);               \
		CHECK_IS_TRANSITIVE(r, a, b, c);           \
	}

#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_PARTIAL_EQUIVALENCE_HPP
