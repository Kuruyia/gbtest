#include "CartridgeMBC1.h"

gbtest::CartridgeMBC1::CartridgeMBC1(gbtest::CartridgeDataSource& cartridgeDataSource)
        : BaseCartridge(cartridgeDataSource)
        , m_ram()
        , m_currentRomBank(1)
        , m_currentRamAndUpperRomBank(0)
        , m_advancedBankingMode(false)
        , m_ramEnable(false)
{

}

bool gbtest::CartridgeMBC1::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Cartridge (MBC1) is in memory area from 0000h to 7FFFh and A000h to BFFFh
    if ((addr > 0x7FFF) && (addr < 0xA000 || addr > 0xBFFF)) {
        return false;
    }

    // Check what part of the memory is being read
    if (addr <= 0x3FFF) {
        // The read is for ROM Bank X0
        if (m_advancedBankingMode && m_cartridgeHeaderData.romSize >= CartridgeHeaderROMSize::ROM1M) {
            m_cartridgeDataSource.read((0x4000 * (m_currentRamAndUpperRomBank << 5)) + addr, val);
        }
        else {
            m_cartridgeDataSource.read(addr, val);
        }
    }
    else if (addr >= 0x4000 && addr <= 0x7FFF) {
        // The read is for ROM Bank 01-7F
        m_cartridgeDataSource.read((0x4000 * (m_currentRomBank | (m_currentRamAndUpperRomBank << 5))) +
                                    (addr - 0x4000), val);
    }
    else if (m_ramEnable && (addr >= 0xA000 && addr <= 0xBFFF)) {
        // The read is for RAM Bank 00-03
        if (m_advancedBankingMode && m_cartridgeHeaderData.ramSize == CartridgeHeaderRAMSize::RAM32K) {
            // RAM Banking is enabled
            val = m_ram[(0x2000 * m_currentRamAndUpperRomBank) + (addr - 0xA000)];
        }
        else {
            // RAM Banking is disabled
            val = m_ram[addr - 0xA000];
        }
    }

    return true;
}

bool gbtest::CartridgeMBC1::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Cartridge (MBC1) is in memory area from 0000h to 7FFFh and A000h to BFFFh
    if ((addr > 0x7FFF) && (addr < 0xA000 || addr > 0xBFFF)) {
        return false;
    }

    // Check what part of the memory is being written to
    if (addr <= 0x1FFF) {
        // Writes to memory area 0000h to 1FFFh are for enabling or disabling RAM
        m_ramEnable = ((val & 0x0A) == 0x0A);
    }
    else if (addr >= 0x2000 && addr <= 0x3FFF) {
        // Writes to memory area 2000h to 3FFFh are for switching the ROM Bank Number

        // Fix the value
        val &= 0x1F;

        if (val == 0) {
            val = 1;
        }

        if (m_cartridgeHeaderData.romSize == CartridgeHeaderROMSize::ROM32K) {
            // Mask out four bits
            val &= 0x01;
        }
        else if (m_cartridgeHeaderData.romSize == CartridgeHeaderROMSize::ROM64K) {
            // Mask out three bits
            val &= 0x03;
        }
        else if (m_cartridgeHeaderData.romSize == CartridgeHeaderROMSize::ROM128K) {
            // Mask out two bits
            val &= 0x07;
        }
        else if (m_cartridgeHeaderData.romSize == CartridgeHeaderROMSize::ROM256K) {
            // Mask out one bit
            val &= 0x0F;
        }

        // Save the high bank number
        m_currentRomBank = val;
    }
    else if (addr >= 0x4000 && addr <= 0x5FFF) {
        // Writes to memory area 4000h to 5FFFh are for switching the RAM Bank Number or the high ROM Bank Number upper bits
        m_currentRamAndUpperRomBank = (val & 0x03);
    }
    else if (addr >= 0x6000 && addr <= 0x7FFF) {
        // Writes to memory area 6000h to 7FFFh are for selecting the Banking Mode
        if (val == 0x00) {
            m_advancedBankingMode = false;
        } else if (val == 0x01) {
            m_advancedBankingMode = true;
        }
    }
    else if (addr >= 0xA000 && addr <= 0xBFFF) {
        // Write is for RAM Bank 00-03
        m_ram[(0x2000 * m_currentRamAndUpperRomBank) + (addr - 0xA000)] = val;
    }

    return true;
}

bool gbtest::CartridgeMBC1::busReadOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Cartridge (MBC1) never overrides write requests
    return false;
}

bool gbtest::CartridgeMBC1::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Cartridge (MBC1) never overrides read requests
    return false;
}
