#include "VRAM.h"

gbtest::VRAM::VRAM()
        : m_readBlocked(false)
        , m_cgbMode(false)
        , m_currentBank(0)
{

}

gbtest::VRAMTileData& gbtest::VRAM::getCurrentVramTileData()
{
    return m_vramTileDataBanks[m_currentBank];
}

const gbtest::VRAMTileData& gbtest::VRAM::getCurrentVramTileData() const
{
    return m_vramTileDataBanks[m_currentBank];
}

gbtest::VRAM::VRAMTileDataBanks& gbtest::VRAM::getVramTileDataBanks()
{
    return m_vramTileDataBanks;
}

const gbtest::VRAM::VRAMTileDataBanks& gbtest::VRAM::getVramTileDataBanks() const
{
    return m_vramTileDataBanks;
}

gbtest::VRAMTileMaps& gbtest::VRAM::getVramTileMaps()
{
    return m_vramTileMaps;
}

const gbtest::VRAMTileMaps& gbtest::VRAM::getVramTileMaps() const
{
    return m_vramTileMaps;
}

gbtest::VRAMMapAttributes& gbtest::VRAM::getVramMapAttributes()
{
    return m_vramMapAttributes;
}

const gbtest::VRAMMapAttributes& gbtest::VRAM::getVramMapAttributes() const
{
    return m_vramMapAttributes;
}

void gbtest::VRAM::setReadBlocked(bool readBlocked)
{
    m_readBlocked = readBlocked;
}

void gbtest::VRAM::setCGBMode(bool cgbMode)
{
    m_cgbMode = cgbMode;

    // Reset the current bank if we're leaving CGB mode
    if (!cgbMode) {
        m_currentBank = 0;
    }

    // Clear the map attributes
    m_vramMapAttributes.clear();
}

bool gbtest::VRAM::isCGBMode() const
{
    return m_cgbMode;
}

void gbtest::VRAM::setCurrentBank(uint8_t bank)
{
    // Don't allow modifying the bank for non-CGB mode
    if (!m_cgbMode) {
        return;
    }

    m_currentBank = bank;
}

uint8_t gbtest::VRAM::getCurrentBank() const
{
    return m_currentBank;
}

bool gbtest::VRAM::isReadBlocked() const
{
    return m_readBlocked;
}

bool gbtest::VRAM::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Check for the VRAM Bank register
    if (m_cgbMode) {
        if (addr == 0xFF4F) {
            val = (m_currentBank | 0xFE);
            return true;
        }
    }

    // Dispatch the read request
    if (m_vramTileDataBanks[m_currentBank].busRead(addr, val, requestSource)) { return true; }

    if (m_currentBank == 1) {
        if (m_vramMapAttributes.busRead(addr, val, requestSource)) { return true; }
    }
    else {
        if (m_vramTileMaps.busRead(addr, val, requestSource)) { return true; }
    }

    return false;
}

bool gbtest::VRAM::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Check for the VRAM Bank register
    if (m_cgbMode) {
        if (addr == 0xFF4F) {
            m_currentBank = (val & 0x01);
            return true;
        }
    }

    // Dispatch the write request
    if (m_vramTileDataBanks[m_currentBank].busWrite(addr, val, requestSource)) { return true; }

    if (m_currentBank == 1) {
        if (m_vramMapAttributes.busWrite(addr, val, requestSource)) { return true; }
    }
    else {
        if (m_vramTileMaps.busWrite(addr, val, requestSource)) { return true; }
    }

    return false;
}

bool gbtest::VRAM::busReadOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Dispatch the read override request
    if (m_vramTileDataBanks[m_currentBank].busReadOverride(addr, val, requestSource)) { return true; }

    if (m_currentBank == 1) {
        if (m_vramMapAttributes.busReadOverride(addr, val, requestSource)) { return true; }
    }
    else {
        if (m_vramTileMaps.busReadOverride(addr, val, requestSource)) { return true; }
    }

    return false;
}

bool gbtest::VRAM::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Dispatch the write override request
    if (m_vramTileDataBanks[m_currentBank].busWriteOverride(addr, val, requestSource)) { return true; }

    if (m_currentBank == 1) {
        if (m_vramMapAttributes.busWriteOverride(addr, val, requestSource)) { return true; }
    }
    else {
        if (m_vramTileMaps.busWriteOverride(addr, val, requestSource)) { return true; }
    }

    return false;
}
