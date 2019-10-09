// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/detail/iterator/iterator_traits.hpp"

#include "cjdb/concepts/core/integral.hpp"
#include "cjdb/detail/iterator/incrementable_traits.hpp"
#include "cjdb/detail/iterator/readable_traits.hpp"
#include "cjdb/test/iterator/legacy_iterator_wrapper.hpp"
#include <vector>

template<typename Category, typename Value, typename Difference, typename Reference>
struct explicit_members {
	using iterator_category = Category;
	using value_type = Value;
	using difference_type = Difference;
	using reference = Reference;
};

template<typename Category, typename Value, typename Difference, typename Reference>
struct explicit_members_with_pointer : explicit_members<Category, Value, Difference, Reference> {
	using pointer = typename explicit_members<Category, Value, Difference, Reference>::value_type*;
};

template<typename Category, typename Value, typename Difference, typename Reference>
constexpr void check_members_explicitly_provided()
{
	{
		using fake_iterator = explicit_members<Category, Value, Difference, Reference>;
		using iterator_traits = cjdb::iterator_traits<fake_iterator>;
		static_assert(cjdb::same_as<typename iterator_traits::iterator_category, Category>);
		static_assert(cjdb::same_as<typename iterator_traits::value_type, Value>);
		static_assert(cjdb::same_as<typename iterator_traits::difference_type, Difference>);
		static_assert(cjdb::same_as<typename iterator_traits::reference, Reference>);
		static_assert(cjdb::same_as<typename iterator_traits::pointer, void>);
	}

	{
		using fake_iterator = explicit_members_with_pointer<Category, Value, Difference, Reference>;
		using iterator_traits = cjdb::iterator_traits<fake_iterator>;
		static_assert(cjdb::same_as<typename iterator_traits::iterator_category, Category>);
		static_assert(cjdb::same_as<typename iterator_traits::value_type, Value>);
		static_assert(cjdb::same_as<typename iterator_traits::difference_type, Difference>);
		static_assert(cjdb::same_as<typename iterator_traits::reference, Reference>);
		static_assert(cjdb::same_as<typename iterator_traits::pointer, Value*>);
	}
}

template<typename I, template<typename> typename... Args>
requires (sizeof...(Args) > 0)
constexpr void check_with_legacy_input_iterator()
{
	auto check = []<typename Iterator, typename Traits>(Iterator, Traits, auto category) {
		static_assert(cjdb::same_as<typename Traits::iterator_category, decltype(category)>);
		static_assert(cjdb::same_as<typename Traits::value_type, cjdb::iter_value_t<I>>);
		static_assert(cjdb::same_as<typename Traits::difference_type, cjdb::iter_difference_t<I>>);

		if constexpr (cjdb::derived_from<Iterator, cjdb_test::reference_extension<I>>) {
			static_assert(cjdb::same_as<typename Traits::reference, typename Iterator::reference>);
		}
		else {
			static_assert(cjdb::same_as<typename Traits::reference, cjdb::iter_reference_t<I>>);
		}

		if constexpr (cjdb::derived_from<Iterator, cjdb_test::pointer_extension<I>>) { // NOLINT(bugprone-branch-clone)
			static_assert(cjdb::same_as<typename Traits::pointer, typename Iterator::pointer>);
		}
		else if constexpr (cjdb_test::has_arrow<Iterator>) { // NOLINT(bugprone-branch-clone)
			static_assert(cjdb::same_as<typename Traits::pointer,
			                            decltype(std::declval<I&>().operator->())>);
		}
		else {
			static_assert(cjdb::same_as<typename Traits::pointer, void>);
		}
	};

	using cjdb_test::minimal_extension;
	{
		using iterator = cjdb_test::legacy_input_iterator<I, minimal_extension, Args...>;
		using iterator_traits = cjdb::iterator_traits<iterator>;
		check(iterator{I{}}, iterator_traits{}, std::input_iterator_tag{});
	}
	{
		using iterator = cjdb_test::legacy_forward_iterator<I, minimal_extension, Args...>;
		using iterator_traits = cjdb::iterator_traits<iterator>;
		check(iterator{}, iterator_traits{}, std::forward_iterator_tag{});
	}
	{
		using iterator = cjdb_test::legacy_bidirectional_iterator<I, minimal_extension, Args...>;
		using iterator_traits = cjdb::iterator_traits<iterator>;
		check(iterator{}, iterator_traits{}, std::bidirectional_iterator_tag{});
	}
	{
		using iterator = cjdb_test::legacy_random_access_iterator<I, minimal_extension, Args...>;
		using iterator_traits = cjdb::iterator_traits<iterator>;
		check(iterator{}, iterator_traits{}, std::random_access_iterator_tag{});
	}
}

