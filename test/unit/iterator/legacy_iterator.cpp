// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/detail/iterator/legacy_iterator.hpp"

#include "cjdb/detail/iterator/incrementable_traits.hpp"
#include "cjdb/detail/iterator/indirectly_readable_traits.hpp"

#include <array>
#include <deque>
#include <forward_list>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template<typename T>
void check_legacy_iterator()
{
	using cjdb::detail_iterator_associated_types::legacy_iterator;
	static_assert(legacy_iterator<T>);

	using cjdb::detail_iterator_associated_types::legacy_input_iterator;
	static_assert(not legacy_input_iterator<T>);
}

template<typename T>
void check_legacy_input_iterator()
{
	using cjdb::detail_iterator_associated_types::legacy_iterator;
	static_assert(legacy_iterator<T>);

	using cjdb::detail_iterator_associated_types::legacy_input_iterator;
	static_assert(legacy_input_iterator<T>);
}

template<typename T>
void check_legacy_forward_iterator()
{
	using cjdb::detail_iterator_associated_types::legacy_iterator;
	static_assert(legacy_iterator<T>);

	using cjdb::detail_iterator_associated_types::legacy_input_iterator;
	static_assert(legacy_input_iterator<T>);

	using cjdb::detail_iterator_associated_types::legacy_forward_iterator;
	static_assert(legacy_forward_iterator<T>);

	using cjdb::detail_iterator_associated_types::legacy_bidirectional_iterator;
	static_assert(not legacy_bidirectional_iterator<T>);
}

template<typename T>
void check_legacy_bidirectional_iterator()
{
	using cjdb::detail_iterator_associated_types::legacy_iterator;
	static_assert(legacy_iterator<T>);

	using cjdb::detail_iterator_associated_types::legacy_input_iterator;
	static_assert(legacy_input_iterator<T>);

	using cjdb::detail_iterator_associated_types::legacy_forward_iterator;
	static_assert(legacy_forward_iterator<T>);

	using cjdb::detail_iterator_associated_types::legacy_bidirectional_iterator;
	static_assert(legacy_bidirectional_iterator<T>);

	using cjdb::detail_iterator_associated_types::legacy_random_access_iterator;
	static_assert(not legacy_random_access_iterator<T>);
}

template<typename T>
void check_legacy_random_access_iterator()
{
	using cjdb::detail_iterator_associated_types::legacy_iterator;
	static_assert(legacy_iterator<T>);

	using cjdb::detail_iterator_associated_types::legacy_input_iterator;
	static_assert(legacy_input_iterator<T>);

	using cjdb::detail_iterator_associated_types::legacy_forward_iterator;
	static_assert(legacy_forward_iterator<T>);

	using cjdb::detail_iterator_associated_types::legacy_bidirectional_iterator;
	static_assert(legacy_bidirectional_iterator<T>);

	using cjdb::detail_iterator_associated_types::legacy_random_access_iterator;
	static_assert(legacy_random_access_iterator<T>);
}

