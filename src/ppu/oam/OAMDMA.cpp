#include "OAMDMA.h"

gbtest::OAMDMA::OAMDMA(gbtest::Bus& bus)
        : m_transferring(false)
        , m_currentAddressLow(0x00)
        , m_sourceAddressHigh(0x00)
        , m_bus(bus)
{

}

void gbtest::OAMDMA::startTransfer(uint8_t startAddressHigh)
{
    // We can't start another transfer if one is already in progress
    if (m_transferring) { return; }

    // Only allow start source address MSB from 00h to DFh
    if (startAddressHigh > 0xDF) {
        m_sourceAddressHigh = startAddressHigh;
        return;
    }

    // Start the transfer
    m_transferring = true;
    m_currentAddressLow = 0x00;
    m_sourceAddressHigh = startAddressHigh;
}

bool gbtest::OAMDMA::isTransferring() const
{
    return m_transferring;
}

void gbtest::OAMDMA::tick()
{
    // Only proceed if a transfer is ongoing
    if (!m_transferring) { return; }

    // Transfer a byte at each tick
    const uint16_t sourceAddress = (m_sourceAddressHigh << 8) | m_currentAddressLow;
    const uint16_t destinationAddress = 0xFE00 | m_currentAddressLow;

    m_bus.write(destinationAddress, m_bus.read(sourceAddress, BusRequestSource::OAMDMA), BusRequestSource::OAMDMA);

    // Increment the current address low byte, check if the transfer has finished
    ++m_currentAddressLow;

    if (m_currentAddressLow > 0x9F) {
        m_transferring = false;
    }
}

bool gbtest::OAMDMA::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // OAM DMA only uses address FF46h
    if (addr == 0xFF46) {
        // Return the current source address MSB
        val = m_sourceAddressHigh;

        return true;
    }

    return false;
}

bool gbtest::OAMDMA::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // OAM DMA only uses address FF46h
    if (addr == 0xFF46) {
        // Start a transfer with the given value as the source address MSB
        startTransfer(val);

        return true;
    }

    return false;
}

bool gbtest::OAMDMA::busReadOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Override when a DMA transfer is in progress and the requested address is not in the HRAM region
    if (m_transferring && (addr < 0xFF80 || addr > 0xFFFE)) {
        // "Read" the value as FFh
        val = 0xFF;

        return true;
    }

    return false;
}

bool gbtest::OAMDMA::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Override when a DMA transfer is in progress and the requested address is not in the HRAM region
    if (m_transferring && (addr < 0xFF80 || addr > 0xFFFE)) {
        // Don't do anything
        return true;
    }

    return false;
}
