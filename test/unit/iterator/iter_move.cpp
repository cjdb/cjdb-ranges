// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/iterator/iterator_customisation.hpp"

#include "cjdb/test/simple_test.hpp"
#include <utility>
#include <vector>

namespace cjdb_test {
	/// \brief Wrapper around an iterator for testing unqualified calls to iter_move and iter_swap.
	/// \tparam I A type that should model an input iterator.
	///
	template<typename I>
	class unqualified_lookup_wrapper {
	public:
		unqualified_lookup_wrapper() = default;

		constexpr explicit unqualified_lookup_wrapper(I i) noexcept
		: base_(std::move(i))
		{}

		[[nodiscard]] constexpr decltype(auto) operator*() const noexcept { return *base_; }

		constexpr unqualified_lookup_wrapper& operator++() noexcept
		{
			++base_;
			return *this;
		}

		constexpr void operator++(int) noexcept { ++base_; }

		[[nodiscard]] constexpr
		bool operator==(unqualified_lookup_wrapper const& other) const noexcept
		{ return base_ == other.base_; }

		[[nodiscard]] constexpr
		bool operator!=(unqualified_lookup_wrapper const& other) const noexcept
		{ return not (*this == other); }

		/// \brief Delegates cjdb::ranges::iter_move for the underlying iterator.
		/// \param i The iterator to move the contents out of.
		/// \note `noexcept(false)` will be used to ensure that the unqualified-lookup overload is
		///       chosen.
		///
		[[nodiscard]] friend constexpr
		decltype(auto) iter_move(unqualified_lookup_wrapper& i) noexcept(false)
		{ return cjdb::ranges::iter_move(i.base_); }

		// friend void iter_swap(unqualified_lookup_wrapper& lhs, unqualified_lookup_wrapper& rhs)
		// {
		// 	ranges::iter_swap(lhs.base_, rhs_.base_);
		// }
	private:
		I base_ = I{};
	};

	/// \brief Wrapper around an iterator for testing iter_move when an unqualified call to iter_move
	///        isn't possible.
	/// \tparam I A type that should model an input iterator.
	///
	template<typename I>
	class iterator_wrapper {
	public:
		iterator_wrapper() = default;

		constexpr explicit iterator_wrapper(I i) noexcept
		: base_(std::move(i))
		{}

		/// \note `noexcept(false)` is used to check that this operator is called.
		///
		[[nodiscard]] constexpr decltype(auto) operator*() const& noexcept(false) { return *base_; }

		/// \note `noexcept` is used to check that this operator is called.
		///
		[[nodiscard]] constexpr auto&& operator*() && noexcept
		{ return std::move(*base_); }

		constexpr iterator_wrapper& operator++() noexcept
		{
			++base_;
			return *this;
		}

		constexpr void operator++(int) noexcept { ++base_; }

		[[nodiscard]] constexpr bool operator==(iterator_wrapper const& other) const noexcept
		{ return base_ == other.base_; }

		[[nodiscard]] constexpr bool operator!=(iterator_wrapper const& other) const noexcept
		{ return not (*this == other); }
	private:
		I base_ = I{};
	};

	class move_tracker {
	public:
		move_tracker() = default;

		constexpr move_tracker(move_tracker&& other) noexcept
		: moves_{other.moves_ + 1}
		{
			other.moves_ = 0;
		}

		constexpr move_tracker& operator=(move_tracker&& other) noexcept
		{
			moves_ = other.moves_ + 1;
			other.moves_ = 0;
			return *this;
		}

		constexpr move_tracker(move_tracker const& other) = delete;
		constexpr move_tracker& operator=(move_tracker const& other) = delete;

		[[nodiscard]] constexpr int moves() const noexcept { return moves_; }
	private:
		int moves_ = 0;
	};
} // namespace cjdb_test

///
///
template<typename I>
constexpr void unqualified_lookup_move(I first_, I last_, I result_first_, I result_last_)
{
	auto first = cjdb_test::unqualified_lookup_wrapper{std::move(first_)};
	auto last = cjdb_test::unqualified_lookup_wrapper{std::move(last_)};
	auto result_first = cjdb_test::unqualified_lookup_wrapper{std::move(result_first_)};
	auto result_last = cjdb_test::unqualified_lookup_wrapper{std::move(result_last_)};

	static_assert(not noexcept(cjdb::ranges::iter_move(first)),
	              "unqualified-lookup case not being chosen");

	for (; bool(first != last) and bool(result_first != result_last);
	       (void)++first, (void)++result_first) {
		*result_first = cjdb::ranges::iter_move(first);
	}
}

