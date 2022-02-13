#ifndef GBTEST_APUCHANNEL3_H
#define GBTEST_APUCHANNEL3_H

#include "APUChannel.h"

#include "../units/LengthCounter.h"
#include "../units/VolumeEnvelope.h"
#include "../APURegisters.h"

namespace gbtest {

class APUChannel3
        : public APUChannel {

public:
    APUChannel3();
    ~APUChannel3() override = default;

    [[nodiscard]] Channel3Registers& getRegisters();
    [[nodiscard]] const Channel3Registers& getRegisters() const;

    void tickUnits(uint8_t unitsToTick) override;

    [[nodiscard]] float sample() const override;

    [[nodiscard]] bool isChannelDisabled() const override;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

private:
    Channel3Registers m_channel3Registers;

    LengthCounter m_lengthCounter;
    VolumeEnvelope m_volumeEnvelope;

    void updateFrequency();

    void doTrigger();

}; // class APUChannel3

} // namespace gbtest

#endif //GBTEST_APUCHANNEL3_H
