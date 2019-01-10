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
#ifndef CJDB_FUNCTIONAL_IS_NEWLINE_HPP
#define CJDB_FUNCTIONAL_IS_NEWLINE_HPP

#include "cjdb/concepts/core/character.hpp"

namespace cjdb {
   namespace detail_is_newline_fn {
      struct is_newline_fn {
         template<class CharT>
         constexpr bool operator()(CharT const a) const noexcept
         { return a == '\n' or a == '\f'; }

         template<class CharT>
         constexpr bool operator()(CharT const a, CharT const b) const noexcept
         {
            return a == static_cast<CharT>('\n') or
                   a == static_cast<CharT>('\f') or
                  (a == static_cast<CharT>('\r') and b == static_cast<CharT>('\n'));
         }
      };
   } // namespace detail_is_newline_fn

   inline constexpr auto is_newline = detail_is_newline_fn::is_newline_fn{};
} // namespace cjdb

#endif //