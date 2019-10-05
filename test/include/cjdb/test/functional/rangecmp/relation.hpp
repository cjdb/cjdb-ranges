// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_RELATION_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_RELATION_HPP

#include "cjdb/functional/invoke.hpp"
#include <utility>

namespace cjdb_test {
	template<class R>
	class relation {
	protected:
		constexpr explicit relation(R r) noexcept
		: r_(std::move(r))
		{}

		~relation() = default;

		template<class A, class B>
		[[nodiscard]] constexpr auto operator()(A&& a, B&& b) noexcept
		{ return cjdb::invoke(r_, std::forward<A>(a), std::forward<B>(b)); }

		template<class A, class B>
		[[nodiscard]] constexpr auto operator()(A&& a, B&& b) const noexcept
		{ return cjdb::invoke(r_, std::forward<A>(a), std::forward<B>(b)); }
	private:
		R r_;
	};
} // namespace cjdb_test

#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_RELATION_HPP
