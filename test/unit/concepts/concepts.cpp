// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/concepts.hpp"
#include "cjdb/random.hpp"

// Core
using cjdb::same_as;
using cjdb::derived_from;
using cjdb::convertible_to;
using cjdb::common_reference_with;
using cjdb::common_with;
using cjdb::integral;
using cjdb::signed_integral;
using cjdb::unsigned_integral;
using cjdb::floating_point;
using cjdb::assignable_from;
using cjdb::swappable;
using cjdb::swappable_with;
using cjdb::destructible;
using cjdb::constructible_from;
using cjdb::default_initializable;
using cjdb::move_constructible;
using cjdb::copy_constructible;

// Compare
using cjdb::equality_comparable;
using cjdb::equality_comparable_with;
using cjdb::totally_ordered;
using cjdb::totally_ordered_with;

// Object
using cjdb::movable;
using cjdb::copyable;
using cjdb::semiregular;
using cjdb::regular;

// Callable
using cjdb::invocable;
using cjdb::regular_invocable;
using cjdb::predicate;
using cjdb::relation;
using cjdb::strict_weak_order;

#if defined(__cpp_lib_three_way_comparison) and __cpp_lib_three_way_comparison >= 201907
#include "cjdb/compare.hpp"
// Comparison
using cjdb::three_way_comparable;
using cjdb::three_way_comparable_with;
#endif // __cpp_lib_three_way_comparison

// Random
using cjdb::uniform_random_bit_generator;

int main()
{}
