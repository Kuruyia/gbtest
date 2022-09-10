#ifndef GBTEST_APUCHANNEL4_H
#define GBTEST_APUCHANNEL4_H

#include "APUChannel.h"

#include "../units/AudioNoise.h"
#include "../units/LengthCounter.h"
#include "../units/VolumeEnvelope.h"
#include "../APURegisters.h"

namespace gbtest {

class APUChannel4
        : public APUChannel {

public:
    APUChannel4();
    ~APUChannel4() override = default;

    [[nodiscard]] Channel4Registers& getRegisters();
    [[nodiscard]] const Channel4Registers& getRegisters() const;

    void tickUnits(uint8_t unitsToTick, bool isDoubleSpeedTick) override;

    [[nodiscard]] float sample() const override;

    [[nodiscard]] bool isChannelDisabled() const override;

    void reset() override;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

private:
    Channel4Registers m_channel4Registers;

    AudioNoise m_audioNoise;
    LengthCounter m_lengthCounter;
    VolumeEnvelope m_volumeEnvelope;

    void doTrigger();

}; // class APUChannel4

} // namespace gbtest

#endif //GBTEST_APUCHANNEL4_H
