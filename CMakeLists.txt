cmake_minimum_required(VERSION 2.8)
project(SGLRender)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(./ current_folder_source)
add_executable(SGLRender  ${current_folder_source})


target_link_libraries(SGLRender GLEW GL glut)
