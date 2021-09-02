cmake_minimum_required(VERSION 3.16)
project(gbtest)

find_package(raylib 3.0 REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(gbtest
        src/main.cpp
        src/cpu/LR35902.cpp
        src/cpu/LR35902.h
        src/platform/bus/Bus.cpp
        src/platform/bus/Bus.h
        src/platform/GameBoy.cpp
        src/platform/GameBoy.h
        src/platform/bus/BusProvider.h src/memory/Memory.cpp src/memory/Memory.h)

target_link_libraries(gbtest raylib)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif ()