//
//  Copyright Christopher Di Bella
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "cjdb/functional/rangecmp/partial_equal_to.hpp"

#include "cjdb/concepts/core/same.hpp"
#include <doctest.h>
#include "partial_test.hpp"
#include <utility>


TEST_CASE("Test [cjdb.ext.rangecmp.partial_equal_to]") {
   auto ints = ::cjdb_test::generate_ints();
   using difference_type = decltype(ints)::difference_type;

   using cjdb::ranges::equal_to;
   using cjdb::ranges::partial_equal_to;

   cjdb_test::check_iterators_match(ints, partial_equal_to{-1}, equal_to{});
   cjdb_test::check_iterators_match(ints, partial_equal_to{ 0}, equal_to{});
   cjdb_test::check_iterators_match(ints, partial_equal_to{ 4}, equal_to{});
   // FIXME(cjdb): s/static_cast<difference_type>(std::size(ints))/cjdb::ranges::distance(ints)/
   auto const distance = static_cast<difference_type>(std::size(ints));
   cjdb_test::check_iterators_match(ints, partial_equal_to{distance - 1}, equal_to{});
   cjdb_test::check_iterators_match(ints, partial_equal_to{distance}, equal_to{});

   static_assert(not cjdb::Same<decltype(partial_equal_to{ints}),
                                decltype(partial_equal_to{std::vector<int>{}})>);
   static_assert(cjdb::Same<decltype(partial_equal_to{ints}),
                            decltype(partial_equal_to{std::as_const(ints)})>);
}
