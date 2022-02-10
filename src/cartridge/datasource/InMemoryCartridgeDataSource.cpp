#include "InMemoryCartridgeDataSource.h"

gbtest::InMemoryCartridgeDataSource::InMemoryCartridgeStorage_t& gbtest::InMemoryCartridgeDataSource::getStorage()
{
    return m_rom;
}

const gbtest::InMemoryCartridgeDataSource::InMemoryCartridgeStorage_t&
gbtest::InMemoryCartridgeDataSource::getStorage() const
{
    return m_rom;
}

bool gbtest::InMemoryCartridgeDataSource::read(uint32_t addr, uint8_t& val)
{
    // Check the requested address
    if (addr >= m_rom.size()) {
        return false;
    }

    // Return the value from the ROM
    val = m_rom[addr];

    return true;
}
