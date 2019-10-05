// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_REFLEXIVE_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_REFLEXIVE_HPP

#include "cjdb/concepts/callable/relation.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/functional/rangecmp/relation.hpp"
#include <utility>

namespace cjdb_test {
	template<class R>
	class is_reflexive : protected relation<R> {
	public:
		constexpr explicit is_reflexive(R r) noexcept
		: relation<R>(std::move(r))
		{}

		/// \brief Checks that the relation is reflexive, with respect to type T.
		/// \param a Parameter to check.
		/// \returns invoke(r, a, a)
		///
		template<class A>
		requires cjdb::relation<R, A, A>
		[[nodiscard]] constexpr bool reflexive(A const& a) noexcept
		{ return reflexive_impl(*this, a); }

		/// \brief Checks that the relation is reflexive, with respect to type T.
		/// \param a Parameter to check.
		/// \returns invoke(r, a, a)
		///
		template<class A>
		requires cjdb::relation<R, A, A>
		[[nodiscard]] constexpr bool reflexive(A const& a) const noexcept
		{ return reflexive_impl(*this, a); }
	private:
		template<class Self, class A>
		[[nodiscard]] constexpr static bool reflexive_impl(Self& self, A const& a) noexcept
		{ return self(a, a); }
	};
} // namespace cjdb_test

#define CHECK_IS_REFLEXIVE(r, a) CJDB_CONSTEXPR_CHECK(cjdb_test::is_reflexive{r}.reflexive(a))

#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_REFLEXIVE_HPP
