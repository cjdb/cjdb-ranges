// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_ITERATOR_LEGACY_ITERATOR_WRAPPER_HPP
#define CJDB_TEST_ITERATOR_LEGACY_ITERATOR_WRAPPER_HPP

#include "cjdb/detail/iterator/legacy_iterator.hpp"

namespace cjdb_test {
	template<typename I>
	inline constexpr auto has_arrow = requires(I& i) {
		i.operator->();
	};

	/// \brief Extension point for `legacy_iterator_wrapper` to support `operator->`.
	///
	template<typename I>
	struct arrow_extension {};

	/// \brief Wrapper around a legacy C++ iterator to give it a minimal interface.
	/// \tparam I       Legacy C++ iterator type.
	/// \tparam Args... A series of templates that allow for extensions to `legacy_iterator`. For
	///                 example, legacy input iterators require `value_type` and `difference_type` as
	///                 members; legacy iterators do not (to support them in `legacy_iterator` would
	///                 break minimal interface goal).
	///                 Adding support for a these members is done by creating passing class
	///                 templates that can be instantiated with `I` as the only parameter: the types
	///                 are then available for use.
	///
	template<cjdb::detail_iterator_associated_types::legacy_iterator I, template<typename> typename... Args>
	class legacy_iterator : public Args<I>... {
	public:
		constexpr explicit legacy_iterator(I i)
		: base_{std::move(i)}
		{}

		constexpr decltype(auto) operator*() const { return *base_; }

		constexpr decltype(auto) operator->() const
		requires cjdb::derived_from<legacy_iterator, arrow_extension<I>> and has_arrow<I>
		{ return this->base().operator->(); }

		constexpr legacy_iterator& operator++()
		{
			++base_;
			return *this;
		}

		constexpr legacy_iterator operator++(int)
		{
			auto temp = *this;
			++*this;
			return temp;
		}
	protected:
		[[nodiscard]] constexpr I& base() { return base_; }
		[[nodiscard]] constexpr I const& base() const { return base_; }
	private:
		I base_;
	};

	/// \brief Wrapper around a legacy C++ input iterator to give it a minimal interface.
	/// \tparam I       Legacy C++ input iterator type.
	/// \tparam Args... A series of templates that allow for extensions to `legacy_iterator`. For
	///                 example, legacy input iterators require `value_type` and `difference_type` as
	///                 members; legacy iterators do not (to support them in `legacy_iterator` would
	///                 break minimal interface goal).
	///                 Adding support for a these members is done by creating passing class
	///                 templates that can be instantiated with `I` as the only parameter: the types
	///                 are then available for use.
	///
	template<cjdb::detail_iterator_associated_types::legacy_input_iterator I, template<typename> typename... Args>
	class legacy_input_iterator : public legacy_iterator<I, Args...> {
	public:
		using legacy_iterator<I, Args...>::legacy_iterator;

		static_assert((requires { typename Args<I>::value_type; } or ...));
		static_assert((requires { typename Args<I>::difference_type; } or ...));

		constexpr bool operator==(legacy_input_iterator const& other) const
		{ return this->base() == other.base(); }

		constexpr bool operator!=(legacy_input_iterator const& other) const
		{ return not (*this == other); }

		constexpr legacy_input_iterator& operator++()
		{
			++static_cast<legacy_iterator<I, Args...>&>(*this);
			return *this;
		}

		constexpr legacy_input_iterator operator++(int)
		{
			return legacy_input_iterator{static_cast<legacy_iterator<I, Args...>&>(*this)};
		}
	};

	/// \brief Wrapper around a legacy C++ forward iterator to give it a minimal interface.
	/// \tparam I       Legacy C++ forward iterator type.
	/// \tparam Args... A series of templates that allow for extensions to `legacy_iterator`. For
	///                 example, legacy input iterators require `value_type` and `difference_type` as
	///                 members; legacy iterators do not (to support them in `legacy_iterator` would
	///                 break minimal interface goal).
	///                 Adding support for a these members is done by creating passing class
	///                 templates that can be instantiated with `I` as the only parameter: the types
	///                 are then available for use.
	///
	template<cjdb::detail_iterator_associated_types::legacy_forward_iterator I,
	         template<typename> typename... Args>
	class legacy_forward_iterator : public legacy_input_iterator<I, Args...> {
	public:
		constexpr legacy_forward_iterator()
		: legacy_input_iterator<I, Args...>{I{}}
		{}

		constexpr legacy_forward_iterator& operator++()
		{
			++static_cast<legacy_iterator<I, Args...>&>(*this);
			return *this;
		}

		constexpr legacy_forward_iterator operator++(int)
		{
			return legacy_forward_iterator{static_cast<legacy_iterator<I, Args...>&>(*this)};
		}
	};

