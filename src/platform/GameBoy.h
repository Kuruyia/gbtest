#ifndef GBTEST_GAMEBOY_H
#define GBTEST_GAMEBOY_H

#include "bus/Bus.h"

#include "../cpu/LR35902.h"
#include "../memory/Memory.h"
#include "../ppu/PPU.h"
#include "../utils/Tickable.h"

namespace gbtest {

class GameBoy
        : public Tickable {

public:
    GameBoy();
    ~GameBoy() override;

    void init();
    void update(int64_t delta);
    void tick() override;

    [[nodiscard]] Bus& getBus();
    [[nodiscard]] const Bus& getBus() const;

    [[nodiscard]] LR35902& getCpu();
    [[nodiscard]] const LR35902& getCpu() const;

    [[nodiscard]] PPU& getPpu();
    [[nodiscard]] const PPU& getPpu() const;

private:
    Bus m_bus;
    LR35902 m_cpu;
    Memory m_wholeMemory;
    PPU m_ppu;

    void resetCpuRegisters();

    void registerBusProviders();
    void unregisterBusProviders();

}; // class GameBoy

} // namespace gbtest

#endif //GBTEST_GAMEBOY_H
