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

    void tick() override;
    [[nodiscard]] uint8_t getUnitsToTick() const;

private:
    uint8_t m_tickCounter;

}; // class FrameSequencer

} // namespace gbtest

#endif //GBTEST_FRAMESEQUENCER_H
