cmake_minimum_required(VERSION 2.8)
project(SGLRender)

set(CMAKE_CXX_STANDARD 11)
include_directories(../../sources)

add_executable(SGLRender main.cpp)

add_subdirectory(../../sources SGL.a)
target_link_libraries(SGLRender GLEW GL glut SGL)
