#ifndef GBTEST_GAMEBOY_H
#define GBTEST_GAMEBOY_H

#include "bus/Bus.h"
#include "../cpu/LR35902.h"
#include "../memory/Memory.h"
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

    Bus& getBus();
    LR35902& getCpu();

private:
    Bus m_bus;
    LR35902 m_cpu;
    Memory m_wholeMemory;

    void resetCpuRegisters();

    void registerBusProviders();
    void unregisterBusProviders();

}; // class GameBoy

} // namespace gbtest

#endif //GBTEST_GAMEBOY_H
