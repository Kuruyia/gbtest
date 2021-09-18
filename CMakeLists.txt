cmake_minimum_required(VERSION 3.16)
project(gbtest)

find_package(raylib 3.0 REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(gbtest
        src/cpu/interrupts/InterruptController.cpp
        src/cpu/interrupts/InterruptController.h
        src/cpu/interrupts/InterruptType.h
        src/cpu/LR35902.cpp
        src/cpu/LR35902.h
        src/exceptions/bus/BusLockedAddressException.cpp
        src/exceptions/bus/BusLockedAddressException.h
        src/exceptions/bus/BusNoHandlerException.cpp
        src/exceptions/bus/BusNoHandlerException.h
        src/memory/Memory.cpp
        src/memory/Memory.h
        src/platform/bus/Bus.cpp
        src/platform/bus/Bus.h
        src/platform/GameBoy.cpp
        src/platform/GameBoy.h
        src/platform/bus/BusProvider.h
        src/platform/bus/BusRequestSource.h
        src/ppu/fifo/BackgroundFetcher.cpp
        src/ppu/fifo/BackgroundFetcher.h
        src/ppu/fifo/Fetcher.cpp
        src/ppu/fifo/Fetcher.h
        src/ppu/fifo/FetcherState.h
        src/ppu/fifo/FIFOPixelData.h
        src/ppu/modes/DrawingPPUMode.cpp
        src/ppu/modes/DrawingPPUMode.h
        src/ppu/modes/HBlankPPUMode.cpp
        src/ppu/modes/HBlankPPUMode.h
        src/ppu/modes/OAMSearchPPUMode.cpp
        src/ppu/modes/OAMSearchPPUMode.h
        src/ppu/modes/PPUMode.cpp
        src/ppu/modes/PPUMode.h
        src/ppu/modes/PPUModeManager.cpp
        src/ppu/modes/PPUModeManager.h
        src/ppu/modes/PPUModeType.h
        src/ppu/modes/VBlankPPUMode.cpp
        src/ppu/modes/VBlankPPUMode.h
        src/ppu/oam/OAM.cpp
        src/ppu/oam/OAM.h
        src/ppu/oam/OAMDMA.cpp
        src/ppu/oam/OAMDMA.h
        src/ppu/oam/OAMEntry.h
        src/ppu/vram/VRAM.cpp
        src/ppu/vram/VRAM.h
        src/ppu/vram/VRAMTileData.cpp
        src/ppu/vram/VRAMTileData.h
        src/ppu/vram/VRAMTileMaps.cpp
        src/ppu/vram/VRAMTileMaps.h
        src/ppu/ColorUtils.cpp
        src/ppu/ColorUtils.h
        src/ppu/PPU.cpp
        src/ppu/PPU.h
        src/ppu/PPURegisters.h
        src/utils/Tickable.h
        src/main.cpp)

target_link_libraries(gbtest raylib)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif ()