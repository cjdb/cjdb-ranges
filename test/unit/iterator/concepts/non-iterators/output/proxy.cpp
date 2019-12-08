// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/iterator/concepts/iterator.hpp"

struct dummy {};

struct iterator {
	using element_type = dummy;
	using iterator_concept = cjdb::contiguous_iterator_tag;

	dummy operator*() const;

	iterator& operator++();
	iterator operator++(int);

	iterator& operator--();
	iterator operator--(int);

	iterator& operator+=(int);
	iterator& operator-=(int);

	bool operator==(iterator) const;
	bool operator!=(iterator) const;
	bool operator<(iterator) const;
	bool operator>(iterator) const;
	bool operator<=(iterator) const;
	bool operator>=(iterator) const;

	dummy operator[](int) const;

	friend iterator operator+(iterator, int);
	friend iterator operator+(int, iterator);
	friend iterator operator-(iterator, int);
	friend int operator-(iterator, iterator);
};
static_assert(cjdb::input_or_output_iterator<iterator>);
static_assert(cjdb::input_iterator<iterator>);
static_assert(not cjdb::indirectly_writable<iterator, dummy>);
static_assert(not cjdb::output_iterator<iterator, dummy>);
static_assert(cjdb::forward_iterator<iterator>);
static_assert(cjdb::bidirectional_iterator<iterator>);
static_assert(cjdb::random_access_iterator<iterator>);
static_assert(not cjdb::contiguous_iterator<iterator>);

int main() {}
