#include <cmath>

#include "AudioPulseWave.h"

gbtest::AudioPulseWave::AudioPulseWave()
        : m_frequency(0)
        , m_pulseWavePatternDuty()
{

}

void gbtest::AudioPulseWave::setFrequency(unsigned int frequency)
{
    m_frequency = frequency;
}

unsigned gbtest::AudioPulseWave::getFrequency() const
{
    return m_frequency;
}

void gbtest::AudioPulseWave::setPulseWavePatternDuty(gbtest::PulseWavePatternDuty pulseWavePatternDuty)
{
    m_pulseWavePatternDuty = pulseWavePatternDuty;
}

const gbtest::PulseWavePatternDuty& gbtest::AudioPulseWave::getPulseWavePatternDuty() const
{
    return m_pulseWavePatternDuty;
}

float gbtest::AudioPulseWave::sample(float t) const
{
    // Multiply the time by the frequency
    t *= (float) m_frequency;

    // Only keep the fractional part of the time
    float integral;
    t = modff(t, &integral);
    t = abs(t);

    // Deliver the sample, depending on the duty cycle
    switch (m_pulseWavePatternDuty) {
    case PulseWavePatternDuty::Duty_12_5:
        if (t >= 0.125f) {
            return 0.f;
        }

        break;

    case PulseWavePatternDuty::Duty_25:
        if (t >= 0.25f) {
            return 0.f;
        }

        break;

    case PulseWavePatternDuty::Duty_50:
        if (t >= 0.50f) {
            return 0.f;
        }

        break;

    case PulseWavePatternDuty::Duty_75:
        if (t >= 0.75f) {
            return 0.f;
        }

        break;
    }

    return 1.f;
}
