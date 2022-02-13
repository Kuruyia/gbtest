#ifndef GBTEST_AUDIOPULSEWAVE_H
#define GBTEST_AUDIOPULSEWAVE_H

#include <cstdint>

#include "PulseWavePatternDuty.h"

#include "../../utils/Tickable.h"

namespace gbtest {

class AudioPulseWave
        : public Tickable {

public:
    AudioPulseWave();
    ~AudioPulseWave() override = default;

    void setFrequency(uint16_t frequency);
    [[nodiscard]] uint16_t getFrequency() const;

    void setPulseWavePatternDuty(PulseWavePatternDuty pulseWavePatternDuty);
    [[nodiscard]] const PulseWavePatternDuty& getPulseWavePatternDuty() const;

    [[nodiscard]] float getSample() const;

    void tick() override;

private:
    uint16_t m_frequency;
    PulseWavePatternDuty m_pulseWavePatternDuty;

    float m_currentSample;

    unsigned m_tickCountdown;
    uint8_t m_currentStep;

}; // class AudioPulseWave

} // namespace gbtest

#endif //GBTEST_AUDIOPULSEWAVE_H
