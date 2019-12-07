
cmake_minimum_required(VERSION 2.8)
project(example_texture2d)

set(CMAKE_CXX_STANDARD 11)
include_directories(../../sources)

add_executable(example_texture2d main.cpp)

add_subdirectory(../../sources SGL.a)
target_link_libraries(example_texture2d GLEW GL glut SGL)