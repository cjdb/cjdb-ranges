// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_IRREFLEXIVE_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_IRREFLEXIVE_HPP

#include "cjdb/concepts/callable/relation.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/functional/rangecmp/is_reflexive.hpp"
#include <utility>

namespace cjdb_test {
	template<class R>
	class is_irreflexive : private is_reflexive<R> {
	public:
		constexpr explicit is_irreflexive(R r) noexcept
		: is_reflexive<R>(r)
		{}

		/// \brief Checks that the relation is reflexive, with respect to type T.
		/// \param a Parameter to check.
		/// \returns invoke(r, a, a)
		///
		template<class A>
		requires cjdb::relation<R, A, A>
		[[nodiscard]] constexpr bool irreflexive(A const& a) noexcept
		{ return irreflexive_impl(*this, a); }

		/// \brief Checks that the relation is reflexive, with respect to type T.
		/// \param a Parameter to check.
		/// \returns invoke(r, a, a)
		///
		template<class A>
		requires cjdb::relation<R, A, A>
		[[nodiscard]] constexpr bool irreflexive(A const& a) const noexcept
		{ return irreflexive_impl(*this, a); }
	private:
		template<class Self, class A>
		[[nodiscard]] constexpr static bool irreflexive_impl(Self& self, A const& a)
		{ return not self.reflexive(a); }
	};
} // namespace cjdb_test

#define CHECK_IS_IRREFLEXIVE(r, a) CJDB_CONSTEXPR_CHECK(cjdb_test::is_irreflexive{r}.irreflexive(a))

#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_IRREFLEXIVE_HPP
