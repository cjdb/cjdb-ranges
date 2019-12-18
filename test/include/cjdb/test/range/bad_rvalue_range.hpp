// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_BAD_RVALUE_RANGE_HPP
#define CJDB_TEST_BAD_RVALUE_RANGE_HPP

#include <vector>

namespace cjdb_test {
	/// \brief An object of type `bad_rvalue_range_members` should be an invalid parameter for all CPOs
	///        from [range.access].
	/// \note This type is used for negative testing against [range.access] CPOs.
	///
	template<bool defined = false, bool disabled = false>
	class bad_rvalue_range_members {
		using range_t = std::vector<int>;
	public:
		[[nodiscard]] range_t::iterator begin() &&;
		[[nodiscard]] range_t::const_iterator begin() const&&;

		[[nodiscard]] range_t::iterator end() &&;
		[[nodiscard]] range_t::const_iterator end() const&&;

		[[nodiscard]] range_t::iterator data() &&;
		[[nodiscard]] range_t::const_iterator data() const&&;
	};

	/// \brief An object of type `bad_rvalue_range_unqualified` should be an invalid parameter for all
	///        CPOs from [range.access].
	/// \note This type is used for negative testing against [range.access] CPOs.
	///
	class bad_rvalue_range_unqualified {
	public:
		constexpr friend void begin(bad_rvalue_range_unqualified&&) {}
		constexpr friend void begin(bad_rvalue_range_unqualified const&&) {}
		constexpr friend void end(bad_rvalue_range_unqualified&&) {}
		constexpr friend void end(bad_rvalue_range_unqualified const&&) {}
	};

	/// \brief An object of type `bad_rvalue_range_preferred` should be an invalid parameter for all
	///        CPOs from [range.access].
	/// \note This type is used for negative testing against [range.access] CPOs.
	///
	template<bool defined = false, bool disabled = false>
	class bad_rvalue_range_preferred {
	public:
		constexpr void begin() {}
		constexpr void begin() const {}
		constexpr void end() {}
		constexpr void end() const {}
		constexpr void data() {}
		constexpr void data() const {}

		constexpr friend void begin(bad_rvalue_range_preferred&&) {}
		constexpr friend void begin(bad_rvalue_range_preferred const&&) {}
		constexpr friend void end(bad_rvalue_range_preferred&&) {}
		constexpr friend void end(bad_rvalue_range_preferred const&&) {}
	};

	/// \brief An object of type `bad_rvalue_range_private_members` should be an invalid parameter for
	///        all CPOs from [range.access].
	/// \note This type is used for negative testing against [range.access] CPOs.
	///
	template<bool defined = false, bool disabled = false>
	class bad_rvalue_range_private_members {
	public:
		constexpr friend void begin(bad_rvalue_range_private_members&&) {}
		constexpr friend void begin(bad_rvalue_range_private_members const&&) {}
		constexpr friend void end(bad_rvalue_range_private_members&&) {}
		constexpr friend void end(bad_rvalue_range_private_members const&&) {}
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
