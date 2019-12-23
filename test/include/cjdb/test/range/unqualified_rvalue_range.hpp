// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_UNQUALIFIED_RVALUE_RANGE_HPP
#define CJDB_TEST_UNQUALIFIED_RVALUE_RANGE_HPP

#include <array>

namespace cjdb_test {
	template<bool is_const = false>
	class unqualified_rvalue_range {
		using range_t = std::array<int, 1'000>; // NOLINT(readability-magic-numbers)
	public:
		using size_type = range_t::size_type;

		unqualified_rvalue_range() = default;

		constexpr explicit unqualified_rvalue_range(size_type const n) noexcept
		{ data_.fill(static_cast<int>(n)); }

		[[nodiscard]] constexpr friend auto begin(unqualified_rvalue_range&& x) noexcept(false)
		{
			return std::move(x).data_.begin(); // NOLINT(performance-move-const-arg)
		}

		[[nodiscard]] constexpr friend auto begin(unqualified_rvalue_range const&& x) noexcept
		{
			return std::move(x).data_.begin(); // NOLINT(performance-move-const-arg)
		}

		[[nodiscard]] constexpr friend auto end(unqualified_rvalue_range&& x) noexcept(false)
		{
			return std::move(x).data_.end(); // NOLINT(performance-move-const-arg)
		}

		[[nodiscard]] constexpr friend auto end(unqualified_rvalue_range const&& x) noexcept
		{
			return std::move(x).data_.end(); // NOLINT(performance-move-const-arg)
		}

		[[nodiscard]] constexpr friend range_t::pointer data(unqualified_rvalue_range&&) noexcept(false)
		{ return nullptr; }

		[[nodiscard]] constexpr friend
		range_t::const_pointer data(unqualified_rvalue_range const&&) noexcept
		{ return nullptr; }

		[[nodiscard]] constexpr friend
		auto size(cjdb::detail_maybe_const::maybe_const_t<is_const, unqualified_rvalue_range>&& x)
		noexcept(is_const)
		{ return std::move(x).data_.size(); }

		range_t data_{}; // NOLINT(,misc-non-private-member-variables-in-classes)
	};

	template<bool is_const = false>
	class unqualified_rvalue_range_preferred {
		using range_t = std::array<int, 1'000>; // NOLINT(readability-magic-numbers)
	public:
		using size_type = range_t::size_type;

		unqualified_rvalue_range_preferred() = default;

		constexpr explicit unqualified_rvalue_range_preferred(size_type const n) noexcept
		{ data_.fill(static_cast<int>(n)); }

		[[nodiscard]] constexpr void begin() noexcept {}
		[[nodiscard]] constexpr void begin() const noexcept(false) {}

		[[nodiscard]] constexpr void end() noexcept {}
		[[nodiscard]] constexpr void end() const noexcept(false) {}

		[[nodiscard]] constexpr void data() noexcept {}
		[[nodiscard]] constexpr void data() const noexcept(false) {}

		[[nodiscard]] constexpr friend auto begin(unqualified_rvalue_range_preferred&& x)
		{
			return std::move(x).data_.begin(); // NOLINT(performance-move-const-arg)
		}

		[[nodiscard]] constexpr friend
		auto begin(unqualified_rvalue_range_preferred const&& x) noexcept
		{
			return std::move(x).data_.begin(); // NOLINT(performance-move-const-arg)
		}

		[[nodiscard]] constexpr friend auto end(unqualified_rvalue_range_preferred&& x) noexcept(false)
		{
			return std::move(x).data_.end(); // NOLINT(performance-move-const-arg)
		}

		[[nodiscard]] constexpr friend auto end(unqualified_rvalue_range_preferred const&& x) noexcept
		{
			return std::move(x).data_.end(); // NOLINT(performance-move-const-arg)
		}

		[[nodiscard]] constexpr friend range_t::pointer
		data(unqualified_rvalue_range_preferred&&) noexcept(false)
		{
			return nullptr;
		}

		[[nodiscard]] constexpr friend range_t::const_pointer
		data(unqualified_rvalue_range_preferred const&&) noexcept
		{
			return nullptr;
		}

		[[nodiscard]] constexpr friend
		auto size(cjdb::detail_maybe_const::maybe_const_t<is_const, unqualified_rvalue_range_preferred>&& x)
		noexcept(is_const)
		{ return std::move(x).data_.size(); }

		range_t data_{}; // NOLINT(misc-non-private-member-variables-in-classes)
	};

	template<bool is_const = false>
	class unqualified_rvalue_range_private_members {
		using range_t = std::array<int, 1'000>; // NOLINT(readability-magic-numbers)
	public:
		using size_type = range_t::size_type;

		unqualified_rvalue_range_private_members() = default;

		constexpr explicit unqualified_rvalue_range_private_members(size_type const n) noexcept
		{ data_.fill(static_cast<int>(n)); }

		[[nodiscard]] constexpr friend
		auto begin(unqualified_rvalue_range_private_members&& x) noexcept(false)
		{
			return std::move(x).data_.begin(); // // NOLINT(performance-move-const-arg)
		}

		[[nodiscard]] constexpr friend
		auto begin(unqualified_rvalue_range_private_members const&& x) noexcept
		{
			return std::move(x).data_.begin(); // NOLINT(performance-move-const-arg)
		}

		[[nodiscard]] constexpr friend
		auto end(unqualified_rvalue_range_private_members&& x) noexcept(false)
		{
			return std::move(x).data_.end(); // NOLINT(performance-move-const-arg)
		}

		[[nodiscard]] constexpr friend
		auto end(unqualified_rvalue_range_private_members const&& x) noexcept
		{
			return std::move(x).data_.end(); // NOLINT(performance-move-const-arg)
		}

		[[nodiscard]] constexpr friend range_t::pointer
		data(unqualified_rvalue_range_private_members&&) noexcept(false)
		{ return nullptr; }

		[[nodiscard]] constexpr friend range_t::const_pointer
		data(unqualified_rvalue_range_private_members const&&) noexcept
		{ return nullptr; }

		[[nodiscard]] constexpr friend
		auto size(cjdb::detail_maybe_const::maybe_const_t<is_const, unqualified_rvalue_range_private_members>&& x)
		noexcept(is_const)
		{ return std::move(x).data_.size(); }

		range_t data_{}; // NOLINT(misc-non-private-member-variables-in-classes)
	private:
		[[nodiscard]] constexpr void begin() noexcept {}
		[[nodiscard]] constexpr void begin() const noexcept(false) {}

		[[nodiscard]] constexpr void end() noexcept {}
		[[nodiscard]] constexpr void end() const noexcept(false) {}

		[[nodiscard]] constexpr void data() noexcept {}
		[[nodiscard]] constexpr void data() const noexcept(false) {}
	};
} // namespace cjdb_test

#endif // CJDB_TEST_UNQUALIFIED_RVALUE_RANGE_HPP
