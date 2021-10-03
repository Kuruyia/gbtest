#ifndef GBTEST_APUCHANNEL2_H
#define GBTEST_APUCHANNEL2_H

#include "APUChannel.h"

#include "../units/AudioPulseWave.h"
#include "../APURegisters.h"

#include "../../platform/GameBoyFrequencies.h"

namespace gbtest {

class APUChannel2
        : public APUChannel {

public:
    APUChannel2();
    ~APUChannel2() override = default;

    [[nodiscard]] Channel2Registers& getRegisters();
    [[nodiscard]] const Channel2Registers& getRegisters() const;

    [[nodiscard]] float sample() const override;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

private:
    Channel2Registers m_channel2Registers;

    AudioPulseWave m_audioPulseWave;

    void updateFrequency();
    void updatePatternDuty();

}; // class APUChannel2

} // namespace gbtest

#endif //GBTEST_APUCHANNEL2_H
