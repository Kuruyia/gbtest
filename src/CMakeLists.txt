# Source files
set(SOURCE_FILES
        apu/channels/APUChannel.cpp
        apu/channels/APUChannel.h
        apu/channels/APUChannel2.cpp
        apu/channels/APUChannel2.h
        apu/units/AudioPulseWave.cpp
        apu/units/AudioPulseWave.h
        apu/units/PulseWavePatternDuty.h
        apu/APU.cpp
        apu/APU.h
        apu/APURegisters.h
        cpu/interrupts/InterruptController.cpp
        cpu/interrupts/InterruptController.h
        cpu/interrupts/InterruptType.h
        cpu/LR35902.cpp
        cpu/LR35902.h
        exceptions/bus/BusLockedAddressException.cpp
        exceptions/bus/BusLockedAddressException.h
        exceptions/bus/BusNoHandlerException.cpp
        exceptions/bus/BusNoHandlerException.h
        joypad/Joypad.cpp
        joypad/Joypad.h
        joypad/JoypadState.h
        memory/Memory.cpp
        memory/Memory.h
        platform/bus/Bus.cpp
        platform/bus/Bus.h
        platform/GameBoy.cpp
        platform/GameBoy.h
        platform/GameBoyFrequencies.h
        platform/bus/BusProvider.h
        platform/bus/BusRequestSource.h
        ppu/fifo/BackgroundFetcher.cpp
        ppu/fifo/BackgroundFetcher.h
        ppu/fifo/Fetcher.cpp
        ppu/fifo/Fetcher.h
        ppu/fifo/FetcherState.h
        ppu/fifo/FIFOPixelData.h
        ppu/fifo/PixelFIFO.h
        ppu/fifo/SpriteFetcher.cpp
        ppu/fifo/SpriteFetcher.h
        ppu/framebuffer/Framebuffer.cpp
        ppu/framebuffer/Framebuffer.h
        ppu/modes/DrawingPPUMode.cpp
        ppu/modes/DrawingPPUMode.h
        ppu/modes/HBlankPPUMode.cpp
        ppu/modes/HBlankPPUMode.h
        ppu/modes/OAMSearchPPUMode.cpp
        ppu/modes/OAMSearchPPUMode.h
        ppu/modes/PPUMode.cpp
        ppu/modes/PPUMode.h
        ppu/modes/PPUModeManager.cpp
        ppu/modes/PPUModeManager.h
        ppu/modes/PPUModeType.h
        ppu/modes/VBlankPPUMode.cpp
        ppu/modes/VBlankPPUMode.h
        ppu/oam/OAM.cpp
        ppu/oam/OAM.h
        ppu/oam/OAMDMA.cpp
        ppu/oam/OAMDMA.h
        ppu/oam/OAMEntry.h
        ppu/oam/SpriteBuffer.cpp
        ppu/oam/SpriteBuffer.h
        ppu/vram/VRAM.cpp
        ppu/vram/VRAM.h
        ppu/vram/VRAMTileData.cpp
        ppu/vram/VRAMTileData.h
        ppu/vram/VRAMTileMaps.cpp
        ppu/vram/VRAMTileMaps.h
        ppu/ColorUtils.cpp
        ppu/ColorUtils.h
        ppu/PPU.cpp
        ppu/PPU.h
        ppu/PPURegisters.h
        timer/Timer.cpp
        timer/Timer.h
        timer/TimerRegisters.h
        utils/Tickable.h
        miniaudio.cpp
        miniaudio.h
        main.cpp exceptions/ppu/UnknownPPUModeException.cpp exceptions/ppu/UnknownPPUModeException.h cartridge/BaseCartridge.h cartridge/CartridgeNoMBC.cpp cartridge/CartridgeNoMBC.h cartridge/datasource/CartridgeDataSource.h cartridge/datasource/InMemoryCartridgeDataSource.h cartridge/BaseCartridge.cpp cartridge/datasource/InMemoryCartridgeDataSource.cpp)

# Dependencies
find_package(Threads REQUIRED)
find_package(raylib 3.0 CONFIG REQUIRED)

# Target
add_executable(gbtest ${SOURCE_FILES})

# Dependencies linking
target_link_libraries(gbtest PRIVATE Threads::Threads)

if (TARGET raylib)
    # System-wide raylib install
    target_link_libraries(gbtest PRIVATE raylib)
elseif (RAYLIB_FOUND)
    # vcpkg raylib install
    target_include_directories(gbtest PRIVATE ${RAYLIB_INCLUDE_DIRS})
    target_link_libraries(gbtest PRIVATE ${RAYLIB_LIBRARIES})
else ()
    # Not found
    message(FATAL_ERROR "raylib not found")
endif ()

if (APPLE)
    target_link_libraries(gbtest PRIVATE "-framework IOKit")
    target_link_libraries(gbtest PRIVATE "-framework Cocoa")
    target_link_libraries(gbtest PRIVATE "-framework OpenGL")
endif ()

if (UNIX)
    target_link_libraries(gbtest PRIVATE ${CMAKE_DL_LIBS})
endif ()

# Install
install(TARGETS gbtest)