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
   name = "amcpp-gp2"
   version = "1.0"
   settings = "os", "compiler", "arch", "build_type"
   generators = "cmake", "cmake_paths", "virtualrunenv"
   build_requires = "catch2/[>=2.3.0]@bincrafters/stable", "google-benchmark/1.4.1@mpusz/stable"
   requires = "gsl_microsoft/[>=1.0.0]@bincrafters/stable"
   exports_sources = "CMakeLists.txt", ".clang*", "test/*", "src/*", "cmake/*"
   no_copy_source = True

   def build(self):
      cmake = CMake(self)

      cmake.configure()
      cmake.build()

      env_build = RunEnvironment(self)
      with tools.environment_append(env_build.vars):
         cmake.test()

   def package_info(self):
      self.env_info.PATH.append(os.path.join(self.package_folder, "bin"))
