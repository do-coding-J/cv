#!/bin/bash

# opencv
if [ ! -d opencv ]; then
    mkdir opencv
fi

cd opencv

# CMakeLists.txt 파일 생성 및 작성
if [ ! -e CMakeLists.txt ]; then
    touch CMakeLists.txt
    cat <<EOF >CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(cv)
include(FetchContent)
FetchContent_Declare(
    opencv_contrib
    GIT_REPOSITORY https://github.com/opencv/opencv_contrib.git
    GIT_TAG 4.9.0
)
FetchContent_MakeAvailable(opencv_contrib)
FetchContent_Declare(
    opencv
    GIT_REPOSITORY https://github.com/opencv/opencv.git
    GIT_TAG 4.9.0
)
set(BUILD_SHARED_LIBS OFF)
# include(config_set.cmake)
set(CMAKE_INSTALL_PREFIX ${PWD})
set(EXTRA_MODULE_PATH \${opencv_contrib_SOURCE_DIR}/modules)
FetchContent_MakeAvailable(opencv)
EOF
fi

# check opencv lib

if [ ! -d include]; then
    cmake -Bbuild -G"Unix Makefiles"
    make -Cbuild -j8
    make install -Cbuild/_deps/opencv-build -j8
fi

# # application
cd ..
cmake -Bbuild -G"Unix Makefiles"
make -Cbuild -j8
