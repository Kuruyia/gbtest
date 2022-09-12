#ifndef GBTEST_FREQUENCYSWEEP_H
#define GBTEST_FREQUENCYSWEEP_H

#include <cstdint>

#include "AudioPulseWave.h"
#include "../../utils/Tickable.h"

namespace gbtest {

class FrequencySweep
        : public Tickable {

public:
    explicit FrequencySweep(AudioPulseWave& audioPulseWave);
    ~FrequencySweep() override = default;

    [[nodiscard]] uint16_t getShadowFrequency() const;

    [[nodiscard]] bool isEnabled() const;
    [[nodiscard]] bool isChannelDisabled() const;

    void setPeriod(uint8_t period);
    [[nodiscard]] uint8_t getPeriod() const;
    [[nodiscard]] uint8_t getEffectivePeriod() const;

    void setDecreasing(bool decreasing);
    [[nodiscard]] bool isDecreasing() const;

    void setSweepShift(uint8_t sweepShift);
    [[nodiscard]] uint8_t getSweepShift() const;

    void doTrigger();

    void tick(bool isDoubleSpeedTick) override;

private:
    AudioPulseWave& m_audioPulseWave;

    uint16_t m_shadowFrequency;
    bool m_enabled;
    bool m_channelDisabled;

    uint8_t m_period;
    uint8_t m_effectivePeriod;
    bool m_decreasing;
    uint8_t m_sweepShift;

    uint8_t m_tickCountdown;
    bool m_calculationMadeInNegateMode;

    [[nodiscard]] uint16_t calculateNextFrequency(uint16_t frequency);
    void checkOverflow(uint16_t frequency);

}; // class FrequencySweep

} // namespace gbtest

#endif //GBTEST_FREQUENCYSWEEP_H
