
cmake_minimum_required(VERSION 2.8)
project(example_line)

set(CMAKE_CXX_STANDARD 11)
include_directories(../../sources)

add_executable(example_line main.cpp)

add_subdirectory(../../sources SGL.a)
target_link_libraries(example_line GLEW GL glut SGL)