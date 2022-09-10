#ifndef GBTEST_DIVIDER_H
#define GBTEST_DIVIDER_H

#include "DividerRegisters.h"

#include "../cpu/LR35902HaltState.h"
#include "../platform/bus/BusProvider.h"
#include "../utils/Tickable.h"

namespace gbtest {

class Divider
        : public BusProvider, public Tickable {

public:
    explicit Divider(const LR35902HaltState& haltState);
    ~Divider() override = default;

    [[nodiscard]] DividerReg& getRegister();
    [[nodiscard]] const DividerReg& getRegister() const;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    void tick(bool isDoubleSpeedTick) override;

private:
    const LR35902HaltState& m_haltState;

    DividerReg m_dividerRegister;
    unsigned m_tickCountdown;

}; // class Divider

} // namespace gbtest

#endif //GBTEST_DIVIDER_H
