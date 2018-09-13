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
#ifndef CJDB_DETAIL_CONCEPTS_CORE_HPP
#define CJDB_DETAIL_CONCEPTS_CORE_HPP

// clang-format off
// Note that header inclusion order reflects how concepts are laid out in the Standard.
//
#include "cjdb/detail/concepts/core/same.hpp"
#include "cjdb/detail/concepts/core/derivedfrom.hpp"
#include "cjdb/detail/concepts/core/convertibleto.hpp"
#include "cjdb/detail/concepts/core/commonreference.hpp"
#include "cjdb/detail/concepts/core/common.hpp"
#include "cjdb/detail/concepts/core/integral.hpp"
#include "cjdb/detail/concepts/core/assignable.hpp"
#include "cjdb/detail/concepts/core/swappable.hpp"
#include "cjdb/detail/concepts/core/destructible.hpp"
#include "cjdb/detail/concepts/core/constructible.hpp"
#include "cjdb/detail/concepts/core/defaultconstructible.hpp"
#include "cjdb/detail/concepts/core/moveconstructible.hpp"
#include "cjdb/detail/concepts/core/copyconstructible.hpp"
// clang-format on

#endif // CJDB_DETAIL_CONCEPTS_CORE_HPP
