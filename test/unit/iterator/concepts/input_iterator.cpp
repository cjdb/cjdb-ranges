// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/iterator/concepts/iterator.hpp"

#include "cjdb/concepts/comparison/equality_comparable.hpp"

struct dummy {};

struct iterator {
	using value_type = dummy;
	using difference_type = int;

	iterator() = default;
	iterator(iterator&&) = default;
	iterator& operator=(iterator&&) = default;

	dummy& operator*() const;

	iterator& operator++();
	void operator++(int);
};
static_assert(cjdb::input_or_output_iterator<iterator>);
static_assert(cjdb::input_iterator<iterator>);
static_assert(cjdb::indirectly_writable<iterator, dummy>);
static_assert(not cjdb::copyable<iterator>);
static_assert(not cjdb::equality_comparable<iterator>);
static_assert(not cjdb::sentinel_for<iterator, iterator>);
static_assert(not cjdb::output_iterator<iterator, dummy>);
static_assert(not cjdb::forward_iterator<iterator>);
static_assert(not cjdb::bidirectional_iterator<iterator>);
static_assert(not cjdb::random_access_iterator<iterator>);
static_assert(not cjdb::contiguous_iterator<iterator>);

int main() {}
