#ifndef GBTEST_CGBSPEEDSWITCHREGISTER_H
#define GBTEST_CGBSPEEDSWITCHREGISTER_H

#include "bus/BusProvider.h"

namespace gbtest {

class CGBSpeedSwitchRegister
        : public BusProvider {

public:
    CGBSpeedSwitchRegister();
    ~CGBSpeedSwitchRegister() override = default;

    void setCGBMode(bool cgbMode);
    [[nodiscard]] bool isCGBMode() const;

    void setDoubleSpeed(bool doubleSpeed);
    [[nodiscard]] bool isDoubleSpeed() const;

    void setPrepareSpeedSwitch(bool prepareSpeedSwitch);
    [[nodiscard]] bool isPreparingSpeedSwitch() const;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

private:
    bool m_cgbMode;

    bool m_doubleSpeed;
    bool m_prepareSpeedSwitch;

}; // class CGBSpeedSwitchRegister

} // namespace gbtest

#endif //GBTEST_CGBSPEEDSWITCHREGISTER_H
