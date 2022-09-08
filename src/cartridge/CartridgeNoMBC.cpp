#include "CartridgeNoMBC.h"

gbtest::CartridgeNoMBC::CartridgeNoMBC(std::unique_ptr<CartridgeDataSource> cartridgeDataSource)
        : BaseCartridge(std::move(cartridgeDataSource))
{

}

bool gbtest::CartridgeNoMBC::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Cartridge (No MBC) is in memory area from 0000h to 7FFFh and A000h to BFFFh
    if ((addr > 0x7FFF) && (addr < 0xA000 || addr > 0xBFFF)) {
        return false;
    }

    // Return the value from the data source
    m_cartridgeDataSource->read(addr, val);

    return true;
}

bool gbtest::CartridgeNoMBC::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Cartridge (No MBC) is in memory area from 0000h to 7FFFh and A000h to BFFFh
    if ((addr > 0x7FFF) && (addr < 0xA000 || addr > 0xBFFF)) {
        return false;
    }

    // We don't do writing here
    return true;
}

bool
gbtest::CartridgeNoMBC::busReadOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Cartridge (No MBC) never overrides read requests
    return false;
}

bool gbtest::CartridgeNoMBC::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Cartridge (No MBC) never overrides read requests
    return false;
}
