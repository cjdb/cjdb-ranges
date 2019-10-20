// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/functional/identity.hpp"

#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/test/constexpr_check.hpp"
#include <type_traits>

namespace cjdb_test {
	auto lvalue_identity = []{
		static_assert(cjdb::same_as<std::invoke_result_t<cjdb::identity, int&>, int&>);
		static_assert(cjdb::same_as<std::invoke_result_t<cjdb::identity, int const&>, int const&>);

		auto mutable_lvalue = []{
			auto i = 10; // NOLINT(readability-magic-numbers)
			return cjdb::identity{}(i) == i;
		};
		CJDB_CONSTEXPR_CHECK(mutable_lvalue());

		auto immutable_lvalue = []{
			constexpr auto i = 431;
			return cjdb::identity{}(i) == i;
		};
		CJDB_CONSTEXPR_CHECK(immutable_lvalue());
	};

	auto xvalue_identity = []{
		class trace {
		public:
			trace() = default;

			constexpr trace(trace&& t) noexcept
			: moved_{}
			{
				t.moved_ = true;
			}

			[[nodiscard]] constexpr auto moved() const noexcept
			{ return moved_; }
		private:
			bool moved_ = false;
		};

		static_assert(cjdb::same_as<std::invoke_result_t<cjdb::identity, trace&&>, trace&&>);

		auto mutable_xvalue = []{
			auto value1 = trace{};
			auto value2 = cjdb::identity{}(std::move(value1));
			return value1.moved() and // NOLINT(bugprone-use-after-move,clang-analyzer-cplusplus.Move)
			       not value2.moved();
		};
		CJDB_CONSTEXPR_CHECK(mutable_xvalue());
	};

	auto rvalue_identity = []{
		static_assert(cjdb::same_as<std::invoke_result_t<cjdb::identity, int>, int&&>);

		auto mutable_prvalue = []{ return cjdb::identity{}(std::pair{0, 1}) == std::pair{0, 1}; };
		CJDB_CONSTEXPR_CHECK(mutable_prvalue());

		auto immutable_prvalue = []{ return cjdb::identity{}(321) == 321; }; // NOLINT(readability-magic-numbers)
		CJDB_CONSTEXPR_CHECK(immutable_prvalue());
	};
} // namespace cjdb_test

int main()
{
	CJDB_EVALUATE_TEST_CASE(cjdb_test::lvalue_identity);
	CJDB_EVALUATE_TEST_CASE(cjdb_test::xvalue_identity);
	CJDB_EVALUATE_TEST_CASE(cjdb_test::rvalue_identity);
	return ::test_result();
}
