cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)

project(SGL)
aux_source_directory(. current_folder_sources)
add_library(${PROJECT_NAME} STATIC ${current_folder_sources})
