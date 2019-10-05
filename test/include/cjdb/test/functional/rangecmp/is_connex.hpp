// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_CONNEX_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_CONNEX_HPP

#include "cjdb/concepts/callable/relation.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/functional/rangecmp/relation.hpp"
#include <utility>

namespace cjdb_test {
	template<class R>
	class is_connex : protected relation<R> {
	public:
		constexpr explicit is_connex(R r) noexcept
		: relation<R>(std::move(r))
		{}

		template<class A, class B>
		[[nodiscard]] constexpr bool connex(A const& a, B const& b) noexcept
		{ return connex_impl(*this, a, b); }

		template<class A, class B>
		[[nodiscard]] constexpr bool connex(A const& a, B const& b) const noexcept
		{ return connex_impl(*this, a, b); }
	private:
		template<class Self, class A, class B>
		[[nodiscard]] constexpr static bool connex_impl(Self& self, A const& a, B const& b) noexcept
		{ return self(a, b) or self(b, a); }
	};
} // namespace cjdb_test

#define CHECK_IS_CONNEX(r, a, b) CJDB_CONSTEXPR_CHECK(cjdb_test::is_connex{r}.connex(a, b))

#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_CONNEX_HPP
