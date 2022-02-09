#include <cstddef>

#include "VRAMTileData.h"

uint16_t gbtest::VRAMTileData::getTileLineUsingFirstMethod(uint8_t tileNumber, uint8_t lineNumber) const
{
    const size_t offset = ((16 * tileNumber) + (2 * lineNumber));

    return (m_memory.at(offset) << 8) | m_memory.at(offset + 1);
}

uint16_t gbtest::VRAMTileData::getTileLineUsingSecondMethod(int8_t tileNumber, uint8_t lineNumber) const
{
    const size_t offset = (0x1000 + (16 * tileNumber) + (2 * lineNumber));

    return (m_memory.at(offset) << 8) | m_memory.at(offset + 1);
}

bool gbtest::VRAMTileData::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // VRAM Tile Data is in memory area from 8000h to 97FFh
    if (addr < 0x8000 || addr > 0x97FF) { return false; }

    // Read from the memory
    val = m_memory[addr - 0x8000];

    return true;
}

bool gbtest::VRAMTileData::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // VRAM Tile Data is in memory area from 8000h to 97FFh
    if (addr < 0x8000 || addr > 0x97FF) { return false; }

    // Write to the memory
    m_memory[addr - 0x8000] = val;

    return true;
}

bool gbtest::VRAMTileData::busReadOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // VRAM Tile Data never overrides read requests
    return false;
}

bool gbtest::VRAMTileData::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // VRAM Tile Data never overrides write requests
    return false;
}
