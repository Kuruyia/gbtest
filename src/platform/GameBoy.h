#ifndef GBTEST_GAMEBOY_H
#define GBTEST_GAMEBOY_H

#include <memory>

#include "bus/Bus.h"
#include "revision/GameBoyRevision.h"
#include "revision/GameBoyRevisionType.h"
#include "GameBoyFrequencies.h"

#include "../apu/APU.h"
#include "../cartridge/BaseCartridge.h"
#include "../cpu/LR35902.h"
#include "../joypad/Joypad.h"
#include "../memory/Memory.h"
#include "../ppu/PPU.h"
#include "../timer/Divider.h"
#include "../timer/Timer.h"
#include "../utils/Tickable.h"

namespace gbtest {

class GameBoy {

public:
    explicit GameBoy(GameBoyRevisionType&& revisionType);
    ~GameBoy();

    void init();
    void reset();
    void reset(GameBoyRevisionType&& revisionType);

    void update(float secondsToEmulate);
    void tick(bool force = false);

    void start();
    void stop();
    [[nodiscard]] bool isRunning() const;

    [[nodiscard]] const GameBoyRevision& getRevision() const;

    [[nodiscard]] Bus& getBus();
    [[nodiscard]] const Bus& getBus() const;

    [[nodiscard]] LR35902& getCpu();
    [[nodiscard]] const LR35902& getCpu() const;

    [[nodiscard]] PPU& getPpu();
    [[nodiscard]] const PPU& getPpu() const;

    [[nodiscard]] Joypad& getJoypad();
    [[nodiscard]] const Joypad& getJoypad() const;

    [[nodiscard]] APU& getApu();
    [[nodiscard]] const APU& getApu() const;

    [[nodiscard]] Timer& getTimer();
    [[nodiscard]] const Timer& getTimer() const;

    void loadCartridge(std::unique_ptr<BaseCartridge> cartridge);
    void loadCartridgeFromDataSource(std::unique_ptr<gbtest::CartridgeDataSource> dataSource);

    [[nodiscard]] BaseCartridge* getCartridge();
    [[nodiscard]] const BaseCartridge* getCartridge() const;

private:
    Bus m_bus;
    LR35902 m_cpu;
    Memory m_wholeMemory;
    PPU m_ppu;
    Joypad m_joypad;
    APU m_apu;
    Divider m_divider;
    Timer m_timer;
    std::unique_ptr<BaseCartridge> m_cartridge;

    GameBoyRevision m_revision;
    bool m_running;

    void resetRegisters();
    void updateCGBMode();

    void registerBusProviders();
    void unregisterBusProviders();

    void tickEmulator();

}; // class GameBoy

} // namespace gbtest

#endif //GBTEST_GAMEBOY_H