template<typename I>
constexpr void check_with_legacy_input_iterator()
{
	using cjdb_test::empty_extension, cjdb_test::reference_extension;
	using cjdb_test::pointer_extension, cjdb_test::arrow_extension;
	check_with_legacy_input_iterator<I, empty_extension>();
	check_with_legacy_input_iterator<I, reference_extension>();
	check_with_legacy_input_iterator<I, pointer_extension>();
	check_with_legacy_input_iterator<I, arrow_extension>();
	check_with_legacy_input_iterator<I, reference_extension, pointer_extension>();
	check_with_legacy_input_iterator<I, reference_extension, arrow_extension>();
}

template<typename I>
constexpr void check_with_legacy_iterator()
{
	{
		using iterator = cjdb_test::legacy_iterator<I>;
		using iterator_traits = cjdb::iterator_traits<iterator>;
		static_assert(cjdb::same_as<typename iterator_traits::iterator_category,
		                            std::output_iterator_tag>);
		static_assert(cjdb::same_as<typename iterator_traits::value_type, void>);
		static_assert(cjdb::same_as<typename iterator_traits::difference_type, void>);
		static_assert(cjdb::same_as<typename iterator_traits::reference, void>);
		static_assert(cjdb::same_as<typename iterator_traits::pointer, void>);
	}
	{
		using iterator = cjdb_test::legacy_iterator<I, cjdb::incrementable_traits>;
		using iterator_traits = cjdb::iterator_traits<iterator>;
		static_assert(cjdb::same_as<typename iterator_traits::iterator_category,
		                            std::output_iterator_tag>);
		static_assert(cjdb::same_as<typename iterator_traits::value_type, void>);
		static_assert(cjdb::same_as<typename iterator_traits::difference_type,
		                            typename cjdb::iter_difference_t<I>>);
		static_assert(cjdb::same_as<typename iterator_traits::reference, void>);
		static_assert(cjdb::same_as<typename iterator_traits::pointer, void>);
	}
}

template<typename T, typename Expected = T>
constexpr void check_pointer()
{
	using iterator_traits = cjdb::iterator_traits<T*>;
	static_assert(cjdb::same_as<typename iterator_traits::iterator_concept,
	                            cjdb::contiguous_iterator_tag>);
	static_assert(cjdb::same_as<typename iterator_traits::iterator_category,
	                            std::random_access_iterator_tag>);
	static_assert(cjdb::same_as<typename iterator_traits::value_type, Expected>);
	static_assert(cjdb::same_as<typename iterator_traits::difference_type, std::ptrdiff_t>);
	static_assert(cjdb::same_as<typename iterator_traits::pointer, T*>);
	static_assert(cjdb::same_as<typename iterator_traits::reference, T&>);
}

