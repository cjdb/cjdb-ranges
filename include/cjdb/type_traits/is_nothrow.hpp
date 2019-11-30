// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TYPE_TRAITS_IS_NOTHROW_HPP
#define CJDB_TYPE_TRAITS_IS_NOTHROW_HPP

#include "cjdb/concepts/comparison/equality_comparable.hpp"
#include "cjdb/concepts/comparison/totally_ordered.hpp"
#include "cjdb/concepts/comparison/three_way_comparable.hpp"

#include <version>

namespace cjdb {
	template<typename T, typename U>
	inline constexpr auto is_nothrow_equality_comparable = requires(T&& t, U&& u) {
		{std::forward<T>(t) == std::forward<U>(u)} noexcept;
		{std::forward<T>(t) != std::forward<U>(u)} noexcept;

		{std::forward<U>(u) == std::forward<T>(t)} noexcept;
		{std::forward<U>(u) != std::forward<T>(t)} noexcept;
	};

	template<typename T, totally_ordered_with<T> U>
	inline constexpr auto is_nothrow_totally_ordered =
		is_nothrow_equality_comparable<T, U> and
		requires(T&& t, U&& u) {
			{std::forward<T>(t) <  std::forward<U>(u)} noexcept;
			{std::forward<T>(t) >  std::forward<U>(u)} noexcept;
			{std::forward<T>(t) <= std::forward<U>(u)} noexcept;
			{std::forward<T>(t) >= std::forward<U>(u)} noexcept;

			{std::forward<U>(u) <  std::forward<T>(t)} noexcept;
			{std::forward<U>(u) >  std::forward<T>(t)} noexcept;
			{std::forward<U>(u) <= std::forward<T>(t)} noexcept;
			{std::forward<U>(u) >= std::forward<T>(t)} noexcept;
		};

	#if defined(__cpp_lib_three_way_comparison) and __cpp_lib_three_way_comparison >= 201907
		template<typename T, three_way_comparable_with<T> U>
		inline constexpr auto is_nothrow_three_way_comparable =
			is_nothrow_totally_ordered<T, U> and
			requires(T&& t, U&& u) {
				{std::forward<T>(t) <=> std::forward<U>(u)} noexcept;
				{std::forward<U>(u) <=> std::forward<T>(t)} noexcept;
			};
	#endif // __cpp_lib_three_way_comparison
} // namespace cjdb

#endif // CJDB_TYPE_TRAITS_IS_NOTHROW_HPP
