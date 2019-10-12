// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/iterator/concepts/iterator.hpp"

struct dummy {};

struct iterator {
	using value_type = dummy;
	using difference_type = int;

	dummy& operator*() const;

	iterator& operator++();
	iterator operator++(int);

	iterator& operator--();
	iterator operator--(int);

	bool operator==(iterator) const;
	bool operator!=(iterator) const;
};
static_assert(cjdb::input_or_output_iterator<iterator>);
static_assert(cjdb::input_iterator<iterator>);
static_assert(cjdb::output_iterator<iterator, dummy>);
static_assert(cjdb::forward_iterator<iterator>);
static_assert(cjdb::bidirectional_iterator<iterator>);
static_assert(not cjdb::random_access_iterator<iterator>);
static_assert(not cjdb::contiguous_iterator<iterator>);

int main() {}
