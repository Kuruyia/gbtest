#ifndef GBTEST_APUCHANNEL_H
#define GBTEST_APUCHANNEL_H

#include "../units/FrameSequencer.h"

#include "../../platform/bus/BusProvider.h"
#include "../../utils/Tickable.h"

namespace gbtest {

class APUChannel
        : public BusProvider, public Tickable {

public:
    APUChannel() = default;
    ~APUChannel() override = default;

    [[nodiscard]] virtual float sample(float t) const = 0;

    void tick() override;

protected:
    FrameSequencer m_frameSequencer;

}; // class APUChannel

} // namespace gbtest

#endif //GBTEST_APUCHANNEL_H
