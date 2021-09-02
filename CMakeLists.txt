cmake_minimum_required(VERSION 3.16)
project(gbtest)

set(CMAKE_CXX_STANDARD 14)
set(BUILD_SHARED_LIBS FALSE)

add_subdirectory(SFML)

include_directories(SFML/include)

add_executable(gbtest src/main.cpp src/LR35902.cpp src/LR35902.h src/Bus.cpp src/Bus.h src/GameBoy.cpp src/GameBoy.h src/DebugScreen.cpp src/DebugScreen.h)
target_link_libraries(gbtest sfml-window sfml-network sfml-graphics sfml-audio sfml-system)