# cmake-mxnet-template

## Checkout MXNET 

```
git clone --recursive https://github.com/apache/incubator-mxnet mxnet
cd mxnet
# git checkout SPECIFIC_TAG
git submodule update --init --recursive
```

cmake project template that includes mxnet, leptonica, opencv preconfigured

## CMAKE Configuration

Edit `CMakeLists.txt` in root directory of the project and change `MXNET_ROOT` parameter to point to your installation directory.

```bash
SET(ENV{MXNET_ROOT} "/home/greg/dev/3rdparty/mxnet")
```

Project has following dependencies

* MxNet - FindMxNet.cmake
* Leptonica - FindLeptonica.cmake
* OpenCV - FindOpenCV.cmake

## Building MXNET

Primary source  [https://mxnet.apache.org/get_started/build_from_source]

Make
```bash
#!/bin/sh
rm -rf build
mkdir -p build && cd build
cmake  -DUSE_CUDA=OFF -DUSE_OPENMP=ON -DUSE_OPENCV=ON -DUSE_MKL_IF_AVAILABLE=OFF -DCMAKE_BUILD_TYPE=Debug ..
make -j USE_CPP_PACKAGE=1
make install
```

Release with CUDA enabled 
```bash
#!/bin/sh
rm -rf build
mkdir -p build && cd build
cmake -DUSE_CPP_PACKAGE=ON -DUSE_CUDA=ON -DUSE_CUDNN=ON  -DUSE_TVM_OP=OFF -DUSE_OPENMP=ON -DUSE_OPENCV=ON -DUSE_MKL_IF_AVAILABLE=OFF -DCMAKE_BUILD_TYPE=Release .. -GNinja ..
```


Ninja build

```bash
#!/bin/sh
rm -rf build
mkdir -p build && cd build
cmake -DUSE_CPP_PACKAGE=ON -DUSE_CUDA=OFF -DUSE_OPENMP=ON -DUSE_OPENCV=ON -DUSE_MKL_IF_AVAILABLE=OFF -DCMAKE_BUILD_TYPE=Debug .. -GNinja ..

# This uses CMake's Build Tool Mode, which is an abstract interface for a couple of commands to the native build tool (e.g. make or Ninja) 
cmake --build . --config Debug -j 24

# Build and Install
cmake --build . --target install  --config Debug -j 24
``

After the MXNET install you should have have libraries in following locations

```txt
    -- Installing: /usr/local/lib/libmxnet.so
    -- Installing: /usr/local/include/mxnet
    -- Installing: /usr/local/include/mxnet-cpp
```


## Dependencies

```
apt-get -qq update
apt-get install --no-install-recommends \
  software-properties-common apt-transport-https \
  build-essential cmake libjemalloc-dev \
  libatlas-base-dev liblapack-dev liblapacke-dev libopenblas-dev \
  libcurl4-openssl-dev libzmq3-dev ninja-build libhdf5-dev libomp-dev
```

* Leptonica   :: sudo apt-get install libleptonica-dev
* OpenCV      :: https://github.com/milq/milq/blob/master/scripts/bash/install-opencv.sh
* mxnet

## Resources

https://cwiki.apache.org/confluence/pages/viewpage.action?pageId=95651665
https://nextjournal.com/mpd/compiling-mxnet

Linking static library (error or bug?) to load python trained model [https://github.com/apache/incubator-mxnet/issues/13870]
