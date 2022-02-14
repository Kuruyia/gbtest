#ifndef GBTEST_DIVIDER_H
#define GBTEST_DIVIDER_H

#include "DividerRegisters.h"

#include "../platform/bus/BusProvider.h"
#include "../utils/Tickable.h"

namespace gbtest {

class Divider
        : public BusProvider, public Tickable {

public:
    Divider();
    ~Divider() override = default;

    void reset();

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    void tick() override;

private:
    DividerReg m_dividerRegister;
    unsigned m_tickCountdown;

}; // class Divider

} // namespace gbtest

#endif //GBTEST_DIVIDER_H
