#include "OAMDMA.h"

bool gbtest::OAMDMA::read(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // OAM DMA only uses address FF46h
    if (addr == 0xFF46) {
        // TODO: Compute the register value, return it
        return true;
    }

    return false;
}

bool gbtest::OAMDMA::write(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // OAM DMA only uses address FF46h
    if (addr == 0xFF46) {
        // TODO: Start a transfer
        return true;
    }

    return false;
}

bool gbtest::OAMDMA::readOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // TODO: Override when a DMA transfer is in progress
    return false;
}

bool gbtest::OAMDMA::writeOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // TODO: Override when a DMA transfer is in progress
    return false;
}
