// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_RANGE_CDATA_HPP
#define CJDB_DETAIL_RANGE_CDATA_HPP

#include "cjdb/concepts/callable/invocable.hpp"
#include "cjdb/range/access/data.hpp"
#include "cjdb/detail/type_traits/inject_const.hpp"

namespace cjdb::ranges::detail_cdata {
	struct cdata_fn {
		template<typename T>
		constexpr auto operator()(T&& t) const
		noexcept(noexcept(data(static_cast<detail_inject_const::inject_const_t<decltype(t)>>(t))))
		requires invocable<detail_data::data_fn, decltype(t)>
		     and invocable<detail_data::data_fn, detail_inject_const::inject_const_t<decltype(t)>>
		{
			return data(static_cast<detail_inject_const::inject_const_t<decltype(t)>>(t));
		}
	};
} // namespace cjdb::ranges::detail_cdata

namespace cjdb::ranges {
	inline constexpr auto cdata = detail_cdata::cdata_fn{};
} // namespace cjdb::ranges

#endif // CJDB_DETAIL_RANGE_CDATA_HPP
