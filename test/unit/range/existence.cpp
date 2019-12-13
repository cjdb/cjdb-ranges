// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// Checks that the names expected when one includes "cjdb/range.hpp" actually exist.
// Does not check for functionality.
//
#include "cjdb/range.hpp"

namespace ranges = cjdb::ranges;
// namespace views = cjdb::views;

using ranges::begin;   // NOLINT(misc-unused-using-decls)
using ranges::cbegin;  // NOLINT(misc-unused-using-decls)
// using ranges::rbegin;  // NOLINT(misc-unused-using-decls)
// using ranges::crbegin; // NOLINT(misc-unused-using-decls)

using ranges::end;      // NOLINT(misc-unused-using-decls)
using ranges::cend;     // NOLINT(misc-unused-using-decls)
// using ranges::rend;  // NOLINT(misc-unused-using-decls)
// using ranges::crend; // NOLINT(misc-unused-using-decls)

using ranges::data;  // NOLINT(misc-unused-using-decls)
using ranges::cdata; // NOLINT(misc-unused-using-decls)

// using ranges::size; // NOLINT(misc-unused-using-decls)

// using ranges::range;       // NOLINT(misc-unused-using-decls)

// using ranges::enable_safe_range; // NOLINT(misc-unused-using-decls)
// using ranges::safe_range;        // NOLINT(misc-unused-using-decls)

// using ranges::iterator_t;               // NOLINT(misc-unused-using-decls)
// using ranges::sentinel_t;               // NOLINT(misc-unused-using-decls)
// using ranges::range_difference_t;       // NOLINT(misc-unused-using-decls)
// using ranges::range_value_t;            // NOLINT(misc-unused-using-decls)
// using ranges::range_reference_t;        // NOLINT(misc-unused-using-decls)
// using ranges::range_rvalue_reference_t; // NOLINT(misc-unused-using-decls)

// using ranges::disable_sized_range; // NOLINT(misc-unused-using-decls)
// using ranges::sized_range;         // NOLINT(misc-unused-using-decls)

// using ranges::enable_view; // NOLINT(misc-unused-using-decls)
// using ranges::view_base;   // NOLINT(misc-unused-using-decls)
// using ranges::view;        // NOLINT(misc-unused-using-decls)

// using ranges::output_range;        // NOLINT(misc-unused-using-decls)
// using ranges::input_range;         // NOLINT(misc-unused-using-decls)
// using ranges::forward_range;       // NOLINT(misc-unused-using-decls)
// using ranges::bidirectional_range; // NOLINT(misc-unused-using-decls)
// using ranges::random_access_range; // NOLINT(misc-unused-using-decls)
// using ranges::contiguous_range;    // NOLINT(misc-unused-using-decls)
// using ranges::common_range;        // NOLINT(misc-unused-using-decls)
// using ranges::viewable_range;      // NOLINT(misc-unused-using-decls)

// using ranges::view_interface; // NOLINT(misc-unused-using-decls)

// using ranges::subrange_kind; // NOLINT(misc-unused-using-decls)
// using ranges::subrange;      // NOLINT(misc-unused-using-decls)

// using ranges::dangling;        // NOLINT(misc-unused-using-decls)
// using ranges::safe_iterator_t; // NOLINT(misc-unused-using-decls)
// using ranges::safe_subrange_t; // NOLINT(misc-unused-using-decls)

// using ranges::empty_view;   // NOLINT(misc-unused-using-decls)
// using ranges::views::empty; // NOLINT(misc-unused-using-decls)
// using views::empty;         // NOLINT(misc-unused-using-decls)

// using ranges::single_view;   // NOLINT(misc-unused-using-decls)
// using ranges::views::single; // NOLINT(misc-unused-using-decls)
// using views::single;         // NOLINT(misc-unused-using-decls)

// using ranges::iota_view;   // NOLINT(misc-unused-using-decls)
// using ranges::views::iota; // NOLINT(misc-unused-using-decls)
// using views::iota;         // NOLINT(misc-unused-using-decls)

// using ranges::basic_istream_view; // NOLINT(misc-unused-using-decls)
// using ranges::istream_view;       // NOLINT(misc-unused-using-decls)

// using ranges::all_view;   // NOLINT(misc-unused-using-decls)
// using ranges::views::all; // NOLINT(misc-unused-using-decls)
// using views::all;         // NOLINT(misc-unused-using-decls)

// using ranges::filter_view;   // NOLINT(misc-unused-using-decls)
// using ranges::views::filter; // NOLINT(misc-unused-using-decls)
// using views::filter;         // NOLINT(misc-unused-using-decls)

// using ranges::transform_view;   // NOLINT(misc-unused-using-decls)
// using ranges::views::transform; // NOLINT(misc-unused-using-decls)
// using views::transform;         // NOLINT(misc-unused-using-decls)

// using ranges::take_view;   // NOLINT(misc-unused-using-decls)
// using ranges::views::take; // NOLINT(misc-unused-using-decls)
// using views::take;         // NOLINT(misc-unused-using-decls)

// using ranges::take_while_view;   // NOLINT(misc-unused-using-decls)
// using ranges::views::take_while; // NOLINT(misc-unused-using-decls)
// using views::take_while;         // NOLINT(misc-unused-using-decls)

// using ranges::drop_view;   // NOLINT(misc-unused-using-decls)
// using ranges::views::drop; // NOLINT(misc-unused-using-decls)
// using views::drop;         // NOLINT(misc-unused-using-decls)

// using ranges::drop_while_view;   // NOLINT(misc-unused-using-decls)
// using ranges::views::drop_while; // NOLINT(misc-unused-using-decls)
// using views::drop_while;         // NOLINT(misc-unused-using-decls)

// using ranges::join_view;   // NOLINT(misc-unused-using-decls)
// using ranges::views::join; // NOLINT(misc-unused-using-decls)
// using views::join;         // NOLINT(misc-unused-using-decls)

// using ranges::split_view;   // NOLINT(misc-unused-using-decls)
// using ranges::views::split; // NOLINT(misc-unused-using-decls)
// using views::split;         // NOLINT(misc-unused-using-decls)

// using ranges::views::counted; // NOLINT(misc-unused-using-decls)
// using views::counted;         // NOLINT(misc-unused-using-decls)

// using ranges::common_view;   // NOLINT(misc-unused-using-decls)
// using ranges::views::common; // NOLINT(misc-unused-using-decls)
// using views::common;         // NOLINT(misc-unused-using-decls)

// using ranges::reverse_view;   // NOLINT(misc-unused-using-decls)
// using ranges::views::reverse; // NOLINT(misc-unused-using-decls)
// using views::reverse;         // NOLINT(misc-unused-using-decls)

// using ranges::elements_view;   // NOLINT(misc-unused-using-decls)
// using ranges::views::elements; // NOLINT(misc-unused-using-decls)
// using views::elements;         // NOLINT(misc-unused-using-decls)

// using ranges::views::keys; // NOLINT(misc-unused-using-decls)
// using views::keys;         // NOLINT(misc-unused-using-decls)

// using ranges::views::values; // NOLINT(misc-unused-using-decls)
// using views::values;         // NOLINT(misc-unused-using-decls)

int main()
{}
