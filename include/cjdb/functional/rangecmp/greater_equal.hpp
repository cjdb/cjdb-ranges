// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_FUNCTIONAL_RANGECMP_GREATER_EQUAL_HPP
#define CJDB_DETAIL_FUNCTIONAL_RANGECMP_GREATER_EQUAL_HPP

#include "cjdb/concepts/comparison/totally_ordered.hpp"
#include "cjdb/functional/rangecmp/less.hpp"
#include "cjdb/type_traits/is_nothrow.hpp"
#include "cjdb/type_traits/type_traits.hpp"
#include <utility>

#include "cjdb/detail/define.hpp"

namespace cjdb::ranges {
	/// \brief Function object for performing comparisons. Applies operator>=.
	///
	struct greater_equal {
		/// \returns `true` if `t` is not less than `u`, `false` otherwise.
		///
		template<class T, totally_ordered_with<T> U>
		constexpr bool operator()(T&& t, U&& u) const noexcept(is_nothrow_totally_ordered<T, U>)
		{
			return not less{}(std::forward<T>(t), std::forward<U>(u));
		}

		using is_transparent = true_type;
	};
} // namespace cjdb::ranges

#include "cjdb/detail/undef.hpp"

#endif // CJDB_DETAIL_FUNCTIONAL_RANGECMP_GREATER_EQUAL_HPP
