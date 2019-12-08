// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/iterator/concepts/indirectly_readable.hpp"

#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/test/iterator/read_write.hpp"


using cjdb::indirectly_readable;
using cjdb::same_as;
namespace ranges = cjdb::ranges;

static_assert(indirectly_readable<cjdb_test::traditional_indirection>);
static_assert(indirectly_readable<cjdb_test::alternative_indirection>);
static_assert(indirectly_readable<cjdb_test::proxy_indirection>);
static_assert(indirectly_readable<cjdb_test::read_only_indirection>);

static_assert(not same_as<cjdb::iter_value_t<cjdb_test::indirection_mismatch>,
                          cjdb::iter_reference_t<cjdb_test::indirection_mismatch>>);
static_assert(indirectly_readable<cjdb_test::indirection_mismatch>);

static_assert(not indirectly_readable<cjdb_test::missing_dereference>);

static_assert(same_as<decltype(ranges::iter_move(std::declval<cjdb_test::iter_move_mismatch&>())),
                      float&>);
static_assert(not indirectly_readable<cjdb_test::iter_move_mismatch>);

static_assert(same_as<decltype(ranges::iter_move(std::declval<cjdb_test::indirection_and_iter_move_mismatch&>())),
                      unsigned long long&>);
static_assert(not indirectly_readable<cjdb_test::indirection_and_iter_move_mismatch>);

struct missing_readable_trait {
	int& operator*() const;
};
static_assert(not indirectly_readable<missing_readable_trait>);

int main() {}
