#include "Bus.h"

#include "../../exceptions/bus/BusLockedAddressException.h"

uint8_t gbtest::Bus::read(uint16_t addr) const
{
    // TODO: Throw an exception if no bus provider could satisfy the request
    ensureAddressIsUnlocked(addr);

    uint8_t val = 0;

    for (BusProvider* const busProvider: m_busProviders) {
        if (busProvider->read(addr, val)) { break; }
    }

    return val;
}

void gbtest::Bus::write(uint16_t addr, uint8_t val)
{
    // TODO: Throw an exception if no bus provider could satisfy the request
    ensureAddressIsUnlocked(addr);

    for (BusProvider* const busProvider: m_busProviders) {
        if (busProvider->write(addr, val)) { return; }
    }
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
    // Check that no bus provider is locking the address
    for (BusProvider* const busProvider: m_busProviders) {
        if (!busProvider->doesAuthorizeAccess(addr)) { throw BusLockedAddressException(addr); }
    }
}
