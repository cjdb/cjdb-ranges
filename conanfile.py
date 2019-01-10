#
#  Copyright Christopher Di Bella
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
from conans import ConanFile, CMake, RunEnvironment, tools
import os

class RangesConan(ConanFile):
   name = "cjdb"
   version = "0.1"
   license = "Apache Licence, Version 2.0"
   author = "Christopher Di Bella <cjdb.ns@gmail.com>"
   url = "https://github.com/cjdb/clang-concepts-ranges"
   description = "A GCC and Clang-compatible implementation of Ranges, using C++20 concepts."
   topics = ("cplusplus", "cpp", "c++20", "ranges")
   settings = "os", "compiler", "arch", "build_type"
   generators = "cmake", "cmake_paths", "virtualrunenv"
   build_requires = "catch2/[>=2.3.0]@bincrafters/stable"
   requires = "gsl_microsoft/[>=1.0.0]@bincrafters/stable"
   exports_sources = "CMakeLists.txt", ".clang*", "test/*", "src/*", "cmake/*"
   no_copy_source = True

   def build(self):
      cmake = CMake(self)

      cmake.configure()
      cmake.build()

      env_build = RunEnvironment(self)
      with tools.environment_append(env_build.vars):
         if self.should_test:
            self.run("ctest -j %s --output-on-failure" % tools.cpu_count())

   def package_info(self):
      self.env_info.PATH.append(os.path.join(self.package_folder, "bin"))
