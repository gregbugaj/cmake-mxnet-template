#!/bin/sh

rm -rf build
mkdir -p build && cd build

cmake ..
#cmake --build .
cmake --build . --target install

#cmake -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON  -DCMAKE_BUILD_TYPE=Debug ..
#make  -j8 && make install

