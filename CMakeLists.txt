cmake_minimum_required(VERSION 3.20)

project(cv)

find_package(OpenCV 4.9.0 EXACT REQUIRED PATHS opencv/lib/cmake/opencv4)

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE opencv/include/opencv4)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
