#include "VRAMMapAttributes.h"

#include <iostream>

gbtest::VRAMMapAttributes::VRAMMapAttributes()
    : m_memory()
{

}

const gbtest::VRAMMapAttributesData&
gbtest::VRAMMapAttributes::getTileAttributesFromTileMap(size_t offset, uint8_t whichMap) const
{
    return m_memory.at((0x400 * whichMap) + offset);
}

bool gbtest::VRAMMapAttributes::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // VRAM Map Attributes is in memory area from 9800h to 9FFFh
    if (addr < 0x9800 || addr > 0x9FFF) { return false; }

    // Read from the memory
    val = m_memory[addr - 0x9800].raw;

    return true;
}

bool gbtest::VRAMMapAttributes::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // VRAM Map Attributes is in memory area from 9800h to 9FFFh
    if (addr < 0x9800 || addr > 0x9FFF) { return false; }

    // Write to the memory
    m_memory[addr - 0x9800].raw = val;

    std::cout << "Writing map attributes to 0x" << std::hex << addr << std::dec << std::endl;

    return true;
}

bool
gbtest::VRAMMapAttributes::busReadOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // VRAM Map Attributes never overrides read requests
    return false;
}

bool gbtest::VRAMMapAttributes::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // VRAM Map Attributes never overrides write requests
    return false;
}
