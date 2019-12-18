// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_BAD_LVALUE_RANGE_HPP
#define CJDB_TEST_BAD_LVALUE_RANGE_HPP

#include <vector>

namespace cjdb_test {
	/// \brief An object of type `bad_lvalue_range` can be called with unqualified calls to `begin` and
	///        `end`..
	///
	/// \note This type is used for negative testing against `ranges::begin` `ranges::end`, and
	///       `ranges::data`.
	///
	class bad_lvalue_range_unqualified {
	public:
		constexpr friend void begin(bad_lvalue_range_unqualified&) {}
		constexpr friend void begin(bad_lvalue_range_unqualified const&) {}
		constexpr friend void end(bad_lvalue_range_unqualified&) {}
		constexpr friend void end(bad_lvalue_range_unqualified const&) {}
	};

	/// \brief An object of type `bad_lvalue_range_preferred` can be called with unqualified calls to
	///        `begin`, `end`, and `data`.
	///
	/// \note This type is used for negative testing against `ranges::begin` `ranges::end`, and
	///       `ranges::data`.
	///
	class bad_lvalue_range_preferred {
	public:
		constexpr void begin() {}
		constexpr void begin() const {}
		constexpr void end() {}
		constexpr void end() const {}
		constexpr void data() {}
		constexpr void data() const {}

		constexpr friend void begin(bad_lvalue_range_preferred&) {}
		constexpr friend void begin(bad_lvalue_range_preferred const&) {}
		constexpr friend void end(bad_lvalue_range_preferred&) {}
		constexpr friend void end(bad_lvalue_range_preferred const&) {}
	};

	/// \brief An object of type `bad_lvalue_range_private_members` can be called with unqualified
	///        calls to `begin`, `end`, and `data`.
	///
	/// \note This type is used for negative testing against `ranges::begin` `ranges::end`, and
	///       `ranges::data`.
	///
	class bad_lvalue_range_private_members {
	public:
		constexpr friend void begin(bad_lvalue_range_private_members&) {}
		constexpr friend void begin(bad_lvalue_range_private_members const&) {}
		constexpr friend void end(bad_lvalue_range_private_members&) {}
		constexpr friend void end(bad_lvalue_range_private_members const&) {}
	private:
		[[nodiscard]] std::vector<int>::iterator begin();
		[[nodiscard]] std::vector<int>::const_iterator begin() const;
		[[nodiscard]] std::vector<int>::iterator end();
		[[nodiscard]] std::vector<int>::const_iterator end() const;
		[[nodiscard]] std::vector<int>::pointer data();
		[[nodiscard]] std::vector<int>::const_pointer data() const;
	};
} // namespace cjdb_test

#endif // CJDB_TEST_BAD_LVALUE_RANGE_HPP
