#!/bin/bash

usage() {
  echo "Usage:"
  echo "./build.sh <ARCH_TYPE>"
  echo "ARCH_TYPE: [x86|x64]"
}

if [ "$#" -lt 1 ]; then
  usage
  exit
fi

# remove Build/ for a clean build
ARCH_TYPE="x64"
for argument in $@
do
  if [ "$argument" == "x86" ]; then
    ARCH_TYPE="x86"
  fi
  if [ "$argument" == "x64" ]; then
    ARCH_TYPE="x64"
  fi
done

# build
#mkdir -p Build && cd Build && rm -rf && cmake .. && make && cd -
mkdir -p Build && cd Build && rm -rf && cmake -DArchType=${ARCH_TYPE} -DCMAKE_BUILD_TYPE=Debug .. && make && cd -
