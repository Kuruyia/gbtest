#ifndef GBTEST_INTERRUPTCONTROLLER_H
#define GBTEST_INTERRUPTCONTROLLER_H

#include <bitset>

#include "InterruptType.h"
#include "../../platform/bus/BusProvider.h"
#include "../../utils/Tickable.h"

namespace gbtest {

class InterruptController
        : public Tickable, public BusProvider {

public:
    InterruptController();
    ~InterruptController() override = default;

    void setInterruptMasterEnable(bool interruptMasterEnable);
    [[nodiscard]] bool isInterruptMasterEnabled() const;

    void setDelayedInterruptEnableCountdown(int delayedInterruptEnableCountdown);
    void handleDelayedInterrupt();

    void setInterruptEnabled(InterruptType interruptType, bool enabled);
    [[nodiscard]] bool isInterruptEnabled(InterruptType interruptType);

    void setInterruptRequested(InterruptType interruptType, bool requested);
    [[nodiscard]] bool isInterruptRequested(InterruptType interruptType);

    void tick() override;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

private:
    bool m_interruptMasterEnable;
    int m_delayedInterruptEnableCountdown;

    std::bitset<5> m_interruptEnable;
    std::bitset<5> m_interruptFlag;

}; // class InterruptController

} // namespace InterruptController

#endif //GBTEST_INTERRUPTCONTROLLER_H
