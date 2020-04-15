#!/bin/sh

rm -rf build
mkdir -p build && cd build

# CMAKE build
#cmake ..
#cmake --build . --target install

# Make build
cmake -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON  -DCMAKE_BUILD_TYPE=Debug ..
make  -j8 && make install

# Ninja build
#cmake -G Ninja -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON  -DCMAKE_BUILD_TYPE=Debug ..
#ninja -C . -j $(nproc)
