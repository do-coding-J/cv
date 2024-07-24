cmake_minimum_required(VERSION 3.20)

project(cv)

find_package(Eigen3 REQUIRED)
find_package(OpenCV 4.9.0 EXACT REQUIRED PATHS ${CMAKE_CURRENT_SOURCE_DIR}/opencv/lib/cmake/opencv4)

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/opencv/include/opencv4)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
