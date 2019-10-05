// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_PARTIAL_ORDER_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_PARTIAL_ORDER_HPP

#include "cjdb/test/functional/rangecmp/is_antisymmetric.hpp"
#include "cjdb/test/functional/rangecmp/is_reflexive.hpp"
#include "cjdb/test/functional/rangecmp/is_transitive.hpp"

#define CHECK_IS_PARTIAL_ORDER(r, a, b, c) \
	{                                       \
		CHECK_IS_REFLEXIVE(r, a);            \
		CHECK_IS_ANTISYMMETRIC(r, a, b);     \
		CHECK_IS_TRANSITIVE(r, a, b, c);     \
	}

#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_PARTIAL_ORDER_HPP
