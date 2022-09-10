#ifndef GBTEST_APUCHANNEL3_H
#define GBTEST_APUCHANNEL3_H

#include "APUChannel.h"

#include "../units/AudioWave.h"
#include "../units/LengthCounter.h"
#include "../APURegisters.h"

namespace gbtest {

class APUChannel3
        : public APUChannel {

public:
    APUChannel3();
    ~APUChannel3() override = default;

    void commitNR30();
    void commitNR31();
    void commitNR32();
    void commitNR33();
    void commitNR34();
    void commitRegisters();

    [[nodiscard]] Channel3Registers& getRegisters();
    [[nodiscard]] const Channel3Registers& getRegisters() const;

    [[nodiscard]] AudioWave::WavePatternData& getWavePatternData();
    [[nodiscard]] const AudioWave::WavePatternData& getWavePatternData() const;

    void tickUnits(uint8_t unitsToTick, bool isDoubleSpeedTick) override;

    [[nodiscard]] float sample() const override;

    [[nodiscard]] bool isChannelDisabled() const override;

    void reset() override;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

private:
    Channel3Registers m_channel3Registers;

    AudioWave m_audioWave;
    LengthCounter m_lengthCounter;

    void updateFrequency();

    void doTrigger();

}; // class APUChannel3

} // namespace gbtest

#endif //GBTEST_APUCHANNEL3_H
