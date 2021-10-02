#ifndef GBTEST_APUCHANNEL2_H
#define GBTEST_APUCHANNEL2_H

#include "APUChannel.h"
#include "../APURegisters.h"

namespace gbtest {

class APUChannel2
        : public APUChannel {

public:
    APUChannel2() = default;
    ~APUChannel2() override = default;

    float sample() const override;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

private:
    SoundLengthWavePatternDuty m_soundLengthWavePatternDuty;
    VolumeEnvelope m_volumeEnvelope;
    FrequencyLow m_frequencyLow;
    FrequencyHigh m_frequencyHigh;

}; // class APUChannel2

} // namespace gbtest

#endif //GBTEST_APUCHANNEL2_H
