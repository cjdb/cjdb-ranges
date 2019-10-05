// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/concepts/core/convertible_to.hpp"

#include "cjdb/type_traits/expose_type.hpp"

template<typename From, typename To>
constexpr void models_convertible_to()
{
	static_assert(cjdb::convertible_to<From, To>);
	static_assert(cjdb::convertible_to<From, To const>);
	static_assert(cjdb::convertible_to<From, To const&>);

	static_assert(cjdb::convertible_to<From const, To>);
	static_assert(cjdb::convertible_to<From const, To const>);
	static_assert(cjdb::convertible_to<From const, To const&>);

	static_assert(cjdb::convertible_to<From&, To>);
	static_assert(cjdb::convertible_to<From&, To const>);

	if constexpr (std::is_base_of_v<To, From>) { // NOLINT
		static_assert(cjdb::convertible_to<From&, To&>);
	}

	static_assert(cjdb::convertible_to<From&, To const&>);

	static_assert(cjdb::convertible_to<From const&, To>);
	static_assert(cjdb::convertible_to<From const&, To const>);
	static_assert(cjdb::convertible_to<From const&, To const&>);
}

int main()
{
	{
		static_assert(cjdb::convertible_to<void, void>);
		models_convertible_to<int, int>();
	}
	{
		models_convertible_to<int, float>();
		models_convertible_to<float, int>();
	}
	{
		struct implicitly_constructible_from_int {
			[[maybe_unused]] implicitly_constructible_from_int(int); // NOLINT(google-explicit-constructor)
		};
		models_convertible_to<int, implicitly_constructible_from_int>();

		struct implicitly_convertible_to_int {
			[[maybe_unused]] operator int();		 // NOLINT(google-explicit-constructor)
			[[maybe_unused]] operator int() const; // NOLINT(google-explicit-constructor)
		};
		models_convertible_to<implicitly_convertible_to_int, int>();

		struct implicitly_convertible_to_and_from_int {
			[[maybe_unused]] implicitly_convertible_to_and_from_int(int); // NOLINT(google-explicit-constructor)
			[[maybe_unused]] operator int();						 // NOLINT(google-explicit-constructor)
			[[maybe_unused]] operator int() const;				 // NOLINT(google-explicit-constructor)
		};
		models_convertible_to<int, implicitly_convertible_to_and_from_int>();
		models_convertible_to<implicitly_convertible_to_and_from_int, int>();
	}
	{
		struct base {};
		models_convertible_to<base, base>();

		struct public_derived : public base {};
		models_convertible_to<public_derived, base>();
		static_assert(not cjdb::convertible_to<base, public_derived>);

		struct protected_derived : protected base {};
		static_assert(not cjdb::convertible_to<protected_derived, base>);
		static_assert(not cjdb::convertible_to<protected_derived, public_derived>);
		static_assert(not cjdb::convertible_to<base, protected_derived>);

		struct private_derived : private base {};
		static_assert(not cjdb::convertible_to<private_derived, base>);
		static_assert(not cjdb::convertible_to<private_derived, protected_derived>);
		static_assert(not cjdb::convertible_to<private_derived, public_derived>);
		static_assert(not cjdb::convertible_to<base, private_derived>);
	}
}
