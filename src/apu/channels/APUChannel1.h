#ifndef GBTEST_APUCHANNEL1_H
#define GBTEST_APUCHANNEL1_H

#include "APUChannel.h"

#include "../units/AudioPulseWave.h"
#include "../units/LengthCounter.h"
#include "../units/Sweep.h"
#include "../units/VolumeEnvelope.h"
#include "../APURegisters.h"

namespace gbtest {

class APUChannel1
        : public APUChannel {

public:
    APUChannel1();
    ~APUChannel1() override = default;

    [[nodiscard]] Channel1Registers& getRegisters();
    [[nodiscard]] const Channel1Registers& getRegisters() const;

    [[nodiscard]] float sample() const override;

    [[nodiscard]] bool isChannelDisabled() const override;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    void tick() override;

private:
    Channel1Registers m_channel1Registers;

    AudioPulseWave m_audioPulseWave;
    LengthCounter m_lengthCounter;
    Sweep m_sweep;
    VolumeEnvelope m_volumeEnvelope;

    void updateFrequency();
    void updatePatternDuty();

    void doTrigger();

}; // class APUChannel1

} // namespace gbtest

#endif //GBTEST_APUCHANNEL1_H
