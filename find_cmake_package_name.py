#!/usr/bin/python
#
#  Copyright 2019 Christopher Di Bella
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
import argparse
import re

import sys
import subprocess

from os import environ
from os import walk
from os import path


def parse_args():
    """Parses the program's arguments."""

    parser = argparse.ArgumentParser(
        description="Find a package's CMake name.")

    parser.add_argument(
        '--package',
        metavar='package',
        nargs=1,
        help='The name of the package Conan has installed.')
    parser.add_argument(
        '--conan-root',
        metavar='conan_root',
        nargs=1,
        default='{}/.conan/data'.format(environ['HOME']),
        help='The directory to search for the package name.')
    args = parser.parse_args()
    return args.package[0], args.conan_root


def split_package_ref(package_ref):
    """Split the package reference into its name, version, repository, and branch.

    package_ref -- The Conan package reference to split.
    """
    match = re.match(
        r"""([^/]+)/  # package name
                         ([^@]+)@  # version
                         ([^/]+)/  # repository
                         (.+)      # branch name""", package_ref, re.VERBOSE)

    if match:
        package_name = match.group(1)
        version = match.group(2)
        repository = match.group(3)
        branch = match.group(4)
    else:
        raise RuntimeError(
            "Package reference \"{}\" is invalid.".format(package_name))

    return package_name, version, repository, branch


def find_path(conan_root, package_info):
    """Confirm that the path to the exists.

    conan_root -- The root directory for the Conan metadata.

    package_info -- The split details of the package reference.
    """

    package_name, version, repository, branch = package_info
    package_path = "{}/{}/{}/{}/{}".format(conan_root, package_name, version,
                                           repository, branch)

    if not path.isdir(package_path):
        print(
            "Error: path name \"{}\" is not a directory.".format(package_path),
            file=sys.stderr)
        exit(1)
    return package_path


def find_configurations(package_path):
    """Find CMake configuration files.

    package_path -- The directory path to start searching from.
    """

    config_suffix = re.compile('(C|-c)onfig.cmake$')
    f = list()
    for _, _, files in walk(package_path):
        f += list(filter(lambda file: config_suffix.search(file), files))
    f = list(dict.fromkeys(f))
    return list(map(lambda i: config_suffix.sub('', i), f))


def main():
    package_ref, conan_root = parse_args()
    package_path = find_path(conan_root, split_package_ref(package_ref))

    configurations = find_configurations(package_path)

    for i in configurations:
        print(i)
    exit(len(configurations) == 0)


if __name__ == "__main__":
    main()
