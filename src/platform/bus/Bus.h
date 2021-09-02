#ifndef GBTEST_BUS_H
#define GBTEST_BUS_H

#include <cinttypes>
#include <vector>

#include "BusProvider.h"

namespace gbtest {

class Bus {

public:
    Bus() = default;

    uint8_t read(uint16_t addr) const;
    void write(uint16_t addr, uint8_t val);

    void registerBusProvider(BusProvider* busProvider);
    void unregisterBusProvider(BusProvider* busProvider);

private:
    std::vector<BusProvider*> m_busProviders;

}; // class Bus

} // namespace gbtest

#endif //GBTEST_BUS_H
