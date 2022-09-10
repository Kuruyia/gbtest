#ifndef GBTEST_APUCHANNEL_H
#define GBTEST_APUCHANNEL_H

#include <cstdint>

#include "../units/FrameSequencer.h"

#include "../../platform/bus/BusProvider.h"

namespace gbtest {

class APUChannel
        : public BusProvider {

public:
    APUChannel() = default;
    ~APUChannel() override = default;

    virtual void tickUnits(uint8_t unitsToTick, bool isDoubleSpeedTick) = 0;

    [[nodiscard]] virtual float sample() const = 0;

    [[nodiscard]] virtual bool isChannelDisabled() const = 0;

    virtual void reset() = 0;

}; // class APUChannel

} // namespace gbtest

#endif //GBTEST_APUCHANNEL_H
