// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_RANGE_SIZE_HPP
#define CJDB_DETAIL_RANGE_SIZE_HPP

#include "cjdb/concepts/core/integral.hpp"
#include "cjdb/concepts/core/unsigned_integral.hpp"
#include "cjdb/detail/decay_copy.hpp"
#include "cjdb/detail/iterator/integer_like.hpp"
#include "cjdb/detail/range/begin.hpp"
#include "cjdb/detail/range/end.hpp"
#include "cjdb/detail/type_traits/inject_const.hpp"
#include "cjdb/detail/unsigned_like.hpp"
#include "cjdb/range/concepts/refinements.hpp"
#include <type_traits>
#include <utility>

#include "cjdb/detail/define.hpp"

namespace cjdb::ranges {
	/// \brief `disable_­sized_­range` allows use of range types with the library that satisfy but do not
	///       in fact model `sized_­range`.
	/// \note Remarks: Pursuant to [namespace.std], users may specialize `disable_­sized_­range` for
	///       cv-unqualified program-defined types. Such specializations shall be usable in constant
	///       expressions ([expr.const]) and have type const bool.
	///
	template<typename>
	inline constexpr auto disable_sized_range = false;
} // namespace cjdb::ranges

namespace cjdb::ranges::detail_size {
	template<typename T>
	concept member_size =
		not disable_sized_range<std::remove_cv_t<T>> and
		requires(T&& t) {
			std::forward<T>(t).size();
			{ detail_decay_copy::decay_copy(std::forward<T>(t).size()) } -> detail_integer_like::is_integer_like;
		};

	template<typename T>
	void size(T&&) = delete;

	template<typename T>
	concept unqualified_size_impl2 = requires(T t) {
		size(static_cast<T&&>(t));
		{ detail_decay_copy::decay_copy(size(static_cast<T&&>(t))) } -> detail_integer_like::is_integer_like;
	};

	template<typename T>
	concept unqualified_size_impl1 =
		unqualified_size_impl2<T> or unqualified_size_impl2<detail_inject_const::inject_const_t<T>>;

	template<typename T>
	concept unqualified_size =
		not member_size<std::remove_reference_t<T>> and
		not disable_sized_range<std::remove_cvref_t<T>> and
		unqualified_size_impl1<T>;

	template<typename T>
	concept raw_array = std::is_array_v<std::remove_reference_t<T>>;

	template<typename T>
	concept forward_sized_range =
		not raw_array<std::remove_reference_t<T>> and
		not member_size<std::remove_reference_t<T>> and
		not unqualified_size<T> and
		forward_range<T> and
		sized_sentinel_for<sentinel_t<T>, iterator_t<T>>;

	template<typename T>
	inline constexpr auto is_nothrow = requires(T t) {
		{ size(static_cast<T&&>(t)) } noexcept;
	};

	struct size_fn {
		template<raw_array T>
		[[nodiscard]] constexpr unsigned_integral auto operator()(T&&) const noexcept
		{
			return detail_decay_copy::decay_copy(std::extent_v<std::remove_cvref_t<T>>);
		}

		template<typename T>
		requires member_size<std::remove_reference_t<T>>
		[[nodiscard]] constexpr integral auto operator()(T&& t) const
		CJDB_NOEXCEPT_RETURN(
			detail_decay_copy::decay_copy(std::forward<T>(t).size())
		)

		template<typename T>
		requires unqualified_size<T>
		[[nodiscard]] constexpr integral auto operator()(T&& t) const
		noexcept(is_nothrow<T> or is_nothrow<detail_inject_const::inject_const_t<T>>)
		{
			if constexpr (requires { size(std::forward<T>(t)); }) {
				return detail_decay_copy::decay_copy(size(std::forward<T>(t)));
			}
			else {
				return detail_decay_copy::decay_copy(size(std::forward<detail_inject_const::inject_const_t<T>>(t)));
			}
		}

		template<forward_sized_range T>
		[[nodiscard]] constexpr unsigned_integral auto operator()(T&& t) const
		CJDB_NOEXCEPT_RETURN(
			detail_unsigned_like::make_unsigned_like{}(end(t) - begin(t))
		)

		template<typename T>
		void operator()(T&&) const = delete;
	};
} // namespace cjdb::ranges::detail_size

namespace cjdb::ranges {
	inline constexpr auto size = detail_size::size_fn{};
} // namespace cjdb::ranges

#include "cjdb/detail/undef.hpp"

#endif // CJDB_DETAIL_RANGE_SIZE_HPP
