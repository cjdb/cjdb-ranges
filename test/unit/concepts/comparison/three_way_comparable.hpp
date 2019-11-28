// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_UNITS_CONCEPTS_COMPARISON_THREE_WAY_COMPARABLE_HPP
#define CJDB_TEST_UNITS_CONCEPTS_COMPARISON_THREE_WAY_COMPARABLE_HPP

#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/type_traits/common_type.hpp"
#include <compare>

namespace cjdb_test {
	struct auto_three_way;
	struct partial_three_way;
	struct weak_three_way;
	struct strong_three_way;
} // namespace cjdb_test

namespace cjdb_test {
	struct auto_three_way {
		bool operator==(auto_three_way const&) const = default;
		auto operator<=>(auto_three_way const&) const = default;

		auto_three_way(partial_three_way);
		operator partial_three_way() const;
		bool operator==(partial_three_way const&) const;
		std::strong_ordering operator<=>(partial_three_way const&) const;

		int x;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::partial_three_way, cjdb_test::auto_three_way> {
		using type = cjdb_test::auto_three_way;
	};

	template<>
	struct common_type<cjdb_test::auto_three_way, cjdb_test::partial_three_way>
	: common_type<cjdb_test::partial_three_way, cjdb_test::auto_three_way>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct partial_three_way {
		bool operator==(partial_three_way const&) const;
		std::partial_ordering operator<=>(partial_three_way const&) const;

		partial_three_way(weak_three_way);
		std::partial_ordering operator<=>(weak_three_way const&) const;
	};

	struct weak_three_way {
		bool operator==(weak_three_way const&) const;
		std::weak_ordering operator<=>(weak_three_way const&) const;

