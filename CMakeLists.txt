cmake_minimum_required(VERSION 3.16)
project(gbtest)

set(CMAKE_CXX_STANDARD 14)
set(BUILD_SHARED_LIBS FALSE)

add_subdirectory(SFML)

include_directories(SFML/include)

add_executable(gbtest main.cpp LR35902.cpp LR35902.h Bus.cpp Bus.h)
target_link_libraries(gbtest sfml-window sfml-network sfml-graphics sfml-audio sfml-system)