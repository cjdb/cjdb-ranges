# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
FROM ubuntu:bionic

RUN apt update                                                                               && \
    apt install -y software-properties-common                                                && \
    apt-add-repository ppa:ubuntu-toolchain-r/test                                           && \
    apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 15CF4D18AF4F7421       && \
    apt-add-repository 'deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-8 main'        && \
    apt upgrade -y                                                                           && \
    apt update                                                                               && \
    apt install -y gcc-8 g++-8 clang-8 clang++-8 lld-8 ninja-build git python3 python3-pip   && \
    python3 -m pip install pip --upgrade                                                     && \
    python3 -m pip install cmake conan

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
RUN apt remove -y clang-8 clang++-8 lld-8 && apt autoremove -y
