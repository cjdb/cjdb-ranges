// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/iterator/concepts/readable.hpp"

using cjdb::readable;
using cjdb::same_as;

struct traditional {
	using value_type = int;
	int& operator*() const;
};
static_assert(readable<traditional>);

struct alternative {
	using element_type = long;
	long& operator*() const;
};
static_assert(readable<alternative>);

struct proxy {
	using value_type = int;
	int operator*() const;
};
static_assert(readable<proxy>);

struct weird_dereference {
	using value_type = int;
	float& operator*() const;
};
static_assert(readable<weird_dereference>);

struct weird_iter_move {
	using value_type = int;
	int& operator*() const;

	friend float& iter_move(weird_iter_move&);
};
static_assert(same_as<decltype(cjdb::ranges::iter_move(std::declval<weird_iter_move&>())), float&>);
static_assert(readable<weird_iter_move>);

struct weird_dereference_iter_move {
	using value_type = int;
	float& operator*() const;

	friend unsigned long long& iter_move(weird_dereference_iter_move&);
};
static_assert(same_as<decltype(cjdb::ranges::iter_move(std::declval<weird_dereference_iter_move&>())),
                      unsigned long long&>);
static_assert(readable<weird_dereference_iter_move>);

struct missing_dereference {
	using value_type = int;
};
static_assert(not readable<missing_dereference>);

struct missing_readable_trait {
	int& operator*() const;
};
static_assert(not readable<missing_readable_trait>);

struct bad_dereference {
	using value_type = int;
	int* operator*() const;
};
static_assert(not readable<bad_dereference>);

struct bad_iter_move {
	using value_type = int;
	value_type& operator*() const;

	friend int* iter_move(bad_iter_move&);
};
static_assert(same_as<decltype(cjdb::ranges::iter_move(std::declval<bad_iter_move&>())), int*>);
static_assert(not readable<bad_iter_move>);

int main() {}
