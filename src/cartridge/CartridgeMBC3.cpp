#include "CartridgeMBC3.h"

gbtest::CartridgeMBC3::CartridgeMBC3(std::unique_ptr<CartridgeDataSource> cartridgeDataSource)
        : BaseCartridge(std::move(cartridgeDataSource))
        , m_ram()
        , m_currentRomBank(1)
        , m_currentRamBankAndRTCRegister(0)
        , m_ramAndRTCEnable(false)
        , m_rtcPeripheral()
        , m_startedLatchSequence(false)
{

}

bool gbtest::CartridgeMBC3::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Cartridge (MBC3) is in memory area from 0000h to 7FFFh and A000h to BFFFh
    if ((addr > 0x7FFF && addr < 0xA000) || addr > 0xBFFF) {
        return false;
    }

    // Check what part of the memory is being read
    if (addr <= 0x3FFF) {
        // The read is for ROM Bank 00
        m_cartridgeDataSource->read(addr, val);
    }
    else if (addr >= 0x4000 && addr <= 0x7FFF) {
        // The read is for ROM Bank 01-7F
        m_cartridgeDataSource->read((0x4000 * m_currentRomBank) + (addr - 0x4000), val);
    }
    else if (m_ramAndRTCEnable && (addr >= 0xA000 && addr <= 0xBFFF)) {
        // Check if the read is for RAM Bank 00-03 or RTC Register 08-0C
        if (m_currentRamBankAndRTCRegister <= 0x03) {
            // Read is for RAM Bank 00-03
            val = m_ram[(0x2000 * m_currentRamBankAndRTCRegister) + (addr - 0xA000)];
        }
        else if (m_currentRamBankAndRTCRegister == 0x08) {
            // Read is for RTC Register 08h (RTC Seconds)
            val = m_rtcPeripheral.getLatchedRegisters().getSeconds();
        }
        else if (m_currentRamBankAndRTCRegister == 0x09) {
            // Read is for RTC Register 09h (RTC Minutes)
            val = m_rtcPeripheral.getLatchedRegisters().getMinutes();
        }
        else if (m_currentRamBankAndRTCRegister == 0x0A) {
            // Read is for RTC Register 0Ah (RTC Hours)
            val = m_rtcPeripheral.getLatchedRegisters().getHours();
        }
        else if (m_currentRamBankAndRTCRegister == 0x0B) {
            // Read is for RTC Register 0Bh (RTC Day Counter Low)
            val = m_rtcPeripheral.getLatchedRegisters().getDayCounterLow();
        }
        else if (m_currentRamBankAndRTCRegister == 0x0C) {
            // Read is for RTC Register 0Ch (RTC Day Counter High)
            val = m_rtcPeripheral.getLatchedRegisters().getDayCounterHigh();
        }
    }

    return true;
}

bool gbtest::CartridgeMBC3::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Cartridge (MBC3) is in memory area from 0000h to 7FFFh and A000h to BFFFh
    if ((addr > 0x7FFF) && (addr < 0xA000 || addr > 0xBFFF)) {
        return false;
    }

    // Check what part of the memory is being written to
    if (addr <= 0x1FFF) {
        // Writes to memory area 0000h to 1FFFh are for enabling/disabling RAM and RTC accesses
        m_ramAndRTCEnable = ((val & 0x0A) == 0x0A);
    }
    else if (addr >= 0x2000 && addr <= 0x3FFF) {
        // Writes to memory area 2000h to 3FFFh are for switching the ROM Bank Number

        // Fix the value
        val &= 0x7F;

        if (val == 0) {
            val = 1;
        }

        // Save the bank number
        m_currentRomBank = val;
    }
    else if (addr >= 0x4000 && addr <= 0x5FFF) {
        // Writes to memory area 4000h to 5FFFh are for switching the RAM Bank Number/RTC Register
        m_currentRamBankAndRTCRegister = val;
    }
    else if (addr >= 0x6000 && addr <= 0x7FFF) {
        // Writes to memory area 6000h to 7FFFh are for latching the clock data
        if (val == 0x00) {
            m_startedLatchSequence = true;
        }
        else {
            if (m_startedLatchSequence && val == 0x01) {
                m_rtcPeripheral.latch();
            }

            m_startedLatchSequence = false;
        }
    }
    else if (addr >= 0xA000 && addr <= 0xBFFF) {
        // Check if the write request is for RAM Bank 00-03 or RTC Register 08-0C
        if (m_currentRamBankAndRTCRegister <= 0x03) {
            // Write is for RAM Bank 00-03
            m_ram[(0x2000 * m_currentRamBankAndRTCRegister) + (addr - 0xA000)] = val;
        }
        else if (m_currentRamBankAndRTCRegister == 0x08) {
            // Write is for RTC Register 08h (RTC Seconds)
            m_rtcPeripheral.getRegisters().setSeconds(val);
        }
        else if (m_currentRamBankAndRTCRegister == 0x09) {
            // Write is for RTC Register 09h (RTC Minutes)
            m_rtcPeripheral.getRegisters().setMinutes(val);
        }
        else if (m_currentRamBankAndRTCRegister == 0x0A) {
            // Write is for RTC Register 0Ah (RTC Hours)
            m_rtcPeripheral.getRegisters().setHours(val);
        }
        else if (m_currentRamBankAndRTCRegister == 0x0B) {
            // Write is for RTC Register 0Bh (RTC Day Counter Low)
            m_rtcPeripheral.getRegisters().setDayCounterLow(val);
        }
        else if (m_currentRamBankAndRTCRegister == 0x0C) {
            // Write is for RTC Register 0Ch (RTC Day Counter High)
            m_rtcPeripheral.getRegisters().setDayCounterHigh(val);
        }
    }

    return true;
}

bool gbtest::CartridgeMBC3::busReadOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Cartridge (MBC3) never overrides write requests
    return false;
}

bool gbtest::CartridgeMBC3::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Cartridge (MBC3) never overrides read requests
    return false;
}

void gbtest::CartridgeMBC3::tick()
{
    // Call the base class function
    BaseCartridge::tick();

    // Tick the RTC
    m_rtcPeripheral.tick();
}
