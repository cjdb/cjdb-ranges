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
#ifdef CJDB_DETAIL_DEFINE_HPP
   #undef CJDB_DETAIL_DEFINE_HPP
#else
   #error "\"cjdb/detail/undef.hpp\" can only be included in a context where "
          "\"cjdb/detail/define.hpp\" has already been included."
#endif // CJDB_DETAIL_DEFINE_HPP

#ifdef CJDB_NOEXCEPT_RETURN
   #undef CJDB_NOEXCEPT_RETURN
#endif // CJDB_NOEXCEPT_RETURN

#ifdef CJDB_NOEXCEPT_REQUIRES_RETURN
   #undef CJDB_NOEXCEPT_REQUIRES_RETURN
#endif // CJDB_NOEXCEPT_REQUIRES_RETURN

#ifdef CJDB_EXPECTS
   #undef CJDB_EXPECTS
#endif // CJDB_EXPECTS

#ifdef CJDB_ENSURES
   #undef CJDB_ENSURES
#endif // CJDB_ENSURES

#ifdef CJDB_ASSERT
   #undef CJDB_ASSERT
#endif // CJDB_ASSERT
