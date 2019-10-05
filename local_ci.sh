#!/bin/bash
# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
BUILD_TYPE=${1}

bash config/scripts/pre-install.sh ${BUILD_TYPE}      && \
bash config/scripts/conan-install.sh ${BUILD_TYPE}    && \
bash config/scripts/build-configure.sh ${BUILD_TYPE}  && \
bash config/scripts/build.sh ${BUILD_TYPE}            && \
bash config/scripts/test.sh ${BUILD_TYPE}
