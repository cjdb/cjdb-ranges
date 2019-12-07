// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-.0 WITH LLVM-exception
//
#include "cjdb/iterator/concepts/indirectly_movable_storable.hpp"

#include "cjdb/concepts/object/semiregular.hpp"
#include "cjdb/range/associated_types.hpp"
#include "cjdb/test/iterator/read_write.hpp"
#include <vector>

namespace cjdb_test {
	template<typename T, typename U, bool expected = true>
	constexpr void check_indirectly_movable_storable()
	{
		static_assert(cjdb::indirectly_movable_storable<T, U> == expected);
		static_assert(cjdb::indirectly_movable_storable<T, U const> == expected);
		static_assert(cjdb::indirectly_movable_storable<T const, U> == expected);
		static_assert(cjdb::indirectly_movable_storable<T const, U const> == expected);
	}

	struct dummy {};
	static_assert(cjdb::semiregular<dummy>);
	static_assert(not cjdb::constructible_from<dummy, int>);
	static_assert(not cjdb::assignable_from<dummy&, int>);

	struct int_constructible {
		int_constructible() = default;
		int_constructible(int);

		int_constructible& operator=(int) = delete;
	};
	static_assert(cjdb::semiregular<int_constructible>);
	static_assert(cjdb::constructible_from<int_constructible, int>);
	static_assert(not cjdb::assignable_from<int_constructible&, int>);

	struct not_movable {
		not_movable() = default;
		not_movable(not_movable&&) = delete;
		not_movable(int);
	};
	static_assert(not cjdb::movable<not_movable>);
	static_assert(cjdb::constructible_from<not_movable, int>);
	static_assert(not cjdb::assignable_from<not_movable&, int>);

	/// \brief A type that should model `indirectly_movable_storable` with `int*`,
	///
	struct fake_int {
		fake_int() = default;

		template<cjdb::same_as<int> T>
		fake_int(T);

		template<cjdb::same_as<int> T>
		fake_int& operator=(T);

		// template<cjdb::same_as<int> T>
		// operator T() const;
	};

	static_assert(cjdb::semiregular<fake_int>);
	static_assert(cjdb::convertible_to<int, fake_int>);
	static_assert(cjdb::constructible_from<fake_int, int>);
} // namespace cjdb_test

int main()
{
	cjdb_test::check_indirectly_movable_storable<int*, int*>();
	cjdb_test::check_indirectly_movable_storable<int const*, int*>();
	cjdb_test::check_indirectly_movable_storable<int*, float*>();
	cjdb_test::check_indirectly_movable_storable<float*, int*>();

	cjdb_test::check_indirectly_movable_storable<int*, cjdb::iterator_t<std::vector<cjdb_test::fake_int>>>();
	// cjdb_test::check_indirectly_movable_storable<cjdb::iterator_t<std::vector<cjdb_test::fake_int>>, int*>();

	cjdb_test::check_indirectly_movable_storable<float*, cjdb::iterator_t<std::vector<cjdb_test::fake_int>>, false>();
	cjdb_test::check_indirectly_movable_storable<cjdb::iterator_t<std::vector<cjdb_test::fake_int>>, float*, false>();

	cjdb_test::check_indirectly_movable_storable<int*, int const*, false>();
	cjdb_test::check_indirectly_movable_storable<float*, int const*, false>();
}
