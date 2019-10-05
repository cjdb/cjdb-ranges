// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_CONCEPTS_CORE_DERIVEDFROM_HPP
#define CJDB_CONCEPTS_CORE_DERIVEDFROM_HPP

#include "cjdb/type_traits/type_traits.hpp"

namespace cjdb {
	/// \brief `derived_from<Derived, Base>` is satisfied if and only if `Derived` is publicly and
	///        unambiguously derived from `Base`, or `Derived` and `Base` are the same class type
	///        ignoring cv-qualifiers
	/// \see [concept.derivedfrom]
	///
	template<class Derived, class Base>
	concept derived_from =
		is_base_of_v<Base, Derived> and
		is_convertible_v<const volatile Derived*, const volatile Base*>;
} // namespace cjdb

#endif // CJDB_CONCEPTS_CORE_DERIVEDFROM_HPP
