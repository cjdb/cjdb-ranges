//
//  Copyright 2019 Christopher Di Bella
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
#ifndef CJDB_TEST_FUNCTIONAL_RANGECMP_IS_STRICT_TOTAL_ORDER_HPP
#define CJDB_TEST_FUNCTIONAL_RANGECMP_IS_STRICT_TOTAL_ORDER_HPP

#include "cjdb/test/functional/rangecmp/is_antisymmetric.hpp"
#include "cjdb/test/functional/rangecmp/is_connex.hpp"
#include "cjdb/test/functional/rangecmp/is_irreflexive.hpp"
#include "cjdb/test/functional/rangecmp/is_transitive.hpp"

#define CHECK_IS_STRICT_TOTAL_ORDER(r, a, b, c) \
   {                                            \
      CHECK_IS_IRREFLEXIVE(r, a);               \
      CHECK_IS_ANTISYMMETRIC(r, a, b);          \
      CHECK_IS_TRANSITIVE(r, a, b, c);          \
      CHECK_IS_CONNEX(r, a, b);                 \
   }                                            \


#endif // CJDB_TEST_FUNCTIONAL_RANGECMP_IS_STRICT_TOTAL_ORDER_HPP
