// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_ASYMMETRIC_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_ASYMMETRIC_HPP

#include "cjdb/concepts/callable/relation.hpp"
#include "cjdb/concepts/comparison/equality_comparable.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/functional/rangecmp/is_antisymmetric.hpp"
#include "cjdb/test/functional/rangecmp/is_irreflexive.hpp"
#include <utility>

namespace cjdb_test {
	template<class R>
	class is_asymmetric
	: private is_irreflexive<R>
	, private is_antisymmetric<R> {
	public:
		constexpr explicit is_asymmetric(R r) noexcept
		: is_irreflexive<R>(r)
		, is_antisymmetric<R>(r)
		{}

		template<class A, cjdb::equality_comparable_with<A> B>
		requires cjdb::relation<R, A, B>
		[[nodiscard]] constexpr bool asymmetric(A const& a, B const& b) noexcept
		{ return asymmetric_impl(*this, a, b); }

		template<class A, cjdb::equality_comparable_with<A> B>
		requires cjdb::relation<R, A, B>
		[[nodiscard]] constexpr bool asymmetric(A const& a, B const& b) const noexcept
		{ return asymmetric_impl(*this, a, b); }
	private:
		template<class Self, class A, class B>
		[[nodiscard]] constexpr bool asymmetric_impl(Self& self, A const& a, B const& b) noexcept
		{ return self.irreflexive(a) and self.irreflexive(b) and self.antisymmetric(a, b); }
	};
} // namespace cjdb_test

#define CHECK_IS_ASYMMETRIC(r, a, b) \
	CJDB_CONSTEXPR_CHECK(cjdb_test::is_asymmetric{r}.asymmetric(a, b))

#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_ASYMMETRIC_HPP
