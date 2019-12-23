// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_UNQUALIFIED_LVALUE_RANGE_HPP
#define CJDB_TEST_UNQUALIFIED_LVALUE_RANGE_HPP

#include <array>
#include "cjdb/detail/type_traits/maybe_const.hpp"

namespace cjdb_test {
	template<bool is_const = false>
	class unqualified_lvalue_range {
		using range_t = std::array<int, 1'000>; // NOLINT(readability-magic-numbers)
	public:
		using size_type = range_t::size_type;

		unqualified_lvalue_range() = default;

		constexpr explicit unqualified_lvalue_range(size_type const n) noexcept
		{ data_.fill(static_cast<int>(n)); }

		[[nodiscard]] constexpr friend auto begin(unqualified_lvalue_range& x) noexcept(false)
		{ return x.data_.begin(); }

		[[nodiscard]] constexpr friend auto begin(unqualified_lvalue_range const& x) noexcept
		{ return x.data_.begin(); }

		[[nodiscard]] constexpr friend
		auto end(unqualified_lvalue_range& x) noexcept(false)
		{ return x.data_.end(); }

		[[nodiscard]] constexpr friend
		auto end(unqualified_lvalue_range const& x) noexcept
		{ return x.data_.end(); }

		[[nodiscard]] constexpr friend
		range_t::pointer data(unqualified_lvalue_range&) noexcept(false)
		{ return nullptr; }

		[[nodiscard]] constexpr friend
		range_t::const_pointer data(unqualified_lvalue_range const&) noexcept
		{ return nullptr; }

		[[nodiscard]] constexpr friend
		auto size(cjdb::detail_maybe_const::maybe_const_t<is_const, unqualified_lvalue_range>& x)
		noexcept(is_const)
		{ return x.data_.size(); }

		range_t data_{}; // NOLINT(misc-non-private-member-variables-in-classes)
	};

	template<bool is_const = false>
	class unqualified_lvalue_range_preferred {
		using range_t = std::array<int, 1'000>; // NOLINT(readability-magic-numbers)
	public:
		using size_type = range_t::size_type;

		unqualified_lvalue_range_preferred() = default;

		constexpr explicit unqualified_lvalue_range_preferred(size_type const n) noexcept
		{
			data_.fill(static_cast<int>(n));
		}

		constexpr void begin() noexcept {}
		constexpr void begin() const noexcept(false) {}
		constexpr void end() noexcept {}
		constexpr void end() const noexcept(false) {}
		constexpr void size() noexcept(false) {}
		constexpr void size() const noexcept {}
		constexpr void data() noexcept {}
		constexpr void data() const noexcept(false) {}

		[[nodiscard]] constexpr friend
		auto begin(unqualified_lvalue_range_preferred& x) noexcept(false)
		{ return x.data_.begin(); }

		[[nodiscard]] constexpr friend
		auto begin(unqualified_lvalue_range_preferred const& x) noexcept
		{ return x.data_.begin(); }

		[[nodiscard]] constexpr friend
		auto end(unqualified_lvalue_range_preferred& x) noexcept(false)
		{ return x.data_.end(); }

		[[nodiscard]] constexpr friend
		auto end(unqualified_lvalue_range_preferred const& x) noexcept
		{ return x.data_.end(); }

		[[nodiscard]] constexpr friend
		auto size(cjdb::detail_maybe_const::maybe_const_t<is_const, unqualified_lvalue_range_preferred<is_const>>& x)
		noexcept(is_const)
		{ return x.data_.size(); }

		[[nodiscard]] constexpr friend
		range_t::pointer data(unqualified_lvalue_range_preferred&) noexcept(false)
		{ return nullptr; }

		[[nodiscard]] constexpr friend
		range_t::const_pointer data(unqualified_lvalue_range_preferred const&) noexcept
		{ return nullptr; }

		range_t data_{}; // NOLINT(misc-non-private-member-variables-in-classes)
	};

	template<bool is_const = false>
	class unqualified_lvalue_range_private_members {
		using range_t = std::array<int, 1'000>; // NOLINT(readability-magic-numbers)
	public:
		using size_type = range_t::size_type;

		unqualified_lvalue_range_private_members() = default;

		constexpr explicit unqualified_lvalue_range_private_members(size_type const n) noexcept
		{
			data_.fill(static_cast<int>(n));
		}

		[[nodiscard]] constexpr friend
		auto begin(unqualified_lvalue_range_private_members& x) noexcept(false)
		{ return x.data_.begin(); }

		[[nodiscard]] constexpr friend
		auto begin(unqualified_lvalue_range_private_members const& x) noexcept
		{ return x.data_.begin(); }

		[[nodiscard]] constexpr friend
		auto end(unqualified_lvalue_range_private_members& x) noexcept(false)
		{ return x.data_.end(); }

		[[nodiscard]] constexpr friend
		auto end(unqualified_lvalue_range_private_members const& x) noexcept
		{ return x.data_.end(); }

		[[nodiscard]] constexpr friend
		auto size(cjdb::detail_maybe_const::maybe_const_t<is_const, unqualified_lvalue_range_private_members<is_const>>& x)
		noexcept(is_const)
		{ return x.data_.size(); }

		[[nodiscard]] constexpr friend range_t::pointer
		data(unqualified_lvalue_range_private_members&) noexcept(false)
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
		[[nodiscard]] constexpr auto begin() const noexcept(false)
		{ return data_.begin(); }

		[[nodiscard]] constexpr auto end() noexcept
		{ return data_.end(); }
		[[nodiscard]] constexpr auto end() const noexcept(false)
		{ return data_.end(); }

		[[nodiscard]] constexpr auto size() noexcept
		{ return data_.size(); }
		[[nodiscard]] constexpr auto size() const noexcept(false)
		{ return data_.size(); }

		[[nodiscard]] constexpr range_t::pointer data() noexcept
		{ return nullptr; }
		[[nodiscard]] constexpr range_t::const_pointer data() const noexcept(false)
		{ return nullptr; }
	};
} // namespace cjdb_test

#endif // CJDB_TEST_UNQUALIFIED_LVALUE_RANGE_HPP
