// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/iterator/concepts/iterator.hpp"

struct iterator {
	struct value_type {};
	using difference_type = int;

	value_type& operator*() const;

	iterator& operator++();
	iterator operator++(int);
};

struct sentinel {
	friend bool operator==(iterator, sentinel);
	friend bool operator==(sentinel, iterator);
	friend bool operator!=(iterator, sentinel);
	friend bool operator!=(sentinel, iterator);

	friend iterator::difference_type operator-(sentinel, iterator);
	friend long operator-(iterator, sentinel);
};

static_assert(cjdb::input_iterator<iterator>);
static_assert(cjdb::sentinel_for<sentinel, iterator>);
static_assert(not cjdb::disable_sized_sentinel<sentinel, iterator>);
static_assert(not cjdb::sized_sentinel_for<sentinel, iterator>);

int main() {}
