#define _USE_MATH_DEFINES
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
    /*
     * Compute the Fourier series pulse wave:
     *  - k: Pulse width (duty cycle)
     *  - t: Time when to compute the sample
     */
    float fourierSum = 0.f;

    const float k = static_cast<float>(m_pulseWavePatternDuty) / 8.f;

    for (unsigned n = 1; n <= NB_HARMONICS; ++n) {
        fourierSum += (2.f / (static_cast<float>(n) * static_cast<float>(M_PI)))
                * ::sinf(static_cast<float>(n) * static_cast<float>(M_PI) * k)
                * ::cosf(2.f * static_cast<float>(n) * static_cast<float>(M_PI) * t * static_cast<float>(m_frequency));
    }

    return k + fourierSum;
}
