// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/functional/rangecmp/partial_equal_to.hpp"

#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/test/simple_test.hpp"
#include "partial_test.hpp"
#include <utility>


int main()
{
	auto ints = ::cjdb_test::generate_ints();
	using difference_type = decltype(ints)::difference_type;

	using cjdb::ranges::equal_to;
	using cjdb::ranges::partial_equal_to;

	cjdb_test::check_iterators_match(ints, partial_equal_to{-1}, equal_to{});
	cjdb_test::check_iterators_match(ints, partial_equal_to{ 0}, equal_to{});
	cjdb_test::check_iterators_match(ints, partial_equal_to{ 4}, equal_to{});
	// FIXME(cjdb): s/static_cast<difference_type>(std::size(ints))/cjdb::ranges::distance(ints)/
	auto const distance = static_cast<difference_type>(std::size(ints));
	cjdb_test::check_iterators_match(ints, partial_equal_to{distance - 1}, equal_to{});
	cjdb_test::check_iterators_match(ints, partial_equal_to{distance}, equal_to{});

	static_assert(not cjdb::same_as<decltype(partial_equal_to{ints}),
	                                decltype(partial_equal_to{std::vector<int>{}})>);
	static_assert(cjdb::same_as<decltype(partial_equal_to{ints}),
	                            decltype(partial_equal_to{std::as_const(ints)})>);

	return ::test_result();
}
