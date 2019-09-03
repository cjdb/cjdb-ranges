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
#include "cjdb/concepts.hpp"

// Core
using cjdb::same_as;
using cjdb::derived_from;
using cjdb::convertible_to;
using cjdb::common_reference_with;
using cjdb::common_with;
using cjdb::integral;
using cjdb::signed_integral;
using cjdb::unsigned_integral;
using cjdb::assignable_from;
using cjdb::swappable;
using cjdb::swappable_with;
using cjdb::destructible;
using cjdb::constructible_from;
using cjdb::default_initializable;
using cjdb::move_constructible;
using cjdb::copy_constructible;

// Compare
using cjdb::equality_comparable;
using cjdb::equality_comparable_with;
using cjdb::totally_ordered;
using cjdb::totally_ordered_with;

// Object
using cjdb::movable;
using cjdb::copyable;
using cjdb::semiregular;
using cjdb::regular;

// Callable
using cjdb::invocable;
using cjdb::regular_invocable;
using cjdb::predicate;
using cjdb::relation;
using cjdb::strict_weak_order;

int main()
{}
