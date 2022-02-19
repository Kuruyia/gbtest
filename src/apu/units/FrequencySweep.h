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

    [[nodiscard]] unsigned getShadowFrequency() const;

    [[nodiscard]] bool isEnabled() const;

    void setPeriod(uint8_t period);
    [[nodiscard]] uint8_t getPeriod() const;

    void setDecreasing(bool decreasing);
    [[nodiscard]] bool isDecreasing() const;

    void setSweepShift(uint8_t sweepShift);
    [[nodiscard]] uint8_t getSweepShift() const;

    void doTrigger();

    void tick() override;

private:
    AudioPulseWave& m_audioPulseWave;

    unsigned m_shadowFrequency;
    bool m_enabled;

    uint8_t m_period;
    bool m_decreasing;
    uint8_t m_sweepShift;

    uint8_t m_tickCountdown;

    [[nodiscard]] bool calculateNewFrequency();

}; // class FrequencySweep

} // namespace gbtest

#endif //GBTEST_FREQUENCYSWEEP_H
