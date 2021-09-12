#include "VRAM.h"

bool gbtest::VRAM::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Dispatch the read request
    if (m_vramTileData.busRead(addr, val, requestSource)) { return true; }
    if (m_vramTileMaps.busRead(addr, val, requestSource)) { return true; }

    return false;
}

bool gbtest::VRAM::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Dispatch the write request
    if (m_vramTileData.busWrite(addr, val, requestSource)) { return true; }
    if (m_vramTileMaps.busWrite(addr, val, requestSource)) { return true; }

    return false;
}

bool gbtest::VRAM::busReadOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Dispatch the read override request
    if (m_vramTileData.busReadOverride(addr, val, requestSource)) { return true; }
    if (m_vramTileMaps.busReadOverride(addr, val, requestSource)) { return true; }

    return false;
}

bool gbtest::VRAM::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Dispatch the write override request
    if (m_vramTileData.busWriteOverride(addr, val, requestSource)) { return true; }
    if (m_vramTileMaps.busWriteOverride(addr, val, requestSource)) { return true; }

    return false;
}
