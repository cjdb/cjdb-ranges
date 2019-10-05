# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
from conans import ConanFile, CMake, RunEnvironment, tools
import os

class Project_name(ConanFile):
    name = "cjdblib"
    description = "A reference implementation for C++next features."
    author = "Christopher Di Bella"
    license = "Apache-2.0 WITH LLVM-exception"
    url = "https://github.com/cjdb/cjdblib.git"
    version = "1.0"
    topics = ("cpp", "c++", "cmake", "conan")
    settings = ("os", "compiler", "arch", "build_type")
    generators = ("cmake", "cmake_paths", "virtualrunenv")
    options = {
        "enable_clang_tidy": ["Off", "On"],
        "clang_tidy_path": "ANY"
    }
    default_options = {
        "enable_clang_tidy": "Off",
        "clang_tidy_path": "/usr/bin/clang-tidy"
    }
    requires = ("contracts-consolation/0.1@cjdb/experimental")
    exports_sources = (".clang*", "cmake/*", "CMakeLists.txt", "include/*",
                       "source/*", "test/*", "LICENSE.md")
    build_policy = "always"
    no_copy_source = False

    def build(self):
        cmake = CMake(self)

        cmake.definitions[f"{self.name}_ENABLE_CLANG_TIDY"] = self.options.enable_clang_tidy
        cmake.definitions[f"{self.name}_CLANG_TIDY_PATH"] = self.options.clang_tidy_path
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
