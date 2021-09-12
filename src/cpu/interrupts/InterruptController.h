#ifndef GBTEST_INTERRUPTCONTROLLER_H
#define GBTEST_INTERRUPTCONTROLLER_H

#include <bitset>

#include "InterruptType.h"
#include "../../platform/bus/BusProvider.h"
#include "../../platform/bus/Bus.h"
#include "../../utils/Tickable.h"

namespace gbtest {

class InterruptController
        : public Tickable, public BusProvider {

public:
    explicit InterruptController(Bus& bus);
    ~InterruptController() override = default;

    void setInterruptMasterEnable(bool interruptMasterEnable);
    [[nodiscard]] bool isInterruptMasterEnabled() const;

    void setDelayedInterruptEnableCountdown(int delayedInterruptEnableCountdown);
    void handleDelayedInterrupt();

    void setInterruptEnabled(InterruptType interruptType, bool enabled);
    [[nodiscard]] bool isInterruptEnabled(InterruptType interruptType) const;
    [[nodiscard]] const std::bitset<5>& getInterruptEnable() const;

    void setInterruptRequested(InterruptType interruptType, bool requested);
    [[nodiscard]] bool isInterruptRequested(InterruptType interruptType) const;
    [[nodiscard]] const std::bitset<5>& getInterruptRequest() const;

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

    Bus& m_bus;
    std::bitset<5> m_previousInterruptLines;

}; // class InterruptController

} // namespace InterruptController

#endif //GBTEST_INTERRUPTCONTROLLER_H