		weak_three_way(partial_three_way);
		bool operator==(partial_three_way const&) const;
		std::weak_ordering operator<=>(partial_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::partial_three_way, cjdb_test::weak_three_way> {
		using type = cjdb_test::partial_three_way;
	};

	template<>
	struct common_type<cjdb_test::weak_three_way, cjdb_test::partial_three_way>
	: common_type<cjdb_test::partial_three_way, cjdb_test::weak_three_way>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct strong_three_way {
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};

	struct int_three_way {
		bool operator==(int_three_way const&) const;
		int operator<=>(int_three_way const&) const;

		int_three_way(strong_three_way);
		operator strong_three_way() const;
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::strong_three_way, cjdb_test::int_three_way> {
		using type = cjdb_test::strong_three_way;
	};

	template<>
	struct common_type<cjdb_test::int_three_way, cjdb_test::strong_three_way>
	: common_type<cjdb_test::strong_three_way, cjdb_test::int_three_way>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct partial_three_way_bad_eq {
		void operator==(partial_three_way_bad_eq const&) const;
		std::partial_ordering operator<=>(partial_three_way_bad_eq const&) const;

		partial_three_way_bad_eq(strong_three_way);
		operator strong_three_way() const;
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::strong_three_way, cjdb_test::partial_three_way_bad_eq> {
		using type = cjdb_test::strong_three_way;
	};

	template<>
	struct common_type<cjdb_test::partial_three_way_bad_eq, cjdb_test::strong_three_way>
	: common_type<cjdb_test::strong_three_way, cjdb_test::partial_three_way_bad_eq>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct weak_three_way_bad_eq {
		void operator==(weak_three_way_bad_eq const&) const;
		std::weak_ordering operator<=>(weak_three_way_bad_eq const&) const;

		weak_three_way_bad_eq(strong_three_way);
		operator strong_three_way() const;
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::strong_three_way, cjdb_test::weak_three_way_bad_eq> {
		using type = cjdb_test::strong_three_way;
	};

	template<>
	struct common_type<cjdb_test::weak_three_way_bad_eq, cjdb_test::strong_three_way>
	: common_type<cjdb_test::strong_three_way, cjdb_test::weak_three_way_bad_eq>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct strong_three_way_bad_eq {
		void operator==(strong_three_way_bad_eq const&) const;
		std::strong_ordering operator<=>(strong_three_way_bad_eq const&) const;

		strong_three_way_bad_eq(strong_three_way);
		operator strong_three_way() const;
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::strong_three_way, cjdb_test::strong_three_way_bad_eq> {
		using type = cjdb_test::strong_three_way;
	};

	template<>
	struct common_type<cjdb_test::strong_three_way_bad_eq, cjdb_test::strong_three_way>
	: common_type<cjdb_test::strong_three_way, cjdb_test::strong_three_way_bad_eq>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct partial_missing_equal_to {
		bool operator==(partial_missing_equal_to) const = delete;
		bool operator!=(partial_missing_equal_to) const;
		std::partial_ordering operator<=>(partial_missing_equal_to const&) const;

		partial_missing_equal_to(strong_three_way);
		operator strong_three_way() const;
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::strong_three_way, cjdb_test::partial_missing_equal_to> {
		using type = cjdb_test::strong_three_way;
	};

	template<>
	struct common_type<cjdb_test::partial_missing_equal_to, cjdb_test::strong_three_way>
	: common_type<cjdb_test::strong_three_way, cjdb_test::partial_missing_equal_to>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct weak_missing_equal_to {
		bool operator==(weak_missing_equal_to) const = delete;
		bool operator!=(weak_missing_equal_to) const;
		std::weak_ordering operator<=>(weak_missing_equal_to const&) const;

		weak_missing_equal_to(strong_three_way);
		operator strong_three_way() const;
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::strong_three_way, cjdb_test::weak_missing_equal_to> {
		using type = cjdb_test::strong_three_way;
	};

	template<>
	struct common_type<cjdb_test::weak_missing_equal_to, cjdb_test::strong_three_way>
	: common_type<cjdb_test::strong_three_way, cjdb_test::weak_missing_equal_to>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct strong_missing_equal_to {
		bool operator==(strong_missing_equal_to) const = delete;
		bool operator!=(strong_missing_equal_to) const;
		std::strong_ordering operator<=>(strong_missing_equal_to const&) const;

		strong_missing_equal_to(strong_three_way);
		operator strong_three_way() const;
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::strong_three_way, cjdb_test::strong_missing_equal_to> {
		using type = cjdb_test::strong_three_way;
	};

	template<>
	struct common_type<cjdb_test::strong_missing_equal_to, cjdb_test::strong_three_way>
	: common_type<cjdb_test::strong_three_way, cjdb_test::strong_missing_equal_to>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct partial_missing_not_equal_to {
		bool operator==(partial_missing_not_equal_to) const;
		bool operator!=(partial_missing_not_equal_to) const = delete;
		std::partial_ordering operator<=>(partial_missing_not_equal_to const&) const;

		partial_missing_not_equal_to(strong_three_way);
		operator strong_three_way() const;
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::strong_three_way, cjdb_test::partial_missing_not_equal_to> {
		using type = cjdb_test::strong_three_way;
	};

	template<>
	struct common_type<cjdb_test::partial_missing_not_equal_to, cjdb_test::strong_three_way>
	: common_type<cjdb_test::strong_three_way, cjdb_test::partial_missing_not_equal_to>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct weak_missing_not_equal_to {
		bool operator==(weak_missing_not_equal_to) const;
		bool operator!=(weak_missing_not_equal_to) const = delete;
		std::weak_ordering operator<=>(weak_missing_not_equal_to const&) const;

		weak_missing_not_equal_to(strong_three_way);
		operator strong_three_way() const;
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::strong_three_way, cjdb_test::weak_missing_not_equal_to> {
		using type = cjdb_test::strong_three_way;
	};

	template<>
	struct common_type<cjdb_test::weak_missing_not_equal_to, cjdb_test::strong_three_way>
	: common_type<cjdb_test::strong_three_way, cjdb_test::weak_missing_not_equal_to>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct strong_missing_not_equal_to {
		bool operator==(strong_missing_not_equal_to) const;
		bool operator!=(strong_missing_not_equal_to) const = delete;
		std::strong_ordering operator<=>(strong_missing_not_equal_to const&) const;

		strong_missing_not_equal_to(strong_three_way);
		operator strong_three_way() const;
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::strong_three_way, cjdb_test::strong_missing_not_equal_to> {
		using type = cjdb_test::strong_three_way;
	};

	template<>
	struct common_type<cjdb_test::strong_missing_not_equal_to, cjdb_test::strong_three_way>
	: common_type<cjdb_test::strong_three_way, cjdb_test::strong_missing_not_equal_to>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct partial_missing_less {
		bool operator==(partial_missing_less) const;
		std::partial_ordering operator<=>(partial_missing_less const&) const;
		void operator<(partial_missing_less) const = delete;

		partial_missing_less(strong_three_way);
		operator strong_three_way() const;
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::strong_three_way, cjdb_test::partial_missing_less> {
		using type = cjdb_test::strong_three_way;
	};

	template<>
	struct common_type<cjdb_test::partial_missing_less, cjdb_test::strong_three_way>
	: common_type<cjdb_test::strong_three_way, cjdb_test::partial_missing_less>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct weak_missing_less {
		bool operator==(weak_missing_less) const;
		std::weak_ordering operator<=>(weak_missing_less const&) const;
		void operator<(weak_missing_less) const = delete;

		weak_missing_less(strong_three_way);
		operator strong_three_way() const;
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::strong_three_way, cjdb_test::weak_missing_less> {
		using type = cjdb_test::strong_three_way;
	};

	template<>
	struct common_type<cjdb_test::weak_missing_less, cjdb_test::strong_three_way>
	: common_type<cjdb_test::strong_three_way, cjdb_test::weak_missing_less>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct strong_missing_less {
		bool operator==(strong_missing_less) const;
		std::strong_ordering operator<=>(strong_missing_less const&) const;
		void operator<(strong_missing_less) const = delete;

		strong_missing_less(strong_three_way);
		operator strong_three_way() const;
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::strong_three_way, cjdb_test::strong_missing_less> {
		using type = cjdb_test::strong_three_way;
	};

	template<>
	struct common_type<cjdb_test::strong_missing_less, cjdb_test::strong_three_way>
	: common_type<cjdb_test::strong_three_way, cjdb_test::strong_missing_less>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct partial_missing_less_equal {
		bool operator==(partial_missing_less_equal) const;
		std::partial_ordering operator<=>(partial_missing_less_equal const&) const;
		void operator<=(partial_missing_less_equal) const = delete;

		partial_missing_less_equal(strong_three_way);
		operator strong_three_way() const;
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::strong_three_way, cjdb_test::partial_missing_less_equal> {
		using type = cjdb_test::strong_three_way;
	};

	template<>
	struct common_type<cjdb_test::partial_missing_less_equal, cjdb_test::strong_three_way>
	: common_type<cjdb_test::strong_three_way, cjdb_test::partial_missing_less_equal>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct weak_missing_less_equal {
		bool operator==(weak_missing_less_equal) const;
		std::weak_ordering operator<=>(weak_missing_less_equal const&) const;
		void operator<=(weak_missing_less_equal) const = delete;

		weak_missing_less_equal(strong_three_way);
		operator strong_three_way() const;
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::strong_three_way, cjdb_test::weak_missing_less_equal> {
		using type = cjdb_test::strong_three_way;
	};

	template<>
	struct common_type<cjdb_test::weak_missing_less_equal, cjdb_test::strong_three_way>
	: common_type<cjdb_test::strong_three_way, cjdb_test::weak_missing_less_equal>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct strong_missing_less_equal {
		bool operator==(strong_missing_less_equal) const;
		std::strong_ordering operator<=>(strong_missing_less_equal const&) const;
		void operator<=(strong_missing_less_equal) const = delete;

		strong_missing_less_equal(strong_three_way);
		operator strong_three_way() const;
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::strong_three_way, cjdb_test::strong_missing_less_equal> {
		using type = cjdb_test::strong_three_way;
	};

	template<>
	struct common_type<cjdb_test::strong_missing_less_equal, cjdb_test::strong_three_way>
	: common_type<cjdb_test::strong_three_way, cjdb_test::strong_missing_less_equal>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct partial_missing_greater {
		bool operator==(partial_missing_greater) const;
		std::partial_ordering operator<=>(partial_missing_greater const&) const;
		void operator>(partial_missing_greater) const = delete;

		partial_missing_greater(strong_three_way);
		operator strong_three_way() const;
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::strong_three_way, cjdb_test::partial_missing_greater> {
		using type = cjdb_test::strong_three_way;
	};

	template<>
	struct common_type<cjdb_test::partial_missing_greater, cjdb_test::strong_three_way>
	: common_type<cjdb_test::strong_three_way, cjdb_test::partial_missing_greater>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct weak_missing_greater {
		bool operator==(weak_missing_greater) const;
		std::weak_ordering operator<=>(weak_missing_greater const&) const;
		void operator>(weak_missing_greater) const = delete;

		weak_missing_greater(strong_three_way);
		operator strong_three_way() const;
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::strong_three_way, cjdb_test::weak_missing_greater> {
		using type = cjdb_test::strong_three_way;
	};

	template<>
	struct common_type<cjdb_test::weak_missing_greater, cjdb_test::strong_three_way>
	: common_type<cjdb_test::strong_three_way, cjdb_test::weak_missing_greater>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct strong_missing_greater {
		bool operator==(strong_missing_greater) const;
		std::strong_ordering operator<=>(strong_missing_greater const&) const;
		void operator>(strong_missing_greater) const = delete;

		strong_missing_greater(strong_three_way);
		operator strong_three_way() const;
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::strong_three_way, cjdb_test::strong_missing_greater> {
		using type = cjdb_test::strong_three_way;
	};

	template<>
	struct common_type<cjdb_test::strong_missing_greater, cjdb_test::strong_three_way>
	: common_type<cjdb_test::strong_three_way, cjdb_test::strong_missing_greater>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct partial_missing_greater_equal {
		bool operator==(partial_missing_greater_equal) const;
		std::partial_ordering operator<=>(partial_missing_greater_equal const&) const;
		void operator>=(partial_missing_greater_equal) const = delete;

		partial_missing_greater_equal(strong_three_way);
		operator strong_three_way() const;
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::strong_three_way, cjdb_test::partial_missing_greater_equal> {
		using type = cjdb_test::strong_three_way;
	};

	template<>
	struct common_type<cjdb_test::partial_missing_greater_equal, cjdb_test::strong_three_way>
	: common_type<cjdb_test::strong_three_way, cjdb_test::partial_missing_greater_equal>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct weak_missing_greater_equal {
		bool operator==(weak_missing_greater_equal) const;
		std::weak_ordering operator<=>(weak_missing_greater_equal const&) const;
		void operator>=(weak_missing_greater_equal) const = delete;

		weak_missing_greater_equal(strong_three_way);
		operator strong_three_way() const;
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::strong_three_way, cjdb_test::weak_missing_greater_equal> {
		using type = cjdb_test::strong_three_way;
	};

	template<>
	struct common_type<cjdb_test::weak_missing_greater_equal, cjdb_test::strong_three_way>
	: common_type<cjdb_test::strong_three_way, cjdb_test::weak_missing_greater_equal>
	{};
} // namespace cjdb

namespace cjdb_test {
	struct strong_missing_greater_equal {
		bool operator==(strong_missing_greater_equal) const;
		std::strong_ordering operator<=>(strong_missing_greater_equal const&) const;
		void operator>=(strong_missing_greater_equal) const = delete;

		strong_missing_greater_equal(strong_three_way);
		operator strong_three_way() const;
		bool operator==(strong_three_way const&) const;
		std::strong_ordering operator<=>(strong_three_way const&) const;
	};
} // namespace cjdb_test

namespace cjdb {
	template<>
	struct common_type<cjdb_test::strong_three_way, cjdb_test::strong_missing_greater_equal> {
		using type = cjdb_test::strong_three_way;
	};

	template<>
	struct common_type<cjdb_test::strong_missing_greater_equal, cjdb_test::strong_three_way>
	: common_type<cjdb_test::strong_three_way, cjdb_test::strong_missing_greater_equal>
	{};
} // namespace cjdb

#endif // CJDB_TEST_UNITS_CONCEPTS_COMPARISON_THREE_WAY_COMPARABLE_HPP
