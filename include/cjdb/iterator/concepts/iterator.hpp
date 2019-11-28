// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_ITERATOR_CONCEPTS_ITERATOR_HPP
#define CJDB_ITERATOR_CONCEPTS_ITERATOR_HPP

#include "cjdb/concepts/comparison/totally_ordered.hpp"
#include "cjdb/concepts/core/derived_from.hpp"
#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/concepts/object/semiregular.hpp"
#include "cjdb/detail/concepts/comparison/weakly_equality_comparable_with.hpp"
#include "cjdb/detail/iterator/incrementable_traits.hpp"
#include "cjdb/detail/iterator/iter_traits.hpp"
#include "cjdb/detail/iterator/readable_traits.hpp"
#include "cjdb/detail/iterator/reference.hpp"
#include "cjdb/iterator/concepts/incrementable.hpp"
#include "cjdb/iterator/concepts/readable.hpp"
#include "cjdb/iterator/concepts/writable.hpp"

#include <memory>
#include <iterator>
#include <type_traits>

namespace cjdb {
	/// \brief The `input_or_output_iterator` concept forms the basis of the iterator concept
	///        taxonomy; every iterator models `input_or_output_iterator`.
	///
	/// This concept specifies operations for dereferencing and incrementing an iterator. Most
	/// algorithms will require additional operations to compare iterators with sentinels, to read
	/// (input iterators) or write (output iterators) values, or to provide a richer set of iterator
	/// movements (forward iterators, bidirectional iterators, and random-access iterators).
	/// \note Unlike the _Cpp17Iterator_ requirements, the `input_or_output_iterator` concept does
	///       not require copyability.
	///
	template<typename I>
	concept input_or_output_iterator =
		requires(I i) {
			{ *i } -> detail_iterator_reference::can_reference;
		} and
		weakly_incrementable<I>;

	/// \brief The `sentinel_for` concept specifies the relationship between an
	///        `input_or_output_iterator` type and a `semiregular` type whose values denote a range.
	///
	/// **Axiom:**
	/// Let `s` and `i` be values of type `S` and `I` such that `[i, s)` denotes a range. Types `S`
	/// and `I` model `sentinel_for<S, I>` only if:
	///    * `i == s` is well defined.
	///    * If `bool(i != s)`, then `i` is dereferenceable and `[++i, s)` denotes a range.
	///
	/// The domain of `==` is not static. Given an iterator `i` and sentinel `s` such that `[i, s)`
	/// denotes a range and `i != s`, `i` and `s` are not required to continue to denote a range
	/// after incrementing any other iterator equal to `i`. Consequently, `i == s` is no longer
	/// required to be well-defined.
	///
	template<typename S, typename I>
	concept sentinel_for =
		semiregular<S> and
		input_or_output_iterator<I> and
		detail_weakly_equality_comparable_with::weakly_equality_comparable_with<S, I>;

	/// \brief `disable_sized_sentinel` allows use of sentinels and iterators with the library that
	///        satisfy but do not in fact model `sized_sentinel_for`.
	///
	/// Users may specialise `disable_sized_sentinel` for cv-unqualified non-array object types `S`
	/// and `I` if `S` and/or `I` is a program-defined type. Such specializations shall be usable in
	/// constant expressions ([expr.const]) and have type `const bool`.
	/// \note The `sized_sentinel_for` concept is modeled by pairs of `random_access_iterators` and
	///       by counted iterators and their sentinels.
	///
	template<typename S, typename I>
	inline constexpr auto disable_sized_sentinel = false;

	/// \brief The `sized_sentinel_for` concept specifies requirements on an
	///        `input_or_output_iterator` and a corresponding `sentinel_for` that allow the use of
	///        `operator-` to compute the distance between them in constant time.
	///
	/// **Axiom:**
	/// Let `i` be an iterator of type `I`, and `s` a sentinel of type `S` such that `[i, s)` denotes
	/// a range. Let `N` be the smallest number of applications of `++i` necessary to make
	/// `bool(i == s)` be `true`. `S` and `I` model `sized_sentinel_for<S, I>` only if
	///    * If _N_ is representable by `iter_difference_t<I>`, then `s - i` is well-defined and
	///      equals _N_.
	///    * If _-N_ is representable by `iter_difference_t<I>`, then `i - s` is well-defined and
	///      equals _-N_.
	///
	template<typename S, typename I>
	concept sized_sentinel_for =
		sentinel_for<S, I> and
		not disable_sized_sentinel<std::remove_cv_t<S>, std::remove_cv_t<I>> and
		requires(I const& i, S const& s) {
			{ s - i } -> same_as<iter_difference_t<I>>;
			{ i - s } -> same_as<iter_difference_t<I>>;
		};

