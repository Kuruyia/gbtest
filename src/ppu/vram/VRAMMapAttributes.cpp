#include "VRAMMapAttributes.h"

gbtest::VRAMMapAttributes::VRAMMapAttributes()
    : m_memory()
{
    clear();
}

const gbtest::VRAMMapAttributesData&
gbtest::VRAMMapAttributes::getTileAttributesFromTileMap(size_t offset, uint8_t whichMap) const
{
    return m_memory.at((0x400 * whichMap) + offset);
}

void gbtest::VRAMMapAttributes::clear()
{
    // Fill the memory with 0x00 bytes
    VRAMMapAttributesData emptyData{};
    emptyData.raw = 0x00;

    m_memory.fill(emptyData);
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