template<typename I>
constexpr void lvalue_move(I first_, I last_, I result_first_, I result_last_)
{
	auto first = cjdb_test::iterator_wrapper{std::move(first_)};
	auto last = cjdb_test::iterator_wrapper{std::move(last_)};
	auto result_first = cjdb_test::iterator_wrapper{std::move(result_first_)};
	auto result_last = cjdb_test::iterator_wrapper{std::move(result_last_)};

	static_assert(not noexcept(cjdb::ranges::iter_move(first)),
	              "`operator*() const&` is not noexcept, and there's no hidden friend iter_move.");

	for (; bool(first != last) and bool(result_first != result_last);
	       (void)++first, (void)++result_first) {
		*result_first = cjdb::ranges::iter_move(first);
	}
}

template<typename I>
constexpr void rvalue_move(I first_, I last_, I result_first_, I result_last_)
{
	auto first = cjdb_test::iterator_wrapper{std::move(first_)};
	auto last = cjdb_test::iterator_wrapper{std::move(last_)};
	auto result_first = cjdb_test::iterator_wrapper{std::move(result_first_)};
	auto result_last = cjdb_test::iterator_wrapper{std::move(result_last_)};

	static_assert(noexcept(cjdb::ranges::iter_move(std::move(first))),
	              "`operator*() &&` is noexcept, and there's no hidden friend iter_move.");

	for (; bool(first != last) and bool(result_first != result_last);
	       (void)++first, (void)++result_first) {
		auto i = first;
		*result_first = cjdb::ranges::iter_move(std::move(i));
	}
}

template<typename I, typename Pred>
constexpr void check_all_of(I first, I last, Pred const& pred)
{
	for (; first != last; ++first) {
		CHECK(pred(*first));
	}
}

int main()
{
	constexpr auto full_size = 100;
	constexpr auto half_size = full_size / 2;
	auto v1 = std::vector<cjdb_test::move_tracker>(full_size);
	auto v2 = std::vector<cjdb_test::move_tracker>(half_size);

	unqualified_lookup_move(v1.begin(), v1.end(), v2.begin(), v2.end());

	auto move_counter_is = [](auto const n) {
		return [n](auto const& x) { return x.moves() == n; };
	};

	check_all_of(v1.cbegin(), v1.cend(), move_counter_is(0));
	check_all_of(v2.cbegin(), v2.cend(), move_counter_is(1));

	auto v3 = std::vector<cjdb_test::move_tracker>(half_size);
	unqualified_lookup_move(v1.begin() + half_size, v1.end(), v3.begin(), v3.end());
	check_all_of(v1.cbegin(), v1.cend(), move_counter_is(0));
	check_all_of(v3.cbegin(), v3.cend(), move_counter_is(1));

	auto v4 = std::vector<cjdb_test::move_tracker>(half_size);
	unqualified_lookup_move(v3.begin(), v3.end(), v4.begin(), v4.end());
	check_all_of(v3.cbegin(), v3.cend(), move_counter_is(0));
	check_all_of(v4.cbegin(), v4.cend(), move_counter_is(2));

	lvalue_move(v2.begin(), v2.end(), v1.begin() + half_size, v1.end());
	check_all_of(v2.cbegin(), v2.cend(), move_counter_is(0));
	check_all_of(v1.cbegin() + half_size, v1.cend(), move_counter_is(2));

	lvalue_move(v4.begin(), v4.end(), v1.begin(), v1.end());
	check_all_of(v4.cbegin(), v4.cend(), move_counter_is(0));
	check_all_of(v1.cbegin(), v1.cbegin() + half_size, move_counter_is(3));

	rvalue_move(v1.begin(), v1.end(), v2.begin(), v2.end());
	check_all_of(v1.cbegin(), v1.cbegin() + half_size, move_counter_is(0));
	check_all_of(v2.cbegin(), v2.cend(), move_counter_is(4));

	rvalue_move(v1.begin() + half_size, v1.end(), v3.begin(), v3.end());
	check_all_of(v1.cbegin(), v1.cend(), move_counter_is(0));
	check_all_of(v3.cbegin(), v3.cend(), move_counter_is(3));

	return ::test_result();
}
