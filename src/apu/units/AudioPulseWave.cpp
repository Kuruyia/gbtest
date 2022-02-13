#include "AudioPulseWave.h"

gbtest::AudioPulseWave::AudioPulseWave()
        : m_frequency(0)
        , m_pulseWavePatternDuty()
        , m_currentSample(0.f)
        , m_tickCountdown((2048 - m_frequency) * 4)
        , m_currentStep(0)
{

}

void gbtest::AudioPulseWave::setFrequency(uint16_t frequency)
{
    m_frequency = frequency;
}

uint16_t gbtest::AudioPulseWave::getFrequency() const
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

float gbtest::AudioPulseWave::getSample() const
{
    return m_currentSample;
}

void gbtest::AudioPulseWave::doTrigger()
{
    // Reset the timer
    m_tickCountdown = ((2048 - m_frequency) * 4);
}

void gbtest::AudioPulseWave::tick()
{
    // Decrease the tick countdown
    --m_tickCountdown;

    // Check if we have to update the sample
    if (m_tickCountdown == 0) {
        // Reset the tick countdown
        m_tickCountdown = ((2048 - m_frequency) * 4);

        // Increase the step
        ++m_currentStep;

        if (m_currentStep >= 8) {
            m_currentStep = 0;
        }

        // Update the sample
        m_currentSample = PULSE_WAVE_PATTERN_WAVEFORMS[(8 * static_cast<unsigned>(m_pulseWavePatternDuty))
                + m_currentStep];
    }
}
