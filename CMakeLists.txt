# Project
cmake_minimum_required(VERSION 3.16)
project(gbtest)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra)

# Subdirectories
add_subdirectory(src)