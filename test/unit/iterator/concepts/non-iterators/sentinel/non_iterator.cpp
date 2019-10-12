// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/iterator/concepts/iterator.hpp"

struct iterator {
	struct value_type {};
	using difference_type = int;

	iterator& operator++();
	iterator operator++(int);
};

struct sentinel {
	friend bool operator==(iterator, sentinel);
	friend bool operator==(sentinel, iterator);
	friend bool operator!=(iterator, sentinel);
	friend bool operator!=(sentinel, iterator);
};

static_assert(not cjdb::input_iterator<iterator>);
static_assert(not cjdb::sentinel_for<sentinel, iterator>);

int main() {}
