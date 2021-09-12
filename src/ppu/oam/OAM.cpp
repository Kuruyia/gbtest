#include "OAM.h"

bool gbtest::OAM::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // OAM is in memory area from FE00h to FE9Fh
    if (addr < 0xFE00 || addr > 0xFE9F) { return false; }

    // Grab the correct entry
    const OAMEntry& oamEntry = m_oamEntries[(addr - 0xFE00) / 4];

    // Return the correct byte of this entry
    const unsigned idx = addr & 0x0003;

    switch (idx) {
    case 0:
        val = oamEntry.yPosition;
        break;

    case 1:
        val = oamEntry.xPosition;
        break;

    case 2:
        val = oamEntry.tileIndex;
        break;

    case 3:
        val = oamEntry.flags.raw;
        break;

    default:
        break;
    }

    return true;
}

bool gbtest::OAM::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // OAM is in memory area from FE00h to FE9Fh
    if (addr < 0xFE00 || addr > 0xFE9F) { return false; }

    // Grab the correct entry
    OAMEntry& oamEntry = m_oamEntries[(addr - 0xFE00) / 4];

    // Return the correct byte of this entry
    const unsigned idx = addr & 0x0003;

    switch (idx) {
    case 0:
        oamEntry.yPosition = val;
        break;

    case 1:
        oamEntry.xPosition = val;
        break;

    case 2:
        oamEntry.tileIndex = val;
        break;

    case 3:
        oamEntry.flags.raw = val;
        break;

    default:
        break;
    }

    return true;
}

bool gbtest::OAM::busReadOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // OAM never overrides read requests
    return false;
}

bool gbtest::OAM::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // OAM never overrides write requests
    return false;
}