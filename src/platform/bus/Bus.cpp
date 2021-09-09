#include "Bus.h"

#include "../../exceptions/bus/BusLockedAddressException.h"
#include "../../exceptions/bus/BusNoHandlerException.h"

uint8_t gbtest::Bus::read(uint16_t addr, BusRequestSource requestSource) const
{
    // Variable declaration
    size_t i = 0;
    uint8_t val = 0;

    // Check first if a provider overrides the request
    for (BusProvider* const busProvider: m_busProviders) {
        if (busProvider->readOverride(addr, val, requestSource)) { return val; }
    }

    // Try to read from every provider
    while (i < m_busProviders.size()) {
        if (m_busProviders[i]->read(addr, val, requestSource)) { break; }
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
        if (busProvider->writeOverride(addr, val, requestSource)) { return; }
    }

    // Try to write to every provider
    for (BusProvider* const busProvider: m_busProviders) {
        if (busProvider->write(addr, val, requestSource)) { return; }
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