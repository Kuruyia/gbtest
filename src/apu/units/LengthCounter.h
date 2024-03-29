#ifndef GBTEST_LENGTHCOUNTER_H
#define GBTEST_LENGTHCOUNTER_H

#include <cstdint>

#include "../../utils/Tickable.h"

namespace gbtest {

class LengthCounter
        : public Tickable {

public:
    explicit LengthCounter(uint16_t countdownReloadValue);
    ~LengthCounter() override = default;

    void setCountdown(uint16_t countdown);
    [[nodiscard]] uint16_t getCountDown() const;

    void setEnabled(bool enabled);
    [[nodiscard]] bool isEnabled() const;

    [[nodiscard]] bool isChannelDisabled() const;
    void setChannelDisabled(bool channelDisabled);

    void doTrigger(bool canTick);

    void tick(bool isDoubleSpeedTick) override;

private:
    const uint16_t m_countdownReloadValue;

    uint16_t m_countdown;
    bool m_enabled;
    bool m_channelDisabled;

}; // class LengthCounter

} // namespace gbtest

#endif //GBTEST_LENGTHCOUNTER_H
