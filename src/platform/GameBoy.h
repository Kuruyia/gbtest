#ifndef GBTEST_GAMEBOY_H
#define GBTEST_GAMEBOY_H

#include <memory>

#include "bus/Bus.h"
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

class GameBoy
        : public Tickable {

public:
    GameBoy();
    ~GameBoy() override;

    void init();
    void update(float secondsToEmulate);
    void tick() override;

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

    void resetCpuRegisters();

    void registerBusProviders();
    void unregisterBusProviders();

}; // class GameBoy

} // namespace gbtest

#endif //GBTEST_GAMEBOY_H
