// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_UNQUALIFIED_LVALUE_RANGE_HPP
#define CJDB_TEST_UNQUALIFIED_LVALUE_RANGE_HPP

#include <array>

namespace cjdb_test {
	class unqualified_lvalue_range {
		using range_t = std::array<int, 1'000>; // NOLINT(readability-magic-numbers)
	public:
		[[nodiscard]] constexpr friend auto begin(unqualified_lvalue_range& x)
		{
			return x.data_.begin();
		}

		[[nodiscard]] constexpr friend auto begin(unqualified_lvalue_range const& x) noexcept
		{
			return x.data_.begin();
		}

		[[nodiscard]] constexpr friend auto end(unqualified_lvalue_range& x)
		{
			return x.data_.end();
		}

		[[nodiscard]] constexpr friend auto end(unqualified_lvalue_range const& x) noexcept
		{
			return x.data_.end();
		}

		[[nodiscard]] constexpr friend range_t::pointer
		data(unqualified_lvalue_range&) noexcept
		{
			return nullptr;
		}

		[[nodiscard]] constexpr friend range_t::const_pointer
		data(unqualified_lvalue_range const&) noexcept
		{
			return nullptr;
		}

		range_t data_{}; // NOLINT(misc-non-private-member-variables-in-classes)
	};

	class unqualified_lvalue_range_preferred {
		using range_t = std::array<int, 1'000>; // NOLINT(readability-magic-numbers)
	public:
		[[nodiscard]] constexpr int begin() noexcept
		{ return data_.front(); }

		[[nodiscard]] constexpr int begin() const
		{ return data_.front(); }

		[[nodiscard]] constexpr int end() noexcept
		{ return data_.back(); }

		[[nodiscard]] constexpr int end() const
		{ return data_.back(); }

		constexpr void data() noexcept {}
		constexpr void data() const {}

		[[nodiscard]] constexpr friend auto begin(unqualified_lvalue_range_preferred& x)
		{ return x.data_.begin(); }

		[[nodiscard]] constexpr friend
		auto begin(unqualified_lvalue_range_preferred const& x) noexcept
		{ return x.data_.begin(); }

		[[nodiscard]] constexpr friend auto end(unqualified_lvalue_range_preferred& x)
		{ return x.data_.end(); }

		[[nodiscard]] constexpr friend auto end(unqualified_lvalue_range_preferred const& x) noexcept
		{ return x.data_.end(); }

		[[nodiscard]] constexpr friend range_t::pointer
		data(unqualified_lvalue_range_preferred&) noexcept
		{
			return nullptr;
		}

		[[nodiscard]] constexpr friend range_t::const_pointer
		data(unqualified_lvalue_range_preferred const&) noexcept
		{
			return nullptr;
		}

		range_t data_{}; // NOLINT(misc-non-private-member-variables-in-classes)
	};

	class unqualified_lvalue_range_private_members {
		using range_t = std::array<int, 1'000>; // NOLINT(readability-magic-numbers)
	public:
		[[nodiscard]] constexpr friend auto begin(unqualified_lvalue_range_private_members& x)
		{ return x.data_.begin(); }

		[[nodiscard]] constexpr friend
		auto begin(unqualified_lvalue_range_private_members const& x) noexcept
		{ return x.data_.begin(); }

		[[nodiscard]] constexpr friend auto end(unqualified_lvalue_range_private_members& x)
		{ return x.data_.end(); }

		[[nodiscard]] constexpr friend
		auto end(unqualified_lvalue_range_private_members const& x) noexcept
		{ return x.data_.end(); }

		[[nodiscard]] constexpr friend range_t::pointer
		data(unqualified_lvalue_range_private_members&) noexcept
		{
			return nullptr;
		}

		[[nodiscard]] constexpr friend range_t::const_pointer
		data(unqualified_lvalue_range_private_members const&) noexcept
		{
			return nullptr;
		}

		range_t data_{}; // NOLINT(misc-non-private-member-variables-in-classes)
	private:
		[[nodiscard]] constexpr auto begin() noexcept
		{ return data_.begin(); }

		[[nodiscard]] constexpr auto begin() const
		{ return data_.begin(); }

		[[nodiscard]] constexpr auto end() noexcept
		{ return data_.end(); }

		[[nodiscard]] constexpr auto end() const
		{ return data_.end(); }

		constexpr void data() noexcept {}
		constexpr void data() const {}
	};
} // namespace cjdb_test

#endif // CJDB_TEST_UNQUALIFIED_LVALUE_RANGE_HPP
