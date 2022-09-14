#ifndef GBTEST_FRAMESEQUENCER_H
#define GBTEST_FRAMESEQUENCER_H

#include <cstdint>

#include "../../platform/GameBoyFrequencies.h"
#include "../../utils/Tickable.h"
#include "APUUnit.h"

namespace gbtest {

class FrameSequencer
        : public Tickable {

public:
    FrameSequencer();
    ~FrameSequencer() override = default;

    void tick(bool isDoubleSpeedTick) override;
    [[nodiscard]] uint8_t getUnitsToTick() const;

private:
    static constexpr unsigned TICK_COUNT = GAMEBOY_FREQUENCY / 512;

    unsigned m_tickCounter;
    uint8_t m_step;

    uint8_t m_unitsToTick;

}; // class FrameSequencer

} // namespace gbtest

#endif //GBTEST_FRAMESEQUENCER_H
