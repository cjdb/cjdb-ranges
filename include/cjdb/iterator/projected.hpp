// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_ITERATOR_PROJECTED_HPP
#define CJDB_ITERATOR_PROJECTED_HPP

#include "cjdb/iterator/concepts/indirect_callable.hpp"
#include "cjdb/iterator/concepts/readable.hpp"
#include "cjdb/iterator/associated_types.hpp"
#include <type_traits>

namespace cjdb {
	/// \brief `projected` is used to constrain algorithms that accept callable objects and
	///        projections ([defns.projection]).
	///
	/// It combines a `readable` type `I` and a callable object type `Proj` into a new `readable`
	/// type whose `reference` type is the result of applying `Proj` to the `iter_­reference_­t` of
	/// `I`.
	///
	template<readable I, indirectly_regular_unary_invocable<I> Proj>
	struct projected {
		using value_type = std::remove_cvref_t<indirect_result_t<Proj&, I>>;
		indirect_result_t<Proj&, I> operator*() const;              // not defined
	};

	template<weakly_incrementable I, class Proj>
	struct incrementable_traits<projected<I, Proj>> {
		using difference_type = iter_difference_t<I>;
	};
} // namespace cjdb

#endif // CJDB_ITERATOR_PROJECTED_HPP
