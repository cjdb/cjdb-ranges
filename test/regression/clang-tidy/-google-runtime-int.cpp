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

/// This test checks that google-runtime-int is *disabled*.
/// \see https://clang.llvm.org/extra/clang-tidy/checks/google-runtime-int.html.

int main()
{
   constexpr auto not_int16 = short{0};
   (void)not_int16;

   constexpr auto not_uint16 = static_cast<unsigned short>(0);
   (void)not_uint16;

   constexpr auto not_int32 = 0L;
   (void)not_int32;

   constexpr auto not_uint32 = 0UL;
   (void)not_uint32;

   constexpr auto not_int64 = 0LL;
   (void)not_int64;

   constexpr auto not_uint64 = 0ULL;
   (void)not_uint64;
}