	/// \brief Wrapper around a legacy C++ bidirectional iterator to give it a minimal interface.
	/// \tparam I       Legacy C++ bidirectional iterator type.
	/// \tparam Args... A series of templates that allow for extensions to `legacy_iterator`. For
	///                 example, legacy input iterators require `value_type` and `difference_type` as
	///                 members; legacy iterators do not (to support them in `legacy_iterator` would
	///                 break minimal interface goal).
	///                 Adding support for a these members is done by creating passing class
	///                 templates that can be instantiated with `I` as the only parameter: the types
	///                 are then available for use.
	///
	template<cjdb::detail_iterator_associated_types::legacy_bidirectional_iterator I,
	         template<typename> typename... Args>
	class legacy_bidirectional_iterator : public legacy_forward_iterator<I, Args...> {
	public:
		using legacy_forward_iterator<I, Args...>::legacy_forward_iterator;

		constexpr legacy_bidirectional_iterator& operator++()
		{
			++static_cast<legacy_iterator<I, Args...>&>(*this);
			return *this;
		}

		constexpr legacy_bidirectional_iterator operator++(int)
		{
			return legacy_input_iterator{static_cast<legacy_iterator<I, Args...>&>(*this)};
		}

		constexpr legacy_bidirectional_iterator& operator--()
		{
			--this->base();
			return *this;
		}

		constexpr legacy_bidirectional_iterator operator--(int)
		{
			auto temp = *this;
			--*this;
			return temp;
		}
	};

	/// \brief Wrapper around a legacy C++ random-access iterator to give it a minimal interface.
	/// \tparam I       Legacy C++ random-access iterator type.
	/// \tparam Args... A series of templates that allow for extensions to `legacy_iterator`. For
	///                 example, legacy input iterators require `value_type` and `difference_type` as
	///                 members; legacy iterators do not (to support them in `legacy_iterator` would
	///                 break minimal interface goal).
	///                 Adding support for a these members is done by creating passing class
	///                 templates that can be instantiated with `I` as the only parameter: the types
	///                 are then available for use.
	///
	template<cjdb::detail_iterator_associated_types::legacy_random_access_iterator I,
	         template<typename> typename... Args>
	class legacy_random_access_iterator : public legacy_bidirectional_iterator<I, Args...> {
	public:
		using legacy_bidirectional_iterator<I, Args...>::legacy_bidirectional_iterator;
		using typename legacy_bidirectional_iterator<I, Args...>::difference_type;

		constexpr legacy_random_access_iterator& operator++()
		{
			++static_cast<legacy_iterator<I, Args...>&>(*this);
			return *this;
		}

		constexpr legacy_random_access_iterator operator++(int)
		{
			return legacy_input_iterator{static_cast<legacy_iterator<I, Args...>&>(*this)};
		}

			constexpr legacy_random_access_iterator& operator--()
		{
			++static_cast<legacy_iterator<I, Args...>&>(*this);
			return *this;
		}

		constexpr legacy_random_access_iterator operator--(int)
		{
			return legacy_input_iterator{static_cast<legacy_iterator<I, Args...>&>(*this)};
		}

		constexpr legacy_random_access_iterator& operator+=(difference_type const n)
		{
			this->base() += n;
			return *this;
		}

		constexpr legacy_random_access_iterator& operator-=(difference_type const n)
		{ return *this += -n; }

		friend constexpr legacy_random_access_iterator
		operator+(legacy_random_access_iterator x, difference_type const y)
		{ return x += y; }

		friend constexpr legacy_random_access_iterator
		operator+(difference_type const y, legacy_random_access_iterator x)
		{ return x + y; }

		friend constexpr legacy_random_access_iterator
		operator-(legacy_random_access_iterator x, difference_type const y)
		{ return x -= y; }

		constexpr difference_type operator-(legacy_random_access_iterator const& other) const
		{ return this->base() - other.base(); }

		constexpr decltype(auto) operator[](difference_type const n) const
		{ return *(*this + n); }

		constexpr bool operator<(legacy_random_access_iterator const& other) const
		{ return this->base() < other.base(); }

		constexpr bool operator>(legacy_random_access_iterator const& other) const
		{ return other < *this; }

		constexpr bool operator<=(legacy_random_access_iterator const& other) const
		{ return not (other < *this); }

		constexpr bool operator>=(legacy_random_access_iterator const& other) const
		{ return not (*this < other); }
	};

	/// \brief Minimum extension point for `legacy_input_iterator`.
	///
	template<typename I>
	struct minimal_extension {
		using difference_type = typename cjdb::incrementable_traits<I>::difference_type;
		using value_type = typename cjdb::readable_traits<I>::value_type;
	};

	/// \brief Extension point for reference member.
	///
	template<typename I>
	struct reference_extension {
		using reference = typename I::reference;
	};

	/// \brief Extension point for pointer member.
	///
	template<typename I>
	struct pointer_extension {
		using pointer = typename I::pointer;
	};

	/// \brief Extension point to indicate no extension points.
	/// \note This is used for function overloading when there isn't a better name for two overloads.
	///
	template<typename I>
	struct empty_extension {};
} // namespace cjdb_test

#endif // CJDB_TEST_ITERATOR_LEGACY_ITERATOR_WRAPPER_HPP
