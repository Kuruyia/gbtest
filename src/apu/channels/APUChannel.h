#ifndef GBTEST_APUCHANNEL_H
#define GBTEST_APUCHANNEL_H

#include "../../platform/bus/BusProvider.h"
#include "../../utils/Tickable.h"

namespace gbtest {

class APUChannel
        : public BusProvider, public Tickable {

public:
    APUChannel();
    ~APUChannel() override = default;

    virtual float sample() const = 0;

    void tick() override;

private:
    unsigned m_tickCount;

}; // class APUChannel

} // namespace gbtest

#endif //GBTEST_APUCHANNEL_H