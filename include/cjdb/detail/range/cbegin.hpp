// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_RANGE_CBEGIN_HPP
#define CJDB_DETAIL_RANGE_CBEGIN_HPP

#include "cjdb/concepts/callable/invocable.hpp"
#include "cjdb/detail/range/begin.hpp"
#include "cjdb/detail/type_traits/inject_const.hpp"

#include "cjdb/detail/define.hpp"

namespace cjdb::ranges::detail_cbegin {
	struct cbegin_fn {
		template<typename T>
		constexpr auto operator()(T&& t) const
		noexcept(noexcept(begin(static_cast<detail_inject_const::inject_const_t<decltype(t)>>(t))))
		requires invocable<detail_begin::begin_fn, decltype(t)>
		     and invocable<detail_begin::begin_fn, detail_inject_const::inject_const_t<decltype(t)>>
		{
			return begin(static_cast<detail_inject_const::inject_const_t<decltype(t)>>(t));
		}
	};
} // namespace cjdb::ranges::detail_cbegin

namespace cjdb::ranges {
	inline constexpr auto cbegin = detail_cbegin::cbegin_fn{};
} // namespace cjdb::ranges

#include "cjdb/detail/undef.hpp"

#endif // CJDB_DETAIL_RANGE_CBEGIN_HPP
