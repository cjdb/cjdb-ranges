// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_CONCEPTS_COMPARISON_STRICT_TOTALLY_ORDERED_HPP
#define CJDB_TEST_CONCEPTS_COMPARISON_STRICT_TOTALLY_ORDERED_HPP

#include "boolean.hpp"
#include "cjdb/concepts/core/same_as.hpp"

namespace cjdb_test {
	class totally_ordered1 {
	public:
		totally_ordered1() = default;

		template<cjdb::same_as<int> T>
		constexpr totally_ordered1(T x)
		: x_{x}
		{}

		constexpr friend bool
		operator<(totally_ordered1 x, totally_ordered1 y) noexcept
		{ return x.x_ < y.x_; }

		constexpr friend bool
		operator>(totally_ordered1 x, totally_ordered1 y) noexcept
		{ return y < x; }

		constexpr friend bool
		operator<=(totally_ordered1 x, totally_ordered1 y) noexcept
		{ return not (y < x); }

		constexpr friend bool
		operator>=(totally_ordered1 x, totally_ordered1 y) noexcept
		{ return not (x < y); }

		constexpr friend bool
		operator==(totally_ordered1 x, totally_ordered1 y) noexcept
		{ return x.x_ == y.x_; }

		constexpr friend bool
		operator!=(totally_ordered1 x, totally_ordered1 y) noexcept
		{ return not (x == y); }
	private:
		int x_ = 0;
	};

	class totally_ordered2 {
	public:
		constexpr friend boolean
		operator<(totally_ordered2 x, totally_ordered2 y) noexcept
		{ return x.x_ < y.x_; }

		constexpr friend boolean
		operator>(totally_ordered2 x, totally_ordered2 y) noexcept
		{ return y < x; }

		constexpr friend boolean
		operator<=(totally_ordered2 x, totally_ordered2 y) noexcept
		{ return not (y < x); }

		constexpr friend boolean
		operator>=(totally_ordered2 x, totally_ordered2 y) noexcept
		{ return not (x < y); }

		constexpr friend boolean
		operator==(totally_ordered2 x, totally_ordered2 y) noexcept
		{ return x.x_ == y.x_; }

		constexpr friend boolean
		operator!=(totally_ordered2 x, totally_ordered2 y) noexcept
		{ return not (x == y); }

		constexpr operator totally_ordered1() const noexcept
		{ return {x_}; }
	private:
		int x_ = 0;
	};

	class totally_ordered3 {
	public:
		constexpr friend boolean
		operator<(totally_ordered3 x, totally_ordered3 y) noexcept
		{ return x.x_ < y.x_; }

		constexpr friend boolean
		operator>(totally_ordered3 x, totally_ordered3 y) noexcept
		{ return y < x; }

		constexpr friend boolean
		operator<=(totally_ordered3 y, totally_ordered3 x) noexcept
		{ return not (x < y); }

		constexpr friend boolean
		operator>=(totally_ordered3 x, totally_ordered3 y) noexcept
		{ return not (x < y); }

		constexpr friend boolean
		operator==(totally_ordered3 x, totally_ordered3 y) noexcept
		{ return x.x_ == y.x_; }

		constexpr friend boolean
		operator!=(totally_ordered3 x, totally_ordered3 y) noexcept
		{ return not (x == y); }
	private:
		int x_ = 0;
	};

	class not_totally_ordered_no_lt {
	public:
		constexpr friend bool
		operator>(not_totally_ordered_no_lt x, not_totally_ordered_no_lt y) noexcept
		{ return y.x_ < x.x_; }

		constexpr friend bool
		operator<=(not_totally_ordered_no_lt y, not_totally_ordered_no_lt x) noexcept
		{ return not (y > x); }

		constexpr friend bool
		operator>=(not_totally_ordered_no_lt x, not_totally_ordered_no_lt y) noexcept
		{ return not (y > x); }

		constexpr friend bool
		operator==(not_totally_ordered_no_lt x, not_totally_ordered_no_lt y) noexcept
		{ return x.x_ == y.x_; }

		constexpr friend bool
		operator!=(not_totally_ordered_no_lt x, not_totally_ordered_no_lt y) noexcept
		{ return not (x == y); }
	private:
		int x_ = 0;
	};

	class not_totally_ordered_no_gt {
	public:
		constexpr friend bool
		operator<(not_totally_ordered_no_gt x, not_totally_ordered_no_gt y) noexcept
		{ return x.x_ < y.x_; }

		constexpr friend bool
		operator<=(not_totally_ordered_no_gt y, not_totally_ordered_no_gt x) noexcept
		{ return not (x < y); }

		constexpr friend bool
		operator>=(not_totally_ordered_no_gt x, not_totally_ordered_no_gt y) noexcept
		{ return not (x < y); }

