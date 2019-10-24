# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
from conans import ConanFile, CMake, RunEnvironment, tools

class RangesConan(ConanFile):
    name = "ranges"
    description = "A reference implementation for C++next features."
    author = "Christopher Di Bella"
    license = "Apache-2.0 WITH LLVM-exception"
    url = "https://github.com/cjdb/cjdb-ranges.git"
    version = "head"
    topics = ("cpp", "c++", "ranges")
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
    requires = ("constexpr-contracts/head@cjdb/development")
    exports_sources = ("include/*", "LICENSE.md", "CMakeLists.txt", "test/*", "config/cmake/*")
    build_policy = "missing"
    no_copy_source = True

    def build(self):
        cmake = CMake(self)
        cmake.definitions["CJDB_RANGES_ENABLE_CLANG_TIDY"] = self.options.enable_clang_tidy
        cmake.definitions["CJDB_RANGES_CLANG_TIDY_PATH"] = self.options.clang_tidy_path

        cmake.configure()
        cmake.build()

        env_build = RunEnvironment(self)
        with tools.environment_append(env_build.vars):
            cmake.test(output_on_failure=True)

        cmake.install()

    def package(self):
        self.copy("include/")
        self.copy("LICENSE.md", dst="licenses", ignore_case=True, keep_path=False)

    def package_info(self):
        self.info.header_only()