	/// \brief The `input_iterator` concept defines requirements for a type whose referenced values
	///        can be read (from the requirement for `readable`) and which can be both pre- and
	///        post-incremented.
	/// \note Unlike the _Cpp17InputIterator_ requirements, the `input_iterator` concept does not
	///       need equality comparison since iterators are typically compared to sentinels.
	///
	template<typename I>
	concept input_iterator =
		input_or_output_iterator<I> and
		readable<I> and
		requires { typename detail_iter_traits::iter_concept_t<I>; } and
		derived_from<detail_iter_traits::iter_concept_t<I>, std::input_iterator_tag>;

	/// \brief The `output_iterator` concept defines requirements for a type that can be used to
	///        write values (from the requirement for writable) and which can be both pre- and
	///        post-incremented.
	///
	/// \pre **Axiom:**
	/// Let `E` be an expression such that `decltype((E))` is `T`, and let `i` be a dereferenceable
	/// object of type `I`. `I` and `T` model `output_iterator<I, T>` only if `*i++ = E;` has effects
	/// equivalent to:
	/// ```cpp
	/// *i = E;
	/// ++i;
	/// ```
	/// \note Output iterators are not required to model `equality_comparable`.
	/// \note Algorithms on output iterators should never attempt to pass through the same iterator
	///       twice. They should be single-pass algorithms.
	///
	template<typename I, typename T>
	concept output_iterator =
		input_or_output_iterator<I> and
		writable<I, T> and
		requires(I i, T&& t) {
			*i++ = std::forward<T>(t); // not required to be equality-preserving
		};

	/// \brief The `forward_iterator` concept adds copyability, equality comparison, and the
	///        multi-pass guarantee, specified below.
	///
	/// \pre **Axiom:**
	/// The domain of `==` for forward iterators is that of iterators over the same underlying
	/// sequence. However, value-initialized iterators of the same type may be compared and shall
	/// compare equal to other value-initialized iterators of the same type.
	///
	/// \pre **Axiom:**
	/// Pointers and references obtained from a forward iterator into a range `[i, s)` shall remain
	/// valid while `[i, s)` continues to denote a range.
	///
	/// \pre **Axiom:**
	/// Two dereferenceable iterators `a` and `b` of type `X` offer the _multi-pass guarantee_ if:
	///    * `a == b` implies `++a == ++b` and
	///    * The expression `((void)[](X x){++x;}(a), *a)` is equivalent to the expression `*a`.
	///
	/// \note Value-initialized iterators behave as if they refer past the end of the same empty
	///       sequence.
	/// \note The requirement that `a == b` implies `++a == ++b` and the removal of the restrictions
	///       on the number of assignments through a mutable iterator (which applies to output
	///       iterators) allow the use of multi-pass one-directional algorithms with forward
	///       iterators.
	/// \note Algorithms in this library use `CJDB_ASSERT(((void)[](X x){++x;}(a), *a) == *a)` as a
	///       pre-condition if `iter_reference_t<I>` models `equality_comparable`. This will
	///       negatively impact debug performance, but may lead to improved performance in certain
	///       optimised builds.
	///
	template<typename I>
	concept forward_iterator =
		input_iterator<I> and
		derived_from<detail_iter_traits::iter_concept_t<I>, std::forward_iterator_tag> and
		incrementable<I> and
		sentinel_for<I, I>;

	/// \brief The `bidirectional_iterator` concept adds the ability to move an iterator backward as
	///        well as forward.
	///
	/// \pre **Axiom:**
	/// A bidirectional iterator `r` is decrementable if and only if there exists some `q` such that
	/// `++q == r`. Decrementable iterators `r` shall be in the domain of the expressions `--r` and
	/// `r--`.
	///
	/// \pre **Axiom:**
	/// Let `a` and `b` be equal objects of type `I`. `I` models `bidirectional_iterator` only if:
	///    * If `a` and `b` are decrementable, then all of the following are true:
	///       * `std::addressof(--a) == std::addressof(a)`
	///       * `bool(a-- == b)`
	///       * after evaluating both `a--` and `--b`, `bool(a == b)` is still `true`
	///       * `bool(++(--a) == b)`
	///    * If `a` and `b` are incrementable, then `bool(--(++a) == b)`.
	/// \note Algorithms in this library check the axioms using `CJDB_ASSERT` when the pre-conditions
	///       are satisfied. This will negatively impact debug performance, but may lead to improved
	///       performance in certain optimised builds.
	///
	template<typename I>
	concept bidirectional_iterator =
		forward_iterator<I> and
		derived_from<detail_iter_traits::iter_concept_t<I>, std::bidirectional_iterator_tag> and
		requires(I i) {
			{ --i } -> same_as<I&>;
			{ i-- } -> same_as<I>;
		};

