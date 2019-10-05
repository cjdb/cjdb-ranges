// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_FUNCTIONAL_RANGECMP_PARTIAL_GREATER_HPP
#define CJDB_FUNCTIONAL_RANGECMP_PARTIAL_GREATER_HPP

#include "cjdb/concepts/comparison/totally_ordered.hpp"
#include "cjdb/detail/functional/rangecmp/partial_inequality.hpp"
#include "cjdb/functional/rangecmp/greater.hpp"

namespace cjdb::ranges {
	/// \brief Function object for performing comparisons. Applies operator>.
	///
	/// Unlike `ranges::greater`, `partial_greater` stores one object, and takes another as a unary
	/// argument when it is called.
	///
	/// `partial_greater` is a partial function: that is, we provide a one value now, and others
	/// when the function is invoked. In keeping up with the 'you don't pay for what you don't use'
	/// idiom employed by the C++ International Standard, `partial_greater` only stores a value
	/// if it is constructed with an rvalue (this is to prevent issues with lifetime management).
	///
	/// If `partial_greater` is constructed using an lvalue, that lvalue is _referenced_ by the
	/// partial function. Users must be careful to ensure that use of the partial function does not
	/// exceed the lifetime of the original object.
	///
	/// \note This is an extension.
	///
	template<totally_ordered T>
	class partial_greater
	: private detail_partial_inequality::partial_inequality<T, ranges::greater> {
	private:
		using base = detail_partial_inequality::partial_inequality<T, ranges::greater>;
	public:
		using base::base;
		using base::operator();
		using base::value;
		using typename base::is_transparent;
	};

	template<class T>
	partial_greater(T&) -> partial_greater<T const&>;

	template<class T>
	partial_greater(T&&) -> partial_greater<remove_const_t<remove_reference_t<T>>&&>;
} // namespace cjdb::ranges

#endif // CJDB_FUNCTIONAL_RANGECMP_PARTIAL_GREATER_HPP