int main()
{
	check_legacy_iterator<std::ostream_iterator<int>>();
	check_legacy_iterator<std::ostream_iterator<double>>();
	check_legacy_iterator<std::back_insert_iterator<std::vector<long>>>();
	check_legacy_iterator<std::back_insert_iterator<std::list<std::vector<int>>>>();
	check_legacy_iterator<std::front_insert_iterator<std::deque<long>>>();
	check_legacy_iterator<std::front_insert_iterator<std::list<std::vector<int>>>>();

	check_legacy_input_iterator<std::istream_iterator<int>>();
	check_legacy_input_iterator<std::istream_iterator<long>>();

	check_legacy_forward_iterator<std::forward_list<std::vector<std::map<int, int>>>::iterator>();
	check_legacy_forward_iterator<std::forward_list<std::vector<std::map<int, int>>>::const_iterator>();
	check_legacy_forward_iterator<std::unordered_set<int>::iterator>();
	check_legacy_forward_iterator<std::unordered_set<int>::const_iterator>();
	check_legacy_forward_iterator<std::unordered_multiset<int>::iterator>();
	check_legacy_forward_iterator<std::unordered_multiset<int>::const_iterator>();
	check_legacy_forward_iterator<std::unordered_map<double, int>::iterator>();
	check_legacy_forward_iterator<std::unordered_map<double, int>::const_iterator>();
	check_legacy_forward_iterator<std::unordered_multimap<double, long long>::iterator>();
	check_legacy_forward_iterator<std::unordered_multimap<double, long long>::const_iterator>();

	check_legacy_bidirectional_iterator<std::list<int>::iterator>();
	check_legacy_bidirectional_iterator<std::list<int>::const_iterator>();
	check_legacy_bidirectional_iterator<std::list<int>::reverse_iterator>();
	check_legacy_bidirectional_iterator<std::list<int>::const_reverse_iterator>();
	check_legacy_bidirectional_iterator<std::set<double>::iterator>();
	check_legacy_bidirectional_iterator<std::set<double>::const_iterator>();
	check_legacy_bidirectional_iterator<std::set<double>::reverse_iterator>();
	check_legacy_bidirectional_iterator<std::set<double>::const_reverse_iterator>();
	check_legacy_bidirectional_iterator<std::multiset<char>::iterator>();
	check_legacy_bidirectional_iterator<std::multiset<char>::const_iterator>();
	check_legacy_bidirectional_iterator<std::multiset<char>::reverse_iterator>();
	check_legacy_bidirectional_iterator<std::multiset<char>::const_reverse_iterator>();
	check_legacy_bidirectional_iterator<std::map<int, double>::iterator>();
	check_legacy_bidirectional_iterator<std::map<int, double>::const_iterator>();
	check_legacy_bidirectional_iterator<std::map<int, double>::reverse_iterator>();
	check_legacy_bidirectional_iterator<std::map<int, double>::const_reverse_iterator>();
	check_legacy_bidirectional_iterator<std::multimap<char, signed char>::iterator>();
	check_legacy_bidirectional_iterator<std::multimap<char, signed char>::const_iterator>();
	check_legacy_bidirectional_iterator<std::multimap<char, signed char>::reverse_iterator>();
	check_legacy_bidirectional_iterator<std::multimap<char, signed char>::const_reverse_iterator>();

	check_legacy_random_access_iterator<std::vector<int>::iterator>();
	check_legacy_random_access_iterator<std::vector<int>::const_iterator>();
	check_legacy_random_access_iterator<std::vector<int>::reverse_iterator>();
	check_legacy_random_access_iterator<std::vector<int>::const_reverse_iterator>();
	check_legacy_random_access_iterator<std::array<short, 1>::iterator>();
	check_legacy_random_access_iterator<std::array<short, 1>::const_iterator>();
	check_legacy_random_access_iterator<std::array<short, 1>::reverse_iterator>();
	check_legacy_random_access_iterator<std::array<short, 1>::const_reverse_iterator>();

	struct dummy {};
	constexpr auto arbitrary_size = 23;
	check_legacy_random_access_iterator<std::array<dummy, arbitrary_size>::iterator>();
	check_legacy_random_access_iterator<std::array<dummy, arbitrary_size>::const_iterator>();
	check_legacy_random_access_iterator<std::array<dummy, arbitrary_size>::reverse_iterator>();
	check_legacy_random_access_iterator<std::array<dummy, arbitrary_size>::const_reverse_iterator>();

	check_legacy_random_access_iterator<std::deque<int>::iterator>();
	check_legacy_random_access_iterator<std::deque<int>::const_iterator>();
	check_legacy_random_access_iterator<std::deque<int>::reverse_iterator>();
	check_legacy_random_access_iterator<std::deque<int>::const_reverse_iterator>();
}
