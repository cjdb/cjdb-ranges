// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_QUASIREFLEXIVE_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_QUASIREFLEXIVE_HPP

#include "cjdb/concepts/callable/relation.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/functional/rangecmp/is_reflexive.hpp"
#include <utility>

namespace cjdb_test {
	template<class R>
	class is_quasireflexive : private is_reflexive<R> {
	public:
		constexpr explicit is_quasireflexive(R r)
		: is_reflexive<R>(std::move(r))
		{}

		/// \brief Checks that the relation is reflexive, with respect to type T.
		/// \param a Parameter to check.
		/// \returns invoke(r, a, a)
		///
		template<class A, class B>
		requires cjdb::relation<R, A, B>
		[[nodiscard]] constexpr bool quasireflexive(A const& a, B const& b) noexcept
		{ return quasireflexive_impl(*this, std::move(a), std::move(b)); }

		/// \brief Checks that the relation is reflexive, with respect to type T.
		/// \param a Parameter to check.
		/// \returns invoke(r, a, a)
		///
		template<class A, class B>
		requires cjdb::relation<R, A, B>
		[[nodiscard]] constexpr bool quasireflexive(A const& a, B const& b) const noexcept
		{ return quasireflexive_impl(*this, std::move(a), std::move(b)); }
	private:
		template<class Self, class A, class B>
		[[nodiscard]] constexpr static
		bool quasireflexive_impl(Self& self, A const& a, B const& b) noexcept
		{ return self(a, b) and self.reflexive(a) and self.reflexive(b); }
	};
} // namespace cjdb_test

#define CHECK_IS_QUASIREFLEXIVE(r, a, b) \
	CJDB_CONSTEXPR_CHECK(cjdb_test::is_quasireflexive{r}.quasi_reflexive(a, b))

#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_QUASIREFLEXIVE_HPP