	/// \brief The `random_access_iterator` concept adds support for constant-time advancement with
	///        `+=`, `+`, `-=`, and `-`, as well as the computation of distance in constant time with
	///        `-`.
	///
	/// Random access iterators also support array notation via subscripting.
	///
	/// **Axiom:**
	/// Let `a` and `b` be valid iterators of type `I` such that `b` is reachable from `a` after `n`
	/// applications of `++a`, let `D` be `iter_difference_t<I>`, and let `n` denote a value of type
	/// `D`. `I` models `random_access_iterator` only if
	///    * `(a += n)` is equal to `b`.
	///    * `std::addressof(a += n)` is equal to `std::addressof(a)`.
	///    * `(a + n)` is equal to `(a += n)`.
	///    * For any two positive values `x` and `y` of type `D`, if `(a + D(x + y))` is valid, then
	///      `(a + D(x + y))` is equal to `((a + x) + y)`.
	///    * `(a + D(0))` is equal to `a`.
	///    * If `(a + D(n - 1))` is valid, then `(a + n)` is equal to `++(a + D(n - 1))`.
	///    * `(b += -n)` is equal to a.
	///    * `(b -= n)` is equal to a.
	///    * `std::addressof(b -= n)` is equal to `std::addressof(b)`.
	///    * `(b - n)` is equal to `(b -= n)`.
	///    * If `b` is dereferenceable, then `a[n]` is valid and is equal to `*b`.
	///    * `bool(a <= b)` is `true`.
	/// \note Algorithms in this library check the axioms using `CJDB_ASSERT` when the pre-conditions
	///       are satisfied. This will negatively impact debug performance, but may lead to improved
	///       performance in certain optimised builds.
	///
	template<typename I>
	concept random_access_iterator =
		bidirectional_iterator<I> and
		derived_from<detail_iter_traits::iter_concept_t<I>, std::random_access_iterator_tag> and
		totally_ordered<I> and
		sized_sentinel_for<I, I> and
		requires(I i, I const j, iter_difference_t<I> const n) {
			{ i += n } -> same_as<I&>;
			{ j +  n } -> same_as<I>;
			{ n +  j } -> same_as<I>;
			{ i -= n } -> same_as<I&>;
			{ j -  n } -> same_as<I>;
			{  j[n]  } -> same_as<iter_reference_t<I>>;
		};

	/// \brief The `contiguous_iterator` concept provides a guarantee that the denoted elements are
	///        stored contiguously in memory.
	///
	/// \pre **Axiom:**
	/// Let `a` and `b` be dereferenceable iterators and `c` be a non-dereferenceable iterator of
	/// type `I` such that `b` is reachable from `a` and `c` is reachable from `b`, and let `D` be
	/// `iter_difference_t<I>`. The type `I` models `contiguous_iterator` only if
	///    * `std::to_address(a) == std::addressof(*a)`,
	///    * `std::to_address(b) == std::to_address(a) + D(b - a)`, and
	///    * `std::to_address(c) == to_address(a) + D(c - a)`.
	/// \note Algorithms in this library check the axioms using `CJDB_ASSERT` when the pre-conditions
	///       are satisfied. This will negatively impact debug performance, but may lead to improved
	///       performance in certain optimised builds.
	///
	template<typename I>
	concept contiguous_iterator =
		random_access_iterator<I> and
		derived_from<detail_iter_traits::iter_concept_t<I>, contiguous_iterator_tag> and
		std::is_lvalue_reference_v<iter_reference_t<I>> and
		same_as<iter_value_t<I>, std::remove_cvref_t<iter_reference_t<I>>> and
		requires(I const& i) {
			{ std::to_address(i) } -> same_as<std::add_pointer_t<iter_reference_t<I>>>;
		};
} // namespace cjdb

#endif // CJDB_ITERATOR_CONCEPTS_ITERATOR_HPP
