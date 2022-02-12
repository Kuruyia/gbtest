#ifndef GBTEST_LENGTHCOUNTER_H
#define GBTEST_LENGTHCOUNTER_H

#include <cstdint>

#include "../../utils/Tickable.h"

namespace gbtest {

class LengthCounter
        : public Tickable {

public:
    LengthCounter();
    ~LengthCounter() override = default;

    void setCountdown(uint8_t countdown);
    [[nodiscard]] uint8_t getCountDown() const;

    void setEnabled(bool enabled);
    [[nodiscard]] bool isEnabled() const;

    [[nodiscard]] bool isChannelDisabled() const;

    void doTrigger();

    void tick() override;

private:
    uint8_t m_countdown;
    bool m_enabled;

}; // class LengthCounter

} // namespace gbtest

#endif //GBTEST_LENGTHCOUNTER_H
