// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/detail/type_traits/maybe_const.hpp"

#include "cjdb/concepts/core/same_as.hpp"

using cjdb::detail_maybe_const::maybe_const_t;

static_assert(cjdb::same_as<maybe_const_t<false, int>, int>);
static_assert(cjdb::same_as<maybe_const_t<true, int>, int const>);

static_assert(cjdb::same_as<maybe_const_t<false, double*>, double*>);
static_assert(cjdb::same_as<maybe_const_t<true, double*>, double* const>);

int main() {}
