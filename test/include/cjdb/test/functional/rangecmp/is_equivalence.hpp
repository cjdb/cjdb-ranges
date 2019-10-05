// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_EQUIVALENCE_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_EQUIVALENCE_HPP

#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/functional/rangecmp/is_partial_equivalence.hpp"
#include "cjdb/test/functional/rangecmp/is_reflexive.hpp"

#define CHECK_IS_EQUIVALENCE(r, a, b, c)        \
	{                                            \
		CHECK_IS_PARTIAL_EQUIVALENCE(r, a, b, c); \
		CHECK_IS_REFLEXIVE(r, a);                 \
	}

#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_EQUIVALENCE_HPP
