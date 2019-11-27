# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
FROM ubuntu:bionic

COPY --from=cjdb/gcc-trunk /usr/local /usr/local
COPY --from=cjdb/clang-concepts /usr/local/ /usr/local

RUN apt update
RUN apt dist-upgrade -y
RUN apt install -y python3 python3-pip ninja-build binutils libz3-dev libedit-dev swig
RUN python3 -m pip install pip --upgrade
RUN python3 -m pip install cmake conan

ENV PATH="/usr/local/bin:$PATH" LD_LIBRARY_PATH="/usr/local/lib64:/usr/local/lib:/usr/local/libexec"
RUN echo "#include <iostream>\n\
\n\
template<typename T>\n\
requires (sizeof(T) == sizeof(int))\n\
constexpr void hello(T t)\n\
{\n\
	std::cout << \"Hello, \" << t << '\\\\n';\n\
}\n\
\n\
int main()\n\
{\n\
	hello(42);\n\
}\n\
" >/tmp/hello.cpp
RUN cat /tmp/hello.cpp
RUN g++ -std=c++2a /tmp/hello.cpp -o /tmp/a.out -fuse-ld=gold
RUN clang++ -std=c++2a /tmp/hello.cpp -o /tmp/a.out -fuse-ld=lld
RUN clang++ -std=c++2a /tmp/hello.cpp -o /tmp/a.out -stdlib=libc++ -cxx-isystem /usr/local/include/c++/v1 -fuse-ld=lld -L /usr/local/lib/ -Wl,-rpath,/usr/local/lib/ -lc++abi
RUN cmake --version

WORKDIR /tmp
RUN conan new Hello/0.1 -t

WORKDIR /tmp/Hello/build
RUN conan install .. || true
RUN sed -i '53s/"9.2"/"9.2", "10"/' ~/.conan/settings.yml
RUN sed -i '69s/"8"/"8", "9", "10"/' ~/.conan/settings.yml

WORKDIR /
RUN rm -rf /tmp/*
