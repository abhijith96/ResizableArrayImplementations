cmake_minimum_required(VERSION 3.22)
project(ResizableArrays CXX)
set(CMAKE_CXX_STANDARD 17)

option(BUILD_TESTS "Build test programs" OFF)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/")
add_subdirectory(src)