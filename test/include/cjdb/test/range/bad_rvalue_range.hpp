// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_BAD_RVALUE_RANGE_HPP
#define CJDB_TEST_BAD_RVALUE_RANGE_HPP

#include <vector>

namespace cjdb_test {
	/// \note This type is used for negative testing against `ranges::begin` and `ranges::end`.
	///
	class bad_rvalue_range_members {
	public:
		[[nodiscard]] std::vector<int>::iterator begin() &&;
		[[nodiscard]] std::vector<int>::const_iterator begin() const&&;
		[[nodiscard]] std::vector<int>::iterator end() &&;
		[[nodiscard]] std::vector<int>::const_iterator end() const&&;
		[[nodiscard]] std::vector<int>::pointer data() &&;
		[[nodiscard]] std::vector<int>::const_pointer data() const&&;
	};

	/// \note This type is used for negative testing against `ranges::begin` and `ranges::end`.
	///
	class bad_rvalue_range_unqualified {
	public:
		[[nodiscard]] constexpr friend int begin(bad_rvalue_range_unqualified&&)
		{ return 0; }
		[[nodiscard]] constexpr friend int begin(bad_rvalue_range_unqualified const&&)
		{ return 0; }
		[[nodiscard]] constexpr friend int end(bad_rvalue_range_unqualified&&)
		{ return 0; }
		[[nodiscard]] constexpr friend int end(bad_rvalue_range_unqualified const&&)
		{ return 0; }
	};

	/// \brief An object of type `bad_rvalue_range_preferred` can be called with unqualified calls to
	///        `begin` and to `end`.
	///
	/// \note This type is used for negative testing against `ranges::begin` and `ranges::end`.
	///
	class bad_rvalue_range_preferred {
	public:
		[[nodiscard]] int begin();
		[[nodiscard]] int begin() const;
		[[nodiscard]] int end();
		[[nodiscard]] int end() const;
		[[nodiscard]] int data();
		[[nodiscard]] int data() const;

		[[nodiscard]] constexpr friend int begin(bad_rvalue_range_preferred&&)
		{ return 0; }
		[[nodiscard]] constexpr friend int begin(bad_rvalue_range_preferred const&&)
		{ return 0; }
		[[nodiscard]] constexpr friend int end(bad_rvalue_range_preferred&&)
		{ return 0; }
		[[nodiscard]] constexpr friend int end(bad_rvalue_range_preferred const&&)
		{ return 0; }
	};

	/// \brief An object of type `bad_rvalue_range_private_members` can be called with unqualified
	///        calls to `begin` and to `end`.
	///
	/// \note This type is used for negative testing against `ranges::begin` and `ranges::end`.
	///
	class bad_rvalue_range_private_members {
	public:
		[[nodiscard]] constexpr friend int begin(bad_rvalue_range_private_members&&)
		{ return 0; }
		[[nodiscard]] constexpr friend int begin(bad_rvalue_range_private_members const&&)
		{ return 0; }
		[[nodiscard]] constexpr friend int end(bad_rvalue_range_private_members&&)
		{ return 0; }
		[[nodiscard]] constexpr friend int end(bad_rvalue_range_private_members const&&)
		{ return 0; }
	private:
		[[nodiscard]] std::vector<int>::iterator begin();
		[[nodiscard]] std::vector<int>::const_iterator begin() const;
		[[nodiscard]] std::vector<int>::iterator end();
		[[nodiscard]] std::vector<int>::const_iterator end() const;
		[[nodiscard]] std::vector<int>::pointer data();
		[[nodiscard]] std::vector<int>::const_pointer data() const;
	};
} // namespace cjdb_test

#endif // CJDB_TEST_BAD_RVALUE_RANGE_HPP
