// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/detail/iterator/iter_traits.hpp"

#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/detail/iterator/incrementable_traits.hpp"
#include "cjdb/detail/iterator/indirectly_readable_traits.hpp"
#include "cjdb/detail/iterator/iterator_traits.hpp"
#include <iterator>

struct random_access_iter_concept {
	using value_type = int;
	using difference_type = int;

	int operator*() const;
	random_access_iter_concept& operator++();
	random_access_iter_concept operator++(int);
	random_access_iter_concept& operator--();
	random_access_iter_concept operator--(int);

	bool operator==(random_access_iter_concept) const;
	bool operator!=(random_access_iter_concept) const;
};

using cjdb::same_as;

static_assert(same_as<cjdb::iterator_traits<random_access_iter_concept>::iterator_category,
                      std::input_iterator_tag>);
static_assert(same_as<cjdb::ranges::detail_iter_traits::iter_concept_t<random_access_iter_concept>,
                      std::random_access_iterator_tag>);

struct bidirectional_iter_concept {
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = int;
	using difference_type = int;

	int operator*() const;
	bidirectional_iter_concept& operator++();
	bidirectional_iter_concept operator++(int);
	bidirectional_iter_concept& operator--();
	bidirectional_iter_concept operator--(int);

	bool operator==(bidirectional_iter_concept) const;
	bool operator!=(bidirectional_iter_concept) const;
};

static_assert(same_as<cjdb::iterator_traits<bidirectional_iter_concept>::iterator_category,
                      std::bidirectional_iterator_tag>);
static_assert(same_as<cjdb::ranges::detail_iter_traits::iter_concept_t<bidirectional_iter_concept>,
                      std::bidirectional_iterator_tag>);

static_assert(same_as<cjdb::ranges::detail_iter_traits::iter_concept_t<int*>,
                      cjdb::contiguous_iterator_tag>);

int main() {}
