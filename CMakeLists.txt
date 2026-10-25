cmake_minimum_required(VERSION 3.14)

project(helloTest)

set(OpenCV_DIR "/usr/lib/x86_64-linux-gnu/cmake/opencv4")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(./source ./includes)

add_executable(helloTest source/demo.cpp source/main.cpp source/complex.cpp)
target_link_libraries(helloTest ${OpenCV_LIBS})
