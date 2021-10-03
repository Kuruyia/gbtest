#ifndef GBTEST_AUDIOPULSEWAVE_H
#define GBTEST_AUDIOPULSEWAVE_H

#include "PulseWavePatternDuty.h"

namespace gbtest {

class AudioPulseWave {

public:
    static constexpr unsigned NB_HARMONICS = 12;

    AudioPulseWave();

    void setFrequency(unsigned frequency);
    [[nodiscard]] unsigned getFrequency() const;

    void setPulseWavePatternDuty(PulseWavePatternDuty pulseWavePatternDuty);
    [[nodiscard]] const PulseWavePatternDuty& getPulseWavePatternDuty() const;

    [[nodiscard]] float sample(float t) const;

private:
    unsigned m_frequency;
    PulseWavePatternDuty m_pulseWavePatternDuty;

}; // class AudioPulseWave

} // namespace gbtest

#endif //GBTEST_AUDIOPULSEWAVE_H
