#include "VRAMTileData.h"

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
