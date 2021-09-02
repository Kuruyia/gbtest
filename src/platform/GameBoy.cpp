#include "GameBoy.h"

#define CLOCK_FREQ_MHZ 4.194304

gbtest::GameBoy::GameBoy()
        : m_cpu(m_bus)
        , m_wholeMemory(0x0000, 0x10000)
{
    // TODO: Have the real memory layout
    m_bus.registerBusProvider(&m_wholeMemory);
}

void gbtest::GameBoy::update(int64_t delta)
{
    const int ticksToEmulate = delta * CLOCK_FREQ_MHZ;
//    std::cout << "Emulating " << ticksToEmulate << " ticks" << std::endl;

    for (unsigned i = 0; i < ticksToEmulate; ++i) {
        tick();
    }
}

void gbtest::GameBoy::tick()
{
    m_cpu.tick();
}

gbtest::Bus& gbtest::GameBoy::getBus()
{
    return m_bus;
}

gbtest::LR35902& gbtest::GameBoy::getCpu()
{
    return m_cpu;
}
