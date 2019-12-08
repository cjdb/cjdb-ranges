// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/iterator/concepts/indirectly_writable.hpp"

#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/test/iterator/read_write.hpp"

using cjdb::indirectly_writable;
using cjdb::same_as;

static_assert(indirectly_writable<int*, int>);
static_assert(indirectly_writable<int*, double>);
static_assert(indirectly_writable<int**, int*>);
static_assert(not indirectly_writable<int*, int*>);
static_assert(not indirectly_writable<int**, int>);

static_assert(indirectly_writable<cjdb_test::traditional_indirection, int>);
static_assert(indirectly_writable<cjdb_test::traditional_indirection, double>);
static_assert(not indirectly_writable<cjdb_test::traditional_indirection, double*>);

static_assert(not indirectly_writable<cjdb_test::read_only_indirection, int>);
static_assert(not indirectly_writable<cjdb_test::proxy_indirection, int>);

static_assert(not indirectly_writable<int, int>);
static_assert(not indirectly_writable<cjdb_test::missing_dereference, cjdb_test::missing_dereference::value_type>);

int main() {}
