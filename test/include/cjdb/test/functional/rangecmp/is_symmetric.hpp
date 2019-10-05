// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_SYMMETRIC_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_SYMMETRIC_HPP

#include "cjdb/concepts/callable/relation.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/functional/rangecmp/relation.hpp"
#include <utility>

namespace cjdb_test {
	template<class R>
	class is_symmetric : protected relation<R> {
	public:
		constexpr explicit is_symmetric(R r)
		: relation<R>(std::move(r))
		{}

		/// \brief Checks that the relation is symmetric, with respect to types T and U.
		/// \param a Parameter to check.
		/// \param b Parameter to check.
		/// \returns invoke(r, a, b) == invoke(r, b, a)
		///
		template<class A, class B>
		requires cjdb::relation<R, A, B>
		[[nodiscard]] constexpr bool symmetric(A const& a, B const& b) noexcept
		{ return symmetric_impl(*this, a, b); }

		/// \brief Checks that the relation is symmetric, with respect to types T and U.
		/// \param a Parameter to check.
		/// \param b Parameter to check.
		/// \returns invoke(r, a, b) == invoke(r, b, a)
		///
		template<class A, class B>
		requires cjdb::relation<R, A, B>
		[[nodiscard]] constexpr bool symmetric(A const& a, B const& b) const noexcept
		{ return symmetric_impl(*this, a, b); }
	private:
		template<class Self, class A, class B>
		[[nodiscard]] constexpr static bool symmetric_impl(Self& self, A const& a, B const& b) noexcept
		{ return self(a, b) == self(b, a); }
	};
} // namespace cjdb_test

#define CHECK_IS_SYMMETRIC(r, a, b) CJDB_CONSTEXPR_CHECK(cjdb_test::is_symmetric{r}.symmetric(a, b))

#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_SYMMETRIC_HPP
