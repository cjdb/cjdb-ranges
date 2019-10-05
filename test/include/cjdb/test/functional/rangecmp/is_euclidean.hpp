// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_EUCLIDEAN_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_EUCLIDEAN_HPP

#include "cjdb/concepts/callable/relation.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include "cjdb/test/functional/rangecmp/relation.hpp"
#include <utility>

namespace cjdb_test {
	template<class R>
	class is_euclidean_relation : protected relation<R> {
	public:
		constexpr explicit is_euclidean_relation(R r) noexcept
		: relation<R>(std::move(r))
		{}

		template<class A, class B>
		requires cjdb::relation<R, A, B>
		[[nodiscard]] constexpr bool euclidean(A const& a, B const& b, A const& c) noexcept
		{ return euclidean_impl(*this, a, b, c); }

		template<class A, class B>
		requires cjdb::relation<R, A, B>
		[[nodiscard]] constexpr bool euclidean(A const& a, B const& b, A const& c) const noexcept
		{ return euclidean_impl(*this, a, b, c); }
	private:
		template<class Self, class A, class B>
		[[nodiscard]] constexpr static
		bool euclidean_impl(Self& self, A const& a, B const& b, A const& c) noexcept
		{ return self(a, b) and self(a, c) and self(b, c); }
	};
} // namespace cjdb_test

#define CHECK_IS_EUCLIDEAN_RELATION(r, a, b, c) \
	CJDB_CONSTEXPR_CHECK(cjdb_test::is_euclidean_relation{r}.euclidean(a, b, c))

#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_EUCLIDEAN_HPP
