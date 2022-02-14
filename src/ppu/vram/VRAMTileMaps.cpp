#include "VRAMTileMaps.h"

gbtest::VRAMTileMaps::VRAMTileMaps()
        : m_memory()
{

}

uint8_t gbtest::VRAMTileMaps::getTileNumberFromTileMap(size_t offset, uint8_t whichMap) const
{
    return m_memory.at((0x400 * whichMap) + offset);
}

bool gbtest::VRAMTileMaps::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // VRAM Tile Maps is in memory area from 9800h to 9FFFh
    if (addr < 0x9800 || addr > 0x9FFF) { return false; }

    // Read from the memory
    val = m_memory[addr - 0x9800];

    return true;
}

bool gbtest::VRAMTileMaps::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // VRAM Tile Maps is in memory area from 9800h to 9FFFh
    if (addr < 0x9800 || addr > 0x9FFF) { return false; }

    // Write to the memory
    m_memory[addr - 0x9800] = val;

    return true;
}

bool gbtest::VRAMTileMaps::busReadOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // VRAM Tile Maps never overrides read requests
    return false;
}

bool gbtest::VRAMTileMaps::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // VRAM Tile Maps never overrides write requests
    return false;
}
