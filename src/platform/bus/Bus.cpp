#include "Bus.h"

#include "../../exceptions/bus/BusLockedAddressException.h"
#include "../../exceptions/bus/BusNoHandlerException.h"

uint8_t gbtest::Bus::read(uint16_t addr) const
{
    // Ensure that no provider is locking this address
    ensureAddressIsUnlocked(addr);

    size_t i = 0;
    uint8_t val = 0;

    while (i < m_busProviders.size()) {
        if (m_busProviders[i]->read(addr, val)) { break; }
        ++i;
    }

    if (i == m_busProviders.size()) {
        throw BusNoHandlerException(addr, false);
    }

    return val;
}

void gbtest::Bus::write(uint16_t addr, uint8_t val)
{
    // Ensure that no provider is locking this address
    ensureAddressIsUnlocked(addr);

    for (BusProvider* const busProvider: m_busProviders) {
        if (busProvider->write(addr, val)) { return; }
    }

    throw BusNoHandlerException(addr, true);
}

void gbtest::Bus::registerBusProvider(BusProvider* busProvider)
{
    m_busProviders.push_back(busProvider);
}

void gbtest::Bus::unregisterBusProvider(BusProvider* busProvider)
{
    m_busProviders.erase(std::remove(m_busProviders.begin(), m_busProviders.end(), busProvider), m_busProviders.end());
}

void gbtest::Bus::ensureAddressIsUnlocked(uint16_t addr) const
{
    // Throw an exception if a bus provider is locking the address
    for (BusProvider* const busProvider: m_busProviders) {
        if (!busProvider->doesAuthorizeAccess(addr)) { throw BusLockedAddressException(addr); }
    }
}
