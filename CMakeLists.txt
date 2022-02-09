# Project
cmake_minimum_required(VERSION 3.16)
project(gbtest)

set(CMAKE_CXX_STANDARD 17)

if (${CMAKE_CXX_COMPILER_ID} EQUAL MSVC)
    add_compile_options(/Wall)
else ()
    add_compile_options(-Wall -Wextra)
endif ()

# Subdirectories
add_subdirectory(src)