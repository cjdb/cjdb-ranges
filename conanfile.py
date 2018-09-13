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

class Project_name(ConanFile):
    name = "cjdblib"
    description = "A reference implementation for C++next features."
    author = "Christopher Di Bella"
    license = "Apache License, Version 2.0"
    url = "https://github.com/cjdb/cjdblib.git"
    version = "1.0"
    topics = ("cpp", "c++", "cmake", "conan")
    settings = ("os", "compiler", "arch", "build_type")
    generators = ("cmake", "cmake_paths", "virtualrunenv")
    options = {
        "code_coverage": ["Off", "gcov", "LLVMSourceCoverage"],
        "required_sanitizers": "ANY",
        "optional_sanitizers": "ANY",
        "enable_clang_tidy": ["Off", "On"],
        "clang_tidy_path": "ANY"
    }
    default_options = {
        "code_coverage": "Off",
        "required_sanitizers": "",
        "optional_sanitizers": "Address;Undefined;ControlFlowIntegrity",
        "enable_clang_tidy": "Off",
        "clang_tidy_path": "/usr/bin/clang-tidy"
    }
    requires = ("doctest/2.2.0@bincrafters/stable")
    exports_sources = (".clang*", "cmake/*", "CMakeLists.txt", "include/*",
                       "source/*", "test/*", "LICENSE.md")
    build_policy = "always"
    no_copy_source = False

    def define_from_options(self, cmake):
        cmake_key = "{}_{}".format(self.name, "CODE_COVERAGE")
        cmake.definitions[cmake_key] = self.options.code_coverage

        cmake_key = "{}_{}".format(self.name, "REQUIRED_SANITIZERS")
        cmake.definitions[cmake_key] = self.options.required_sanitizers

        cmake_key = "{}_{}".format(self.name, "OPTIONAL_SANITIZERS")
        cmake.definitions[cmake_key] = self.options.optional_sanitizers

        cmake_key = "{}_{}".format(self.name, "ENABLE_CLANG_TIDY")
        cmake.definitions[cmake_key] = self.options.enable_clang_tidy

        cmake_key = "{}_{}".format(self.name, "CLANG_TIDY_PATH")
        cmake.definitions[cmake_key] = self.options.clang_tidy_path

        return cmake

    def build(self):
        cmake = CMake(self)

        cmake = self.define_from_options(cmake)
        cmake.configure()
        cmake.build()

        env_build = RunEnvironment(self)
        with tools.environment_append(env_build.vars):
            cmake.test(output_on_failure=True)

    def package(self):
        cmake = CMake(self)

        cmake.install()
        self.copy(
            "LICENSE.md", dst="licenses", ignore_case=True, keep_path=False)

    def package_info(self):
        self.env_info.PATH.append(os.path.join(self.package_folder, "bin"))
