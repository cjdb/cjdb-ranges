// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_TRANSITIVE_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_TRANSITIVE_HPP

#include "cjdb/concepts/callable/relation.hpp"
#include "cjdb/contracts.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/functional/rangecmp/relation.hpp"
#include <utility>

namespace cjdb_test {
	template<class R>
	class is_transitive : protected relation<R> {
	public:
		constexpr explicit is_transitive(R r)
		: relation<R>(std::move(r))
		{}

		/// \brief Checks that the relation is transitive, with respect to types T and U.
		/// \param a Parameter to check.
		/// \param b Parameter to check.
		/// \returns evaluates as true if, and only if, for some `auto c = a`,
		///          `invoke(r, a, b) and invoke(r, b, c) and invoke(r, a, c)` evaluates as true;
		///          false otherwise.
		///
		template<class A, class B>
		requires cjdb::relation<R, A, B>
		[[nodiscard]] constexpr bool transitive(A const& a, B const& b, A const& c) noexcept
		{ return transitive_impl(*this, a, b, c); }

		/// \brief Checks that the relation is transitive, with respect to types T and U.
		/// \param a Parameter to check.
		/// \param b Parameter to check.
		/// \returns evaluates as true if, and only if, for some `auto c = a`,
		///          `invoke(r, a, b) and invoke(r, b, c) and invoke(r, a, c)` evaluates as true;
		///          false otherwise.
		///
		template<class A, class B>
		requires cjdb::relation<R, A, B>
		[[nodiscard]] constexpr bool transitive(A const& a, B const& b, A const& c) const noexcept
		{ return transitive_impl(*this, a, b, c); }
	private:
		template<class Self, class A, class B>
		[[nodiscard]] constexpr static
		bool transitive_impl(Self& self, A const& a, B const& b, A const& c) noexcept
		{
			auto const aRb = self(a, b);
			CJDB_ASSERT(aRb and "transitivity cannot hold: aRc failed.");

			auto const bRc = self(b, c);
			CJDB_ASSERT(bRc and "transitivity cannot hold: bRc failed.");

			auto const aRc = self(a, c);
			return aRb and bRc and aRc;
		}
	};
} // namespace cjdb_test

#define CHECK_IS_TRANSITIVE(r, a, b, c) \
	CJDB_CONSTEXPR_CHECK(cjdb_test::is_transitive{r}.transitive(a, b, c))

#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_TRANSITIVE_HPP
