// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_UNQUALIFIED_RVALUE_RANGE_HPP
#define CJDB_TEST_UNQUALIFIED_RVALUE_RANGE_HPP

#include <array>

namespace cjdb_test {
	class unqualified_rvalue_range {
		using range_t = std::array<int, 1'000>; // NOLINT(readability-magic-numbers)
	public:
		[[nodiscard]] constexpr friend auto begin(unqualified_rvalue_range&& x)
		{
			return x.data_.begin();
		}

		[[nodiscard]] constexpr friend auto begin(unqualified_rvalue_range const&& x) noexcept
		{
			return std::move(x).data_.begin(); // NOLINT(performance-move-const-arg)
		}

		[[nodiscard]] constexpr friend auto end(unqualified_rvalue_range&& x)
		{
			return x.data_.end();
		}

		[[nodiscard]] constexpr friend auto end(unqualified_rvalue_range const&& x) noexcept
		{
			return std::move(x).data_.end(); // NOLINT(performance-move-const-arg)
		}

		[[nodiscard]] constexpr friend range_t::pointer data(unqualified_rvalue_range&&) noexcept
		{
			return nullptr;
		}

		[[nodiscard]] constexpr friend range_t::const_pointer data(unqualified_rvalue_range const&&)
		{
			return nullptr;
		}

		range_t data_{}; // NOLINT(,misc-non-private-member-variables-in-classes)
	};

	class unqualified_rvalue_range_preferred {
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

		[[nodiscard]] constexpr int data() noexcept;
		[[nodiscard]] constexpr int data() const;

		[[nodiscard]] constexpr friend auto begin(unqualified_rvalue_range_preferred&& x)
		{
			return std::move(x).data_.begin(); // NOLINT(performance-move-const-arg)
		}

		[[nodiscard]] constexpr friend
		auto begin(unqualified_rvalue_range_preferred const&& x) noexcept
		{
			return std::move(x).data_.begin(); // NOLINT(performance-move-const-arg)
		}

		[[nodiscard]] constexpr friend auto end(unqualified_rvalue_range_preferred&& x)
		{
			return std::move(x).data_.end(); // NOLINT(performance-move-const-arg)
		}

		[[nodiscard]] constexpr friend auto end(unqualified_rvalue_range_preferred const&& x) noexcept
		{
			return std::move(x).data_.end(); // NOLINT(performance-move-const-arg)
		}

		[[nodiscard]] constexpr friend range_t::pointer
		data(unqualified_rvalue_range_preferred&&) noexcept
		{
			return nullptr;
		}

		[[nodiscard]] constexpr friend range_t::const_pointer
		data(unqualified_rvalue_range_preferred const&&)
		{
			return nullptr;
		}

		range_t data_{}; // NOLINT(misc-non-private-member-variables-in-classes)
	};

	class unqualified_rvalue_range_private_members {
		using range_t = std::array<int, 1'000>; // NOLINT(readability-magic-numbers)
	public:
		[[nodiscard]] constexpr friend auto begin(unqualified_rvalue_range_private_members&& x)
		{
			return std::move(x).data_.begin(); // // NOLINT(performance-move-const-arg)
		}

		[[nodiscard]] constexpr friend
		auto begin(unqualified_rvalue_range_private_members const&& x) noexcept
		{
			return std::move(x).data_.begin(); // NOLINT(performance-move-const-arg)
		}

		[[nodiscard]] constexpr friend auto end(unqualified_rvalue_range_private_members&& x)
		{
			return std::move(x).data_.end(); // NOLINT(performance-move-const-arg)
		}

		[[nodiscard]] constexpr friend
		auto end(unqualified_rvalue_range_private_members const&& x) noexcept
		{
			return std::move(x).data_.end(); // NOLINT(performance-move-const-arg)
		}

		[[nodiscard]] constexpr friend range_t::pointer
		data(unqualified_rvalue_range_private_members&&) noexcept
		{
			return nullptr;
		}

		[[nodiscard]] constexpr friend range_t::const_pointer
		data(unqualified_rvalue_range_private_members const&&)
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

		[[nodiscard]] constexpr int data() noexcept;
		[[nodiscard]] constexpr int data() const;
	};
} // namespace cjdb_test

#endif // CJDB_TEST_UNQUALIFIED_RVALUE_RANGE_HPP
