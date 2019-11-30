// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_CONCEPTS_CORE_FUNDAMENTAL_HPP
#define CJDB_TEST_CONCEPTS_CORE_FUNDAMENTAL_HPP

namespace cjdb_test {
	#define DEFINE_MODELS_CONCEPT_CHECK_FOR(concept)                                       \
		template<class I, bool expected = true>                                             \
		constexpr void models_##concept() noexcept                                          \
		{                                                                                   \
			static_assert(cjdb::concept<I> == expected);                                     \
			static_assert(cjdb::concept<I const> == expected);                               \
			static_assert(cjdb::concept<I volatile> == expected);                            \
			static_assert(cjdb::concept<I const volatile> == expected);                      \
			                                                                                 \
			static_assert(not cjdb::concept<I*>);                                            \
			static_assert(not cjdb::concept<I const*>);                                      \
			static_assert(not cjdb::concept<I volatile*>);                                   \
			static_assert(not cjdb::concept<I const volatile*>);                             \
			                                                                                 \
			static_assert(not cjdb::concept<I&>);                                            \
			static_assert(not cjdb::concept<I const&>);                                      \
			static_assert(not cjdb::concept<I volatile&>);                                   \
			static_assert(not cjdb::concept<I const volatile&>);                             \
			                                                                                 \
			static_assert(not cjdb::concept<std::remove_reference_t<I>&&>);                  \
			static_assert(not cjdb::concept<std::remove_reference_t<I> const&&>);            \
			static_assert(not cjdb::concept<std::remove_reference_t<I> volatile&&>);         \
			static_assert(not cjdb::concept<std::remove_reference_t<I> const volatile&&>);   \
		}
} // namespace cjdb_test

#endif // CJDB_TEST_CONCEPTS_CORE_FUNDAMENTAL_HPP
