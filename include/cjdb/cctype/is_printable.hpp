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
#ifndef CJDB_FUNCTIONAL_IS_PRINTABLE_HPP
#define CJDB_FUNCTIONAL_IS_PRINTABLE_HPP

namespace cjdb {
   namespace detail_is_printable_fn {
      struct is_printable_fn {
         template<class CharT>
         constexpr bool operator()(CharT const a) const noexcept
         { return a >= static_cast<CharT>(' '); }
      };
   } // namespace detail_is_printable_fn

   inline constexpr auto is_printable = detail_is_printable_fn::is_printable_fn{};
} // namespace cjdb

#endif // CJDB_FUNCTIONAL_IS_PRINTABLE_HPP