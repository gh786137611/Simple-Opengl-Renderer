
cmake_minimum_required(VERSION 2.8)
project(example_TextureCube)

set(CMAKE_CXX_STANDARD 11)
include_directories(../../sources)

add_executable(example_TextureCube main.cpp)

add_subdirectory(../../sources SGL.a)
target_link_libraries(example_TextureCube GLEW GL glut SGL)