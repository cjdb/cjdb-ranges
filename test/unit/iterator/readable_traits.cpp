// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/detail/iterator/readable_traits.hpp"

#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/concepts/core/integral.hpp"
#include <memory>
#include <vector>

template<typename T, typename Expected>
constexpr void instantiate_readable_traits()
{
	using cjdb::same_as, cjdb::readable_traits, cjdb::iter_value_t;
	static_assert(same_as<typename readable_traits<T>::value_type, Expected>);
	static_assert(same_as<iter_value_t<T>, typename readable_traits<T>::value_type>);
}

template<typename T>
constexpr void check_array()
{
	instantiate_readable_traits<T[], T>();                // NOLINT(modernize-avoid-c-arrays)
	instantiate_readable_traits<T const[], T>();          // NOLINT(modernize-avoid-c-arrays)
	instantiate_readable_traits<T volatile[], T>();       // NOLINT(modernize-avoid-c-arrays)
	instantiate_readable_traits<T const volatile[], T>(); // NOLINT(modernize-avoid-c-arrays)
}

template<typename T, typename Expected>
constexpr void check_explicit_member()
{
	instantiate_readable_traits<T, Expected>();
	instantiate_readable_traits<T const, Expected>();
}

template<typename T>
constexpr void check_fails()
{
	constexpr auto result = requires { typename cjdb::readable_traits<T>::value_type; };
	static_assert(not result, "This type shouldn't be readable!");
}

template<typename T>
constexpr void check_ref()
{
	struct ref_value {
		using value_type = T&;
	};
	check_fails<ref_value>();

	struct ref_element {
		using element_type = T&;
	};
	check_fails<ref_element>();

	if (not (std::is_const_v<T> or std::is_volatile_v<T>)) {
		check_ref<T const>();
		check_ref<T volatile>();
		check_ref<T const volatile>();
	}
}

int main()
{
	check_array<int>();
	check_array<long>();
	check_array<double>();

	struct dummy {};
	check_array<dummy>();

	struct has_value_type {
		using value_type = int;
	};
	check_explicit_member<has_value_type, int>();
	check_explicit_member<std::vector<int>::iterator, int>();
	check_explicit_member<std::vector<int const>::iterator, int>();

	struct has_element_type {
		using element_type = dummy;
	};
	check_explicit_member<has_element_type, dummy>();
	check_explicit_member<std::shared_ptr<long>, long>();
	check_explicit_member<std::shared_ptr<long const>, long>();

	check_fails<int>();
	check_fails<dummy>();

	struct has_both : has_value_type, has_element_type {};
	check_fails<has_both>();

	struct void_value {
		using value_type = void;
	};
	check_fails<void_value>();

	struct void_element {
		using element_type = void;
	};
	check_fails<void_element>();

	check_ref<int>();
	check_ref<dummy>();
	check_ref<std::shared_ptr<long>>();
}
