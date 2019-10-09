// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/iterator/concepts/writable.hpp"

using cjdb::writable;
using cjdb::same_as;

static_assert(writable<int*, int>);
static_assert(writable<int*, double>);
static_assert(writable<int**, int*>);
static_assert(not writable<int*, int*>);
static_assert(not writable<int**, int>);

struct traditional {
	using value_type = int;
	value_type& operator*() const;
};
static_assert(writable<traditional, int>);
static_assert(writable<traditional, double>);
static_assert(not writable<traditional, double*>);

struct read_only {
	using value_type = int const;
	value_type& operator*() const;
};
static_assert(not writable<read_only, int>);

struct proxy {
	using value_type = int;
	value_type operator*() const;
};
static_assert(not writable<proxy, int>);

static_assert(not writable<int, int>);

int main() {}
