// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_TRICHOTOMY_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_TRICHOTOMY_HPP

#include "cjdb/concepts/callable/relation.hpp"
#include "cjdb/concepts/comparison/equality_comparable.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/functional/rangecmp/relation.hpp"
#include <utility>

namespace cjdb_test {
	template<class R>
	class is_trichotomy : protected relation<R> {
	public:
		constexpr explicit is_trichotomy(R r)
		: relation<R>(std::move(r))
		{}

		template<class A, cjdb::equality_comparable_with<A> B>
		[[nodiscard]] constexpr bool trichotomy(A const& a, B const& b) noexcept
		{ return trichotomy_impl(*this, a, b); }

		template<class A, cjdb::equality_comparable_with<A> B>
		[[nodiscard]] constexpr bool trichotomy(A const& a, B const& b) const noexcept
		{ return trichotomy_impl(*this, a, b); }
	private:
		template<class Self, class A, class B>
		[[nodiscard]] constexpr static bool trichotomy_impl(Self& self, A const& a, B const& b) noexcept
		{
			auto const aRb = static_cast<bool>(self(a, b));
			auto const bRa = static_cast<bool>(self(b, a));
			auto const a_eq_b = static_cast<bool>(a == b);
			return ((not (aRb and bRa)) xor a_eq_b);
		}
	};
} // namespace cjdb_test

#define CHECK_IS_TRICHOTOMY(r, a, b) \
	CJDB_CONSTEXPR_CHECK(cjdb_test::is_trichotomy{r}.trichotomy(a, b))

#endif CJDB_TEST_FUNCTIONAL_RANGECMP_IS_TRICHOTOMY_HPP
