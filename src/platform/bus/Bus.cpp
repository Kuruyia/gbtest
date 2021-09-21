#include <algorithm>

#include "Bus.h"

#include "../../exceptions/bus/BusLockedAddressException.h"
#include "../../exceptions/bus/BusNoHandlerException.h"

gbtest::Bus::Bus()
        : m_interruptLines(0)
{

}

uint8_t gbtest::Bus::read(uint16_t addr, BusRequestSource requestSource) const
{
    // Variable declaration
    size_t i = 0;
    uint8_t val = 0;

    // Check first if a provider overrides the request
    for (BusProvider* const busProvider: m_busProviders) {
        if (busProvider->busReadOverride(addr, val, requestSource)) { return val; }
    }

    // Try to read from every provider
    while (i < m_busProviders.size()) {
        if (m_busProviders[i]->busRead(addr, val, requestSource)) { break; }
        ++i;
    }

    // Throw an exception if no provider was found
    if (i == m_busProviders.size()) {
        throw BusNoHandlerException(addr, false);
    }

    return val;
}

void gbtest::Bus::write(uint16_t addr, uint8_t val, BusRequestSource requestSource)
{
    // Check first if a provider overrides the request
    for (BusProvider* const busProvider: m_busProviders) {
        if (busProvider->busWriteOverride(addr, val, requestSource)) { return; }
    }

    // Try to write to every provider
    for (BusProvider* const busProvider: m_busProviders) {
        if (busProvider->busWrite(addr, val, requestSource)) { return; }
    }

    // Throw an exception if no provider was found
    throw BusNoHandlerException(addr, true);
}

void gbtest::Bus::registerBusProvider(BusProvider* busProvider)
{
    // Push the provider to the provider list
    m_busProviders.push_back(busProvider);
}

void gbtest::Bus::unregisterBusProvider(BusProvider* busProvider)
{
    // Remove the provider from the provider list
    m_busProviders.erase(std::remove(m_busProviders.begin(), m_busProviders.end(), busProvider), m_busProviders.end());
}

void gbtest::Bus::setInterruptLineHigh(gbtest::InterruptType interruptType, bool isHigh)
{
    if (isHigh) {
        m_interruptLines |= static_cast<uint8_t>(interruptType);
    }
    else {
        m_interruptLines &= ~(static_cast<uint8_t>(interruptType));
    }
}

bool gbtest::Bus::isInterruptLineHigh(gbtest::InterruptType interruptType) const
{
    return (m_interruptLines & static_cast<uint8_t>(interruptType)) != 0;
}

uint8_t gbtest::Bus::getInterruptLines() const
{
    return m_interruptLines;
}
