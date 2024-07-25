#!/bin/bash

# opencv
if [ ! -d opencv ]; then
    mkdir opencv
fi

cd opencv

# get dep
if [ ! -d downloads ]; then
    mkdir downloads
fi

cd downloads

## openjpeg (in source build)
# git clone -b v2.5.2 git@github.com:uclouvain/openjpeg.git
# cd openjpeg
# cmake -Bbuild -DCMAKE_BUILDTYPE=Release
# make -Cbuild -j8

## openBLAS




# CMakeLists.txt 파일 생성 및 작성
if [ ! -e CMakeLists.txt ]; then
    touch CMakeLists.txt
    cat <<EOF >CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(cv)
set(CMAKE_INSTALL_PREFIX \${CMAKE_CURRENT_SOURCE_DIR})
include(FetchContent)
FetchContent_Declare(
    opencv
    GIT_REPOSITORY https://github.com/opencv/opencv.git
    GIT_TAG 4.9.0
)
FetchContent_Declare(
    opencv_contrib
    GIT_REPOSITORY https://github.com/opencv/opencv_contrib.git
    GIT_TAG 4.9.0
)
set(BUILD_SHARED_LIBS OFF)
set(EXTRA_MODULES_PATH \${opencv_contrib_SOURCE_DIR}/modules)
FetchContent_MakeAvailable(opencv opencv_contrib)
EOF
fi


# check opencv lib
if [ ! -d include ]; then
    cmake -Bbuild -G"Unix Makefiles"
    cmake -Bbuild -G"Unix Makefiles"
    make -Cbuild -j$(nproc) # opencv source
    make install -Cbuild/_deps/opencv-build -j$(nproc) # install
fi

# # application
# cd ..
# cmake -Bbuild -G"Unix Makefiles"
# make -Cbuild -j$(nproc)
