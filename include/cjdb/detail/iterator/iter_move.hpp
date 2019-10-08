// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_ITERATOR_ITER_MOVE_HPP
#define CJDB_DETAIL_ITERATOR_ITER_MOVE_HPP

#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/detail/concepts/core/reference.hpp"
#include "cjdb/detail/iterator/reference.hpp"
#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb::ranges::detail_iter_move {
	template<typename I>
	void iter_move(I);

	template<typename I>
	concept unqualified_iter_move =
		detail_iterator_reference::dereferenceable<I> and
		requires(I& i) {
			{ iter_move(i) } -> detail_iterator_reference::can_reference;
		};

	template<typename I>
	concept lvalue_iter_move =
		not unqualified_iter_move<I> and
		detail_iterator_reference::dereferenceable<I> and
		requires(I&& i) {
			{ *std::forward<I>(i) } -> detail_reference_concepts::lvalue_reference;
		};

	template<typename I>
	concept rvalue_iter_move =
		not unqualified_iter_move<I> and
		not lvalue_iter_move<I> and
		detail_iterator_reference::dereferenceable<I>;

	struct iter_move_fn {
		template<unqualified_iter_move I>
		constexpr decltype(auto) operator()(I&& i) const
		noexcept(noexcept(iter_move(std::forward<I>(i))))
		{ return iter_move(std::forward<I>(i)); }

		template<lvalue_iter_move I>
		constexpr auto&& operator()(I&& i) const noexcept(noexcept(std::move(*i)))
		{ return std::move(*std::forward<I>(i)); }

		template<rvalue_iter_move I>
		constexpr decltype(auto) operator()(I&& i) const noexcept(noexcept(*std::forward<I>(i)))
		{ return *std::forward<I>(i); }
	};
} // namespace cjdb::ranges::detail_iter_move

namespace cjdb::ranges {
	inline constexpr auto iter_move = detail_iter_move::iter_move_fn{};
} // namespace cjdb

#endif // CJDB_DETAIL_ITERATOR_ITER_MOVE_HPP
