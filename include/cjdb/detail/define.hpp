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
#ifndef CJDB_DETAIL_DEFINE_HPP
#define CJDB_DETAIL_DEFINE_HPP

#define CJDB_NOEXCEPT_RETURN(...)   \
   noexcept(noexcept(__VA_ARGS__))  \
   { return __VA_ARGS__; }          \


#define CJDB_NOEXCEPT_REQUIRES_RETURN(...) \
   noexcept(noexcept(__VA_ARGS__))         \
   requires requires { __VA_ARGS__ }       \
   { return (__VA_ARGS__); }               \


#define CJDB_EXPECTS(...) {          \
      if (not bool((__VA_ARGS__))) { \
         std::terminate();           \
      }                              \
}                                    \


#define CJDB_ENSURES(...) CJDB_EXPECTS(__VA_ARGS__)

#define CJDB_ASSERT(...) CJDB_EXPECTS(__VA_ARGS__)

#endif // CJDB_DETAIL_DEFINE_HPP
