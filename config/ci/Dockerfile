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
FROM ubuntu:bionic

RUN apt update
RUN apt upgrade -y
RUN apt install software-properties-common
RUN apt-add-repository ppa:ubuntu-toolchain-r/test
RUN apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 15CF4D18AF4F7421
RUN apt-add-repository 'deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-8 main'
RUN apt update

# Install tools
RUN apt install clang-8 clang++-8 lld-8
RUN apt install ninja-build git python3 python3-pip

# Python config
RUN python3 -m pip install pip --upgrade
RUN python3 -m pip install cmake conan

# LLVM install
WORKDIR /tmp
RUN git clone https://github.com/saarraz/clang-concepts-monorepo.git

WORKDIR /tmp/clang-concepts-monorepo
RUN git checkout concepts

WORKDIR /tmp/build
RUN cmake -GNinja ../clang-concepts-monorepo/llvm                                            \
	-DCMAKE_C_COMPILER=`which clang-8`                                                        \
	-DCMAKE_CXX_COMPILER=`which clang++-8`                                                    \
	-DCMAKE_BUILD_TYPE=Release                                                                \
	-DCMAKE_INSTALL_PREFIX="/opt/clang-concepts"                                              \
	-DLLVM_INCLUDE_EXAMPLES=Off                                                               \
	-DLLVM_INCLUDE_BENCHMARKS=Off                                                             \
	-DLLVM_INCLUDE_TESTS=Off                                                                  \
	-DLLVM_CXX_STD="c++14"                                                                    \
	-DLLVM_ENABLE_WARNINGS=Off                                                                \
	-DLLVM_ENABLE_LTO=Thin                                                                    \
	-DLLVM_PARALLEL_LINK_JOBS=8                                                               \
	-DLLVM_ENABLE_LLD=On                                                                      \
	-DLLVM_TARGETS_TO_BUILD="X86"                                                             \
	-DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra;compiler-rt;libcxx;libcxxabi;lld;polly"   \
	-DLLVM_ENABLE_BINDINGS=Off
RUN ninja
RUN ninja install

WORKDIR /
RUN rm -rf /tmp/*
RUN apt remove clang-8 clang++-8 lld-8
