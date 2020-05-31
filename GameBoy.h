#ifndef GBTEST_GAMEBOY_H
#define GBTEST_GAMEBOY_H

#include "Bus.h"
#include "LR35902.h"

namespace gbtest
{

class GameBoy
{

public:
    GameBoy();

    void tick();

    Bus &getBus();
    LR35902 &getCpu();

private:
    Bus m_bus;
    LR35902 m_cpu;

}; // class GameBoy

} // namespace gbtest

#endif //GBTEST_GAMEBOY_H
