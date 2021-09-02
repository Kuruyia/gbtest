cmake_minimum_required(VERSION 3.16)
project(gbtest)

find_package(raylib 3.0 REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(gbtest
        src/main.cpp
        src/LR35902.cpp
        src/LR35902.h
        src/Bus.cpp
        src/Bus.h
        src/GameBoy.cpp
        src/GameBoy.h
        )

target_link_libraries(gbtest raylib)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif ()