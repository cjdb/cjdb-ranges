#ifndef CJDB_ITERATOR_ADAPTORS_REVERSE_ITERATOR_HPP
#define CJDB_ITERATOR_ADAPTORS_REVERSE_ITERATOR_HPP

#include "cjdb/concepts/core/derived_from.hpp"
#include "cjdb/concepts/compare.hpp"
#include "cjdb/detail/iterator/legacy_iterator.hpp"
#include "cjdb/iterator/associated_types.hpp"
#include "cjdb/iterator/concepts/iterator.hpp"
#include "cjdb/iterator/reference.hpp"
#include "cjdb/type_traits/expose_type.hpp"
#include <iterator>
#include <type_traits>
#include <utility>

#include "cjdb/detail/define.hpp"

namespace cjdb::detail_reverse_iterator {
	template<typename>
	struct iterator_concept {
		using type = std::bidirectional_iterator_tag;
	};

	template<random_access_iterator I>
	struct iterator_concept<I> {
		using type = std::random_access_iterator_tag;
	};

	template<typename T>
	struct iterator_category {
		using type = T;
	};

	template<derived_from<std::random_access_iterator_tag> T>
	struct iterator_category<T> {
		using type = std::random_access_iterator_tag;
	};

	template<typename I>
	concept has_arrow = std::is_pointer_v<I> or requires(I const i) { i.operator->(); };

	template<typename I>
	concept bidirectional_sympathetic =
		bidirectional_iterator<I> or
		detail_iterator_associated_types::legacy_bidirectional_iterator<I>;

	template<typename I>
	concept random_access_sympathetic =
		bidirectional_sympathetic<I> and
		(random_access_iterator<I> or
		 detail_iterator_associated_types::legacy_random_access_iterator<I>);
} // namespace cjdb::detail_reverse_iterator

namespace cjdb {
	template<detail_reverse_iterator::bidirectional_sympathetic I>
	class reverse_iterator {
	public:
		using iterator_type = I;
		using iterator_concept = _t<detail_reverse_iterator::iterator_concept<I>>;
		using iterator_category = _t<detail_reverse_iterator::iterator_category<typename cjdb::iterator_traits<I>::iterator_category>>;
		using value_type = iter_value_t<I>;
		using difference_type = iter_difference_t<I>;
		using pointer = typename iterator_traits<I>::pointer;
		using reference = iter_reference_t<I>;

		constexpr reverse_iterator() = default;

		constexpr explicit reverse_iterator(I x) noexcept(std::is_nothrow_move_constructible_v<I>)
		: current_{std::move(x)}
		{}

		template<typename U> // DEFECT?
		requires constructible_from<I, U>
		constexpr reverse_iterator(reverse_iterator<U> const& u) // NOLINT(google-explicit-constructor)
		: current_{u.current_}
		{}

		template<typename U> // DEFECT?
		requires assignable_from<I, U>
		constexpr reverse_iterator& operator=(reverse_iterator<U> const& u)
		noexcept(std::is_nothrow_assignable_v<I, U>)
		{
			current_ = u.base();
			return *this;
		}

		[[nodiscard]] constexpr I base() const
		CJDB_NOEXCEPT_RETURN(
			current_
		)

		[[nodiscard]] constexpr reference operator*() const noexcept
		{
			if constexpr (detail_reverse_iterator::random_access_sympathetic<I>) { // NOLINT(bugprone-branch-clone)
				return current_ - 1;
			}
			else {
				I temp = current_;
				--temp;
				return temp;
			}
		}

		[[nodiscard]] constexpr pointer operator->() const
		requires detail_reverse_iterator::has_arrow<I>
		{
			using std::prev;
			if constexpr (std::is_pointer_v<I>) { // NOLINT(bugprone-branch-clone)
				return prev(current_);
			}
			else {
				return prev(current_).operator->();
			}
		}

		constexpr reverse_iterator& operator++() noexcept(noexcept(--current_))
		{
			--current_;
			return *this;
		}

		[[nodiscard]] constexpr reverse_iterator operator++(int)
		noexcept(std::is_nothrow_copy_constructible_v<I> and noexcept(operator++()))
		{
			auto temp = *this;
			++*this;
			return temp;
		}

		constexpr reverse_iterator& operator--() noexcept(noexcept(++current_))
		{
			++current_;
			return *this;
		}

		[[nodiscard]] constexpr reverse_iterator operator--(int)
		noexcept(std::is_nothrow_copy_constructible_v<I> and noexcept(operator--()))
		{
			auto temp = *this;
			--*this;
			return temp;
		}

		[[nodiscard]] constexpr reverse_iterator operator+(difference_type n) const
		noexcept(noexcept(std::declval<I&>() - n))
		requires detail_reverse_iterator::random_access_sympathetic<I>
		{
			return current_ - n;
		}

		constexpr reverse_iterator& operator+=(difference_type n) noexcept(noexcept(current_ -= n))
		{
			current_ -= n;
			return *this;
		}

		[[nodiscard]] constexpr reverse_iterator operator-(difference_type n) const
		noexcept(noexcept(std::declval<I&>() + n))
		requires detail_reverse_iterator::random_access_sympathetic<I>
		{
			return current_ + n;
		}

		constexpr reverse_iterator& operator-=(difference_type n) noexcept(noexcept(current_ += n))
		{
			current_ += n;
			return *this;
		}

		[[nodiscard]] constexpr decltype(auto) operator[](difference_type n) const
		noexcept(noexcept(std::declval<I&>()[n]))
		requires detail_reverse_iterator::random_access_sympathetic<I>
		{
			return current_[-n-1];
		}

		[[nodiscard]] constexpr friend
		iter_rvalue_reference_t<I> iter_move(const reverse_iterator& i)
		noexcept(std::is_nothrow_copy_constructible_v<I> and
		         noexcept(ranges::iter_move(--std::declval<I&>())))
		{
			auto tmp = i.base();
			return ranges::iter_move(--tmp);
		}

		template<indirectly_swappable<I> I2>
		constexpr friend void iter_swap(const reverse_iterator& x, const reverse_iterator<I2>& y)
		noexcept(std::is_nothrow_copy_constructible_v<I> and
		         std::is_nothrow_copy_constructible_v<I2> and
		         noexcept(ranges::iter_swap(--std::declval<I&>(), --std::declval<I2&>())))
		{
			auto x_temp = x.base();
			auto y_temp = y.base();
			ranges::iter_swap(--x_temp, --y_temp);
		}

		template<sentinel_for<I> I2>
		[[nodiscard]] constexpr friend
		bool operator==(reverse_iterator const&, reverse_iterator<I2> const&) = default;

		template<totally_ordered_with<I> I2>
		requires (detail_reverse_iterator::random_access_sympathetic<I> and
		          detail_reverse_iterator::random_access_sympathetic<I2>)
		[[nodiscard]] constexpr friend
		bool operator<(reverse_iterator const& x, reverse_iterator<I2> const& y)
		CJDB_NOEXCEPT_RETURN(
			x.base() > y.base()
		)

		template<totally_ordered_with<I> I2>
		requires detail_reverse_iterator::random_access_sympathetic<I> and
		         detail_reverse_iterator::random_access_sympathetic<I2>
		[[nodiscard]] constexpr friend
		bool operator>(reverse_iterator const& x, reverse_iterator<I2> const& y)
		CJDB_NOEXCEPT_RETURN(
			y < x
		)

		template<totally_ordered_with<I> I2>
		requires detail_reverse_iterator::random_access_sympathetic<I> and
		         detail_reverse_iterator::random_access_sympathetic<I2>
		[[nodiscard]] constexpr friend
		bool operator<=(reverse_iterator const& x, reverse_iterator<I2> const& y)
		CJDB_NOEXCEPT_RETURN(
			not (x < y)
		)

		template<totally_ordered_with<I> I2>
		requires detail_reverse_iterator::random_access_sympathetic<I> and
		         detail_reverse_iterator::random_access_sympathetic<I2>
		[[nodiscard]] constexpr friend
		bool operator>=(reverse_iterator const& x, reverse_iterator<I2> const& y)
		CJDB_NOEXCEPT_RETURN(
			not (y < x)
		)

#if defined(__cpp_lib_three_way_comparison) and __cpp_lib_three_way_comparison >= 201907
		template<three_way_comparable_with<I> I2>
		requires detail_reverse_iterator::random_access_sympathetic<I> and
		         detail_reverse_iterator::random_access_sympathetic<I2>
		[[nodiscard]] constexpr friend
		auto operator<=>(reverse_iterator const& x, reverse_iterator<I2> const& y)
		CJDB_NOEXCEPT_RETURN(
			y.base() <=> x.base() // The argument order is reversed because this is a reverse iterator.
		)
#endif // __cpp_lib_three_way_comparison

		template<sized_sentinel_for<I> I2>
		requires detail_reverse_iterator::random_access_sympathetic<I> and
		         detail_reverse_iterator::random_access_sympathetic<I2>
		[[nodiscard]] constexpr friend
		auto operator-(reverse_iterator const& x, reverse_iterator<I2> const& y)
		CJDB_NOEXCEPT_RETURN(
			y.base() - x.base()
		)

		[[nodiscard]] constexpr friend
		reverse_iterator operator+(difference_type const n, reverse_iterator const& x)
		CJDB_NOEXCEPT_RETURN(
			x.base() - n
		)
	protected:
		I current_{}; // NOLINT(misc-non-private-member-variables-in-classes)
	};

	template<typename I>
	[[nodiscard]] constexpr reverse_iterator<I> make_reverse_iterator(I i)
	noexcept(std::is_nothrow_move_constructible_v<I>)
	{
		return reverse_iterator<I>{std::move(i)};
	}
} // namespace cjdb

#include "cjdb/detail/undef.hpp"

#endif // CJDB_ITERATOR_ADAPTORS_REVERSE_ITERATOR_HPP
