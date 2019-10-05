// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_COREFLEXIVE_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_COREFLEXIVE_HPP

#include "cjdb/concepts/callable/relation.hpp"
#include "cjdb/concepts/comparison/equality_comparable.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/functional/rangecmp/is_reflexive.hpp"
#include <utility>

namespace cjdb_test {
	template<class R>
	class is_coreflexive : private is_reflexive<R> {
	public:
		constexpr explicit is_coreflexive(R r) noexcept
		: is_reflexive<R>(std::move(r))
		{}

		/// \brief Checks that the relation is reflexive, with respect to type T.
		/// \param a Parameter to check.
		/// \returns invoke(r, a, a)
		///
		template<cjdb::equality_comparable A>
		requires cjdb::relation<R, A, A>
		[[nodiscard]] constexpr bool coreflexive(A const& a) noexcept
		{ return coreflexive_impl(*this, std::move(a)); }

		/// \brief Checks that the relation is reflexive, with respect to type T.
		/// \param a Parameter to check.
		/// \returns invoke(r, a, a)
		///
		template<cjdb::equality_comparable A>
		requires cjdb::relation<R, A, A>
		[[nodiscard]] constexpr bool coreflexive(A const& a) const noexcept
		{ return coreflexive_impl(*this, std::move(a)); }
	private:
		template<class Self, class A>
		[[nodiscard]] constexpr static bool coreflexive_impl(Self& self, A const& a)
		{ return self.reflexive(a) and a == a; }
	};
} // namespace cjdb_test

#define CHECK_IS_COREFLEXIVE(r, a) CJDB_CONSTEXPR_CHECK(cjdb_test::is_coreflexive{r}.coreflexive(a))

#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_COREFLEXIVE_HPP