		constexpr friend bool
		operator==(not_totally_ordered_no_gt x, not_totally_ordered_no_gt y) noexcept
		{ return x.x_ == y.x_; }

		constexpr friend bool
		operator!=(not_totally_ordered_no_gt x, not_totally_ordered_no_gt y) noexcept
		{ return not (x == y); }
	private:
		int x_ = 0;
	};

	class not_totally_ordered_no_le {
	public:
		constexpr friend bool
		operator<(not_totally_ordered_no_le x, not_totally_ordered_no_le y) noexcept
		{ return x.x_ < y.x_; }

		constexpr friend bool
		operator>(not_totally_ordered_no_le x, not_totally_ordered_no_le y) noexcept
		{ return y < x; }

		constexpr friend bool
		operator>=(not_totally_ordered_no_le x, not_totally_ordered_no_le y) noexcept
		{ return not (x < y); }

		constexpr friend bool
		operator==(not_totally_ordered_no_le x, not_totally_ordered_no_le y) noexcept
		{ return x.x_ == y.x_; }

		constexpr friend bool
		operator!=(not_totally_ordered_no_le x, not_totally_ordered_no_le y) noexcept
		{ return not (x == y); }
	private:
		int x_ = 0;
	};

	class not_totally_ordered_no_ge {
	public:
		constexpr friend bool
		operator<(not_totally_ordered_no_ge x, not_totally_ordered_no_ge y) noexcept
		{ return x.x_ < y.x_; }

		constexpr friend bool
		operator>(not_totally_ordered_no_ge x, not_totally_ordered_no_ge y) noexcept
		{ return y < x; }

		constexpr friend bool
		operator<=(not_totally_ordered_no_ge y, not_totally_ordered_no_ge x) noexcept
		{ return not (x < y); }

		constexpr friend bool
		operator==(not_totally_ordered_no_ge x, not_totally_ordered_no_ge y) noexcept
		{ return x.x_ == y.x_; }

		constexpr friend bool
		operator!=(not_totally_ordered_no_ge x, not_totally_ordered_no_ge y) noexcept
		{ return not (x == y); }
	private:
		int x_ = 0;
	};

	class not_totally_ordered_no_eq {
	public:
		constexpr friend bool
		operator<(not_totally_ordered_no_eq x, not_totally_ordered_no_eq y) noexcept
		{ return x.x_ < y.x_; }

		constexpr friend bool
		operator>(not_totally_ordered_no_eq x, not_totally_ordered_no_eq y) noexcept
		{ return y < x; }

		constexpr friend bool
		operator<=(not_totally_ordered_no_eq y, not_totally_ordered_no_eq x) noexcept
		{ return not (x < y); }

		constexpr friend bool
		operator>=(not_totally_ordered_no_eq x, not_totally_ordered_no_eq y) noexcept
		{ return not (x < y); }

		constexpr friend bool
		operator!=(not_totally_ordered_no_eq x, not_totally_ordered_no_eq y) noexcept
		{ return x.x_ != y.x_; }
	private:
		int x_ = 0;
	};

	class not_totally_ordered_no_ne {
	public:
		constexpr friend bool
		operator<(not_totally_ordered_no_ne x, not_totally_ordered_no_ne y) noexcept
		{ return x.x_ < y.x_; }

		constexpr friend bool
		operator>(not_totally_ordered_no_ne x, not_totally_ordered_no_ne y) noexcept
		{ return y < x; }

		constexpr friend bool
		operator<=(not_totally_ordered_no_ne y, not_totally_ordered_no_ne x) noexcept
		{ return not (x < y); }

		constexpr friend bool
		operator>=(not_totally_ordered_no_ne x, not_totally_ordered_no_ne y) noexcept
		{ return not (x < y); }

		constexpr friend bool
		operator==(not_totally_ordered_no_ne x, not_totally_ordered_no_ne y) noexcept
		{ return x.x_ == y.x_; }
	private:
		int x_ = 0;
	};

	class not_totally_ordered_wrong_return {
	public:
		constexpr void operator==(not_totally_ordered_wrong_return) const noexcept {}
		constexpr void operator!=(not_totally_ordered_wrong_return) const noexcept {}

		constexpr void operator<(not_totally_ordered_wrong_return) const noexcept {}
		constexpr void operator>(not_totally_ordered_wrong_return) const noexcept {}
		constexpr void operator<=(not_totally_ordered_wrong_return) const noexcept {}
		constexpr void operator>=(not_totally_ordered_wrong_return) const noexcept {}
	};
} // namespace cjdb_test

#endif // CJDB_TEST_CONCEPTS_COMPARISON_STRICT_TOTALLY_ORDERED_HPP
