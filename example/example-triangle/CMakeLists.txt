
cmake_minimum_required(VERSION 2.8)
project(example_triangle)

set(CMAKE_CXX_STANDARD 11)
include_directories(../../sources)

add_executable(example_triangle main.cpp)

add_subdirectory(../../sources SGL.a)
target_link_libraries(example_triangle GLEW GL glut SGL)