#!/bin/bash

# remove Build/ for a clean build
for argument in $@
do
  if [ "$argument" == "clean" ]; then
    rm -rf Build
  fi
done

# build
#mkdir -p Build && cd Build && rm -rf && cmake .. && make && cd -
mkdir -p Build && cd Build && rm -rf && cmake -DCMAKE_BUILD_TYPE=Debug .. && make && cd -