template<typename T>
constexpr void check_fails()
{
	{
		constexpr auto result = requires { typename cjdb::iterator_traits<T>::iterator_concept; };
		static_assert(not result, "iterator_traits<T>::iterator_concept should not exist.");
	}
	{
		constexpr auto result = requires { typename cjdb::iterator_traits<T>::iterator_category; };
		static_assert(not result, "iterator_traits<T>::iterator_category should not exist.");
	}
	{
		constexpr auto result = requires { typename cjdb::iterator_traits<T>::value_type; };
		static_assert(not result, "iterator_traits<T>::value_type should not exist.");
	}
	{
		constexpr auto result = requires { typename cjdb::iterator_traits<T>::difference_type; };
		static_assert(not result, "iterator_traits<T>::difference_type should not exist.");
	}
	{
		constexpr auto result = requires { typename cjdb::iterator_traits<T>::pointer; };
		static_assert(not result, "iterator_traits<T>::pointer should not exist.");
	}
	{
		constexpr auto result = requires { typename cjdb::iterator_traits<T>::reference; };
		static_assert(not result, "iterator_traits<T>::reference should not exist.");
	}
}

struct missing_iterator_category {
	using value_type = int;
	using difference_type = int;
	using pointer = int*;
	using reference = int&;
};

struct missing_value_type {
	using iterator_category = std::input_iterator_tag;
	using difference_type = int;
	using pointer = int*;
	using reference = int&;
};

struct missing_difference_type {
	using iterator_category = std::input_iterator_tag;
	using value_type = int;
	using pointer = int*;
	using reference = int&;
};

struct missing_reference {
	using iterator_category = std::input_iterator_tag;
	using value_type = int;
	using difference_type = int;
	using pointer = int&;
};

int main()
{
	check_members_explicitly_provided<std::input_iterator_tag, int, int, int&>();
	check_members_explicitly_provided<std::input_iterator_tag, int, long, int&>();
	check_members_explicitly_provided<std::forward_iterator_tag, int, double, int&>();

	struct dummy {};
	check_members_explicitly_provided<std::bidirectional_iterator_tag, dummy, int, long long>();
	check_members_explicitly_provided<std::random_access_iterator_tag, dummy, int, long long>();

	check_with_legacy_input_iterator<std::vector<int>::iterator>();
	check_with_legacy_input_iterator<std::vector<int>::const_iterator>();
	check_with_legacy_input_iterator<std::vector<int const>::iterator>();
	check_with_legacy_input_iterator<std::vector<int const>::const_iterator>();

	check_with_legacy_iterator<std::vector<int>::iterator>();
	check_with_legacy_iterator<std::vector<int>::const_iterator>();
	check_with_legacy_iterator<std::vector<int const>::iterator>();
	check_with_legacy_iterator<std::vector<int const>::const_iterator>();
	check_with_legacy_iterator<int* volatile>();
	check_with_legacy_iterator<dummy* volatile>();

	check_pointer<int>();
	check_pointer<int const, int>();
	check_pointer<double>();
	check_pointer<double volatile, double>();
	check_pointer<dummy>();
	check_pointer<dummy const volatile, dummy>();


	check_fails<void>();
	check_fails<dummy>();
	check_fails<dummy&>();
	check_fails<dummy* const>();
	check_fails<dummy* const volatile>();
	check_fails<dummy const&>();
	check_fails<dummy volatile&>();
	check_fails<dummy const volatile&>();
	check_fails<dummy(*)()>();
	check_fails<dummy(&)()>();
	check_fails<int[]>();                    // NOLINT(modernize-avoid-c-arrays)
	check_fails<int const[]>();              // NOLINT(modernize-avoid-c-arrays)
	check_fails<double[]>();                 // NOLINT(modernize-avoid-c-arrays)
	check_fails<double volatile[]>();        // NOLINT(modernize-avoid-c-arrays)
	check_fails<dummy[]>();                  // NOLINT(modernize-avoid-c-arrays)
	check_fails<dummy const volatile[]>();   // NOLINT(modernize-avoid-c-arrays)
	check_fails<missing_iterator_category>();
	check_fails<missing_value_type>();
	check_fails<missing_difference_type>();
	check_fails<missing_reference>();
}
