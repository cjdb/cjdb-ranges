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
using cjdb::Same;
using cjdb::DerivedFrom;
using cjdb::ConvertibleTo;
using cjdb::CommonReference;
using cjdb::Common;
using cjdb::Integral;
using cjdb::SignedIntegral;
using cjdb::UnsignedIntegral;
using cjdb::Assignable;
using cjdb::Swappable;
using cjdb::SwappableWith;
using cjdb::Destructible;
using cjdb::Constructible;
using cjdb::DefaultConstructible;
using cjdb::MoveConstructible;
using cjdb::CopyConstructible;

// Compare
using cjdb::Boolean;
using cjdb::EqualityComparable;
using cjdb::EqualityComparableWith;
using cjdb::StrictTotallyOrdered;
using cjdb::StrictTotallyOrderedWith;

// Object
using cjdb::Movable;
using cjdb::Copyable;
using cjdb::Semiregular;
using cjdb::Regular;

// Callable
using cjdb::Invocable;
using cjdb::RegularInvocable;
using cjdb::Predicate;
using cjdb::Relation;
using cjdb::StrictWeakOrder;

int main()
{}
