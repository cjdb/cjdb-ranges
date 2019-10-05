#!/bin/bash
# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#

format() {
   cd $1
   for i in `ls $1`; do
      if [[ -d $i ]]; then
         format `pwd`/$i
      elif [[ ${i: -4} == ".cpp" || ${i: -4} == ".cxx" || ${i: -3} == ".cc" || ${i: -2} == ".c" || \
              ${i: -4} == ".hpp" || ${i: -4} == ".hxx" || ${i: -3} == ".hh" || ${i: -2} == ".h" ]]
      then
         clang-format -i -style=file -- "$i"
      fi
   done
   cd ..
}

which clang-format
if [[ $? -ne 0 ]]; then
   echo "Could not find clang-format in PATH"
   exit 1
fi

format `pwd`/include
format `pwd`/source
format `pwd`/test

if [[ -z `git status --porcelain --untracked-files=no` ]]; then
   echo "No changes were identified after formatting: now pushing to remote."
   exit 0
else
   echo "Changes were identified after formatting: please commit these changes and re-try pushing."
   git status -v
   exit 1
fi
