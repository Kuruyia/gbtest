#include "CartridgeMBC5.h"

gbtest::CartridgeMBC5::CartridgeMBC5(std::unique_ptr<CartridgeDataSource> cartridgeDataSource)
        : BaseCartridge(std::move(cartridgeDataSource))
        , m_ram()
        , m_currentRomBank(1)
        , m_currentRamBank(0)
        , m_ramEnable(false)
{

}

bool gbtest::CartridgeMBC5::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Cartridge (MBC5) is in memory area from 0000h to 7FFFh and A000h to BFFFh
    if ((addr > 0x7FFF && addr < 0xA000) || addr > 0xBFFF) {
        return false;
    }

    // Check what part of the memory is being read
    if (addr <= 0x3FFF) {
        // The read is for ROM Bank 00
        m_cartridgeDataSource->read(addr, val);
    }
    else if (addr >= 0x4000 && addr <= 0x7FFF) {
        // The read is for ROM Bank 00-1FF
        m_cartridgeDataSource->read((0x4000 * m_currentRomBank) + (addr - 0x4000), val);
    }
    else if (m_ramEnable && (addr >= 0xA000 && addr <= 0xBFFF)) {
        // The read is for RAM Bank 00-0F
        val = m_ram[(0x2000 * m_currentRamBank) + (addr - 0xA000)];
    }

    return true;
}

bool gbtest::CartridgeMBC5::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Cartridge (MBC5) is in memory area from 0000h to 7FFFh and A000h to BFFFh
    if ((addr > 0x7FFF && addr < 0xA000) || addr > 0xBFFF) {
        return false;
    }

    // Check what part of the memory is being written to
    if (addr <= 0x1FFF) {
        // Writes to memory area 0000h to 1FFFh are for enabling or disabling RAM
        m_ramEnable = ((val & 0x0A) == 0x0A);
    }
    else if (addr >= 0x2000 && addr <= 0x2FFF) {
        // Writes to memory area 2000h to 2FFFh are for switching the low ROM Bank Number
        m_currentRomBank &= 0x0100;
        m_currentRomBank |= val;
    }
    else if (addr >= 0x3000 && addr <= 0x3FFF) {
        // Writes to memory area 3000h to 3FFFh are for switching the high ROM Bank Number
        m_currentRomBank &= 0x00FF;
        m_currentRomBank |= (val << 8);
    }
    else if (addr >= 0x4000 && addr <= 0x5FFF) {
        // Writes to memory area 4000h to 5FFFh are for switching the RAM Bank Number or the high ROM Bank Number upper bits
        m_currentRamBank = (val & 0x0F);
    }
    else if (addr >= 0xA000 && addr <= 0xBFFF) {
        // Write is for RAM Bank 00-0F
        m_ram[(0x2000 * m_currentRamBank) + (addr - 0xA000)] = val;
    }

    return true;
}

bool gbtest::CartridgeMBC5::busReadOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Cartridge (MBC5) never overrides write requests
    return false;
}

bool gbtest::CartridgeMBC5::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Cartridge (MBC5) never overrides read requests
    return false;
}
