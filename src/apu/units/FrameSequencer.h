#ifndef GBTEST_FRAMESEQUENCER_H
#define GBTEST_FRAMESEQUENCER_H

#include <cstdint>

#include "APUUnit.h"
#include "../../utils/Tickable.h"

namespace gbtest {

class FrameSequencer
        : public Tickable {

public:
    FrameSequencer();
    ~FrameSequencer() override = default;

    void tick(bool isDoubleSpeedTick) override;
    [[nodiscard]] uint8_t getUnitsToTick() const;

private:
    unsigned m_tickCountdown;
    uint8_t m_step;

    uint8_t m_unitsToTick;

}; // class FrameSequencer

} // namespace gbtest

#endif //GBTEST_FRAMESEQUENCER_H
