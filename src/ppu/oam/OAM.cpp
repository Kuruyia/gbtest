#include "OAM.h"

gbtest::OAM::OAM()
        : m_oamEntries()
{

}

void gbtest::OAM::writeRawValue(size_t offset, uint8_t val)
{
    // Grab the correct entry
    OAMEntry& oamEntry = m_oamEntries.at(offset / 4);

    // Return the correct byte of this entry
    const unsigned idx = (offset & 0x0003);

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
}

void gbtest::OAM::readRawValue(size_t offset, uint8_t& val) const
{
    // Grab the correct entry
    const OAMEntry& oamEntry = m_oamEntries.at(offset / 4);

    // Return the correct byte of this entry
    const unsigned idx = (offset & 0x0003);

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
}

void gbtest::OAM::setOamEntry(const gbtest::OAMEntry& entry, size_t idx)
{
    m_oamEntries.at(idx) = entry;
}

const gbtest::OAMEntry& gbtest::OAM::getOamEntry(size_t idx) const
{
    return m_oamEntries.at(idx);
}

gbtest::OAMEntry& gbtest::OAM::getOamEntry(size_t idx)
{
    return m_oamEntries.at(idx);
}

bool gbtest::OAM::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // OAM is in memory area from FE00h to FE9Fh
    if (addr < 0xFE00 || addr > 0xFE9F) { return false; }

    // Read the raw value
    readRawValue(addr - 0xFE00, val);

    return true;
}

bool gbtest::OAM::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // OAM is in memory area from FE00h to FE9Fh
    if (addr < 0xFE00 || addr > 0xFE9F) { return false; }

    // Write the raw value
    writeRawValue(addr - 0xFE00, val);

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