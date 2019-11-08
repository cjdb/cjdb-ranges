// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_RANGE_CEND_HPP
#define CJDB_DETAIL_RANGE_CEND_HPP

#include "cjdb/concepts/callable/invocable.hpp"
#include "cjdb/detail/range/end.hpp"
#include "cjdb/detail/type_traits/inject_const.hpp"

#include "cjdb/detail/define.hpp"

namespace cjdb::ranges::detail_cend {
	struct cend_fn {
		template<typename T>
		constexpr auto operator()(T&& t) const
		noexcept(noexcept(end(static_cast<detail_inject_const::inject_const_t<decltype(t)>>(t))))
		requires invocable<detail_end::end_fn, decltype(t)>
		     and invocable<detail_end::end_fn, detail_inject_const::inject_const_t<decltype(t)>>
		{
			return end(static_cast<detail_inject_const::inject_const_t<decltype(t)>>(t));
		}
	};
} // namespace cjdb::ranges::detail_cend

namespace cjdb::ranges {
	inline constexpr auto cend = detail_cend::cend_fn{};
} // namespace cjdb::ranges

#include "cjdb/detail/undef.hpp"

#endif // CJDB_DETAIL_RANGE_CEND_HPP
