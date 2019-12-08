// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// Checks that the names expected when one includes "cjdb/iterator.hpp" actually exist.
// Does not check for functionality.
//
#include "cjdb/iterator.hpp"

using cjdb::iterator_traits; // NOLINT(misc-unused-using-decls)

using cjdb::incrementable_traits; // NOLINT(misc-unused-using-decls)
using cjdb::iter_difference_t; // NOLINT(misc-unused-using-decls)

// NOLINTNEXTLINE(misc-unused-using-decls)
using cjdb::indirectly_readable_traits;
using cjdb::iter_value_t; // NOLINT(misc-unused-using-decls)

using cjdb::iter_reference_t; // NOLINT(misc-unused-using-decls)
using cjdb::iter_rvalue_reference_t; // NOLINT(misc-unused-using-decls)

// using cjdb::indirect_result_t;

using cjdb::ranges::iter_move; // NOLINT(misc-unused-using-decls)
// using cjdb::ranges::iter_swap;

using cjdb::indirectly_readable;
using cjdb::indirectly_writable;
using cjdb::weakly_incrementable;
using cjdb::incrementable;

using cjdb::input_or_output_iterator;
using cjdb::sentinel_for;
using cjdb::sized_sentinel_for;

using cjdb::input_iterator;
using cjdb::output_iterator;
using cjdb::forward_iterator;
using cjdb::bidirectional_iterator;
using cjdb::random_access_iterator;
using cjdb::contiguous_iterator;

// using cjdb::projected;

// using cjdb::indirectly_unary_invocable;
// using cjdb::indirectly_regular_unary_invocable;
// using cjdb::indirect_unary_predicate;
// using cjdb::indirect_relation;
// using cjdb::indirect_strict_weak_order;

// using cjdb::indirectly_­movable;
// using cjdb::indirectly_copyable;
// using cjdb::indirectly_swappable;
// using cjdb::comparable;
// using cjdb::permutable;
// using cjdb::mergeable;
// using cjdb::sortable;

// using cjdb::ranges::advance;
// using cjdb::ranges::distance;
// using cjdb::ranges::next;
// using cjdb::ranges::prev;

// using cjdb::reverse_iterator;

// using cjdb::back_insert_iterator;
// using cjdb::back_inserter;

// using cjdb::front_insert_iterator;
// using cjdb::front_inserter;

// using cjdb::insert_iterator;
// using cjdb::inserter;

// using cjdb::move_iterator;
// using cjdb::move_sentinel;

// using cjdb::common_iterator;

// using cjdb::default_sentinel_t;
// using cjdb::default_sentinel;

// using cjdb::counted_iterator;

// using cjdb::unreachable_sentinel_t;
// using cjdb::unreachable;

// using cjdb::istream_iterator;
// using cjdb::istreambuf_iterator;

// using cjdb::ostream_iterator;
// using cjdb::ostreambuf_iterator;

int main()
{}
