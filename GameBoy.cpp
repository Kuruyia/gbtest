#include "GameBoy.h"

gbtest::GameBoy::GameBoy()
: m_bus()
, m_cpu(m_bus)
{

}

void gbtest::GameBoy::tick()
{
    m_cpu.tick();
}

gbtest::Bus &gbtest::GameBoy::getBus()
{
    return m_bus;
}

gbtest::LR35902 &gbtest::GameBoy::getCpu()
{
    return m_cpu;
}
