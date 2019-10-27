// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_LVALUE_RANGE_HPP
#define CJDB_TEST_LVALUE_RANGE_HPP

#include <vector>

namespace cjdb_test {
	class lvalue_range_with_members {
	public:
		using value_type = std::vector<int>::value_type;
		using size_type = std::vector<int>::size_type;

		lvalue_range_with_members() = default;

		explicit lvalue_range_with_members(size_type const n, value_type const value) noexcept
		: data_(n, value)
		{}

		[[nodiscard]] auto begin() &
		{ return data_.begin(); }

		[[nodiscard]] auto begin() const& noexcept
		{ return data_.begin(); }

		[[nodiscard]] auto end() &
		{ return data_.end(); }

		[[nodiscard]] auto end() const& noexcept
		{ return data_.end(); }

		[[nodiscard]] auto const& data() const noexcept
		{ return data_; }
	private:
		std::vector<int> data_;
	};

	class lvalue_range_with_members_and_unqualified_friends : public lvalue_range_with_members {
	public:
		using lvalue_range_with_members::lvalue_range_with_members;

		[[nodiscard]] friend auto begin(lvalue_range_with_members_and_unqualified_friends& x) noexcept
		{ return x.begin(); }

		[[nodiscard]] friend auto begin(lvalue_range_with_members_and_unqualified_friends const& x)
		{ return x.begin(); }

		[[nodiscard]] friend auto end(lvalue_range_with_members_and_unqualified_friends& x) noexcept
		{ return x.end(); }

		[[nodiscard]] friend auto end(lvalue_range_with_members_and_unqualified_friends const& x)
		{ return x.end(); }
	};
} // namespace cjdb_test

#endif // CJDB_TEST_LVALUE_RANGE_HPP
