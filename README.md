# cmake-mxnet-template

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

Ninja build

```bash
#!/bin/sh
rm -rf build
mkdir -p build && cd build
cmake -DUSE_CPP_PACKAGE=ON -DUSE_CUDA=OFF -DUSE_OPENMP=ON -DUSE_OPENCV=ON -DUSE_MKL_IF_AVAILABLE=OFF -DCMAKE_BUILD_TYPE=Debug .. -GNinja ..

# This uses CMake's Build Tool Mode, which is an abstract interface for a couple of commands to the native build tool (e.g. make or Ninja) 
cmake --build . --config Debug

# Build and Install
cmake --build . --target install  --config Debug
``

After the MXNET install you should have have libraries in following locations

```txt
    -- Installing: /usr/local/lib/libmxnet.so
    -- Installing: /usr/local/include/mxnet
    -- Installing: /usr/local/include/mxnet-cpp
```


## Resources

https://cwiki.apache.org/confluence/pages/viewpage.action?pageId=95651665
https://nextjournal.com/mpd/compiling-mxnet

Linking static library (error or bug?) to load python trained model [https://github.com/apache/incubator-mxnet/issues/13870]
