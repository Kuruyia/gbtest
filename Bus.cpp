#include "Bus.h"

const uint8_t &gbtest::Bus::read(const uint16_t &addr) const
{
    return m_memory[addr];
}

void gbtest::Bus::write(const uint16_t &addr, const uint8_t &data)
{
    m_memory[addr] = data;
}
