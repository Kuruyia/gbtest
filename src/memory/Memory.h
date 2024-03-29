#ifndef GBTEST_MEMORY_H
#define GBTEST_MEMORY_H

#include "../platform/bus/BusProvider.h"

namespace gbtest {

class Memory
        : public BusProvider {

public:
    Memory(uint16_t baseAddr, uint32_t size);
    ~Memory() override;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

private:
    uint16_t m_baseAddress;
    uint32_t m_memorySize;

    uint8_t* m_memory;

}; // class Memory

} // namespace gbtest

#endif //GBTEST_MEMORY_H
