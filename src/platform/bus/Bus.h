#ifndef GBTEST_BUS_H
#define GBTEST_BUS_H

#include <bitset>
#include <cstdint>
#include <vector>

#include "BusProvider.h"
#include "BusRequestSource.h"

#include "../../cpu/interrupts/InterruptType.h"

namespace gbtest {

class Bus {

public:
    Bus() = default;

    [[nodiscard]] uint8_t read(uint16_t addr, BusRequestSource requestSource) const;
    void write(uint16_t addr, uint8_t val, BusRequestSource requestSource);

    void registerBusProvider(BusProvider* busProvider);
    void unregisterBusProvider(BusProvider* busProvider);

    void setInterruptLineHigh(InterruptType interruptType, bool isHigh);
    [[nodiscard]] bool isInterruptLineHigh(InterruptType interruptType) const;
    [[nodiscard]] const std::bitset<5>& getInterruptLines() const;

private:
    std::vector<BusProvider*> m_busProviders;
    std::bitset<5> m_interruptLines;

}; // class Bus

} // namespace gbtest

#endif //GBTEST_BUS_H
