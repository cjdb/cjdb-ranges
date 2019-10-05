// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_STRICT_TOTAL_ORDER_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_STRICT_TOTAL_ORDER_HPP

#include "cjdb/test/functional/rangecmp/is_antisymmetric.hpp"
#include "cjdb/test/functional/rangecmp/is_connex.hpp"
#include "cjdb/test/functional/rangecmp/is_irreflexive.hpp"
#include "cjdb/test/functional/rangecmp/is_transitive.hpp"

#define CHECK_IS_STRICT_TOTAL_ORDER(r, a, b, c) {  \
	CHECK_IS_IRREFLEXIVE(r, a);                     \
	CHECK_IS_ANTISYMMETRIC(r, a, b);                \
	CHECK_IS_TRANSITIVE(r, a, b, c);                \
	CHECK_IS_CONNEX(r, a, b);                       \
}

#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_STRICT_TOTAL_ORDER_HPP
