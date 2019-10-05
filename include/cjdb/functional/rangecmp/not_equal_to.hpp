// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_FUNCTIONAL_RANGECMP_NOT_EQUAL_TO_HPP
#define CJDB_DETAIL_FUNCTIONAL_RANGECMP_NOT_EQUAL_TO_HPP

#include "cjdb/concepts/comparison/equality_comparable.hpp"
#include "cjdb/functional/rangecmp/equal_to.hpp"
#include "cjdb/type_traits/is_nothrow.hpp"
#include "cjdb/type_traits/type_traits.hpp"
#include <utility>

namespace cjdb::ranges {
	/// \brief Function object for performing comparisons. Applies operator!=.
	///
	struct not_equal_to {
		/// \returns `true` if `t` is not equal to `u`, `false` otherwise.
		///
		template<class T, equality_comparable_with<T> U>
		constexpr bool operator()(T&& t, U&& u) const noexcept(is_nothrow_equality_comparable<T, U>)
		{
			return not equal_to{}(std::forward<T>(t), std::forward<U>(u));
		}

		using is_transparent = true_type;
	};
} // namespace cjdb::ranges

#endif // CJDB_DETAIL_FUNCTIONAL_RANGECMP_NOT_EQUAL_TO_HPP
