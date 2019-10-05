// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_ANTISYMMETRIC_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_ANTISYMMETRIC_HPP

#include "cjdb/concepts/callable/relation.hpp"
#include "cjdb/concepts/comparison/equality_comparable.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/functional/rangecmp/relation.hpp"
#include <utility>

namespace cjdb_test {
	template<class R>
	class is_antisymmetric : protected relation<R> {
	public:
		constexpr explicit is_antisymmetric(R r) noexcept
		: relation<R>(std::move(r))
		{}

		/// \brief Checks that the relation is symmetric, with respect to types T and U.
		/// \param a Parameter to check.
		/// \param b Parameter to check.
		/// \returns invoke(r, a, b) == invoke(r, b, a)
		///
		template<class A, cjdb::equality_comparable_with<A> B>
		requires cjdb::relation<R, A, B>
		[[nodiscard]] constexpr bool antisymmetric(A const& a, B const& b) noexcept
		{ return antisymmetric_impl(*this, a, b); }

		/// \brief Checks that the relation is symmetric, with respect to types T and U.
		/// \param a Parameter to check.
		/// \param b Parameter to check.
		/// \returns invoke(r, a, b) == invoke(r, b, a)
		///
		template<class A, cjdb::equality_comparable_with<A> B>
		requires cjdb::relation<R, A, B>
		[[nodiscard]] constexpr bool antisymmetric(A const& a, B const& b) const noexcept
		{ return antisymmetric_impl(*this, a, b); }
	private:
		template<class Self, class A, class B>
		[[nodiscard]] constexpr static bool antisymmetric_impl(Self& self, A const& a, B const& b) noexcept
		{ return (self(a, b) != self(b, a)) or (a == b); }
	};
} // namespace cjdb_test

#define CHECK_IS_ANTISYMMETRIC(r, a, b) \
	CJDB_CONSTEXPR_CHECK(cjdb_test::is_antisymmetric{r}.antisymmetric(a, b))

#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_ANTISYMMETRIC_HPP
