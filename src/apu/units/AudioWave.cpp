#include "AudioWave.h"

gbtest::AudioWave::AudioWave()
        : m_wavePatternData()
        , m_currentSampleIdx(0)
        , m_currentSample(0.f)
        , m_enabled(false)
        , m_frequency(0)
        , m_volume(0)
        , m_tickCountdown((2048 - m_frequency) * 2)
{

}

void gbtest::AudioWave::setEnabled(bool enabled)
{
    m_enabled = enabled;
}

bool gbtest::AudioWave::isEnabled() const
{
    return m_enabled;
}

bool gbtest::AudioWave::isChannelDisabled() const
{
    return !m_enabled;
}

void gbtest::AudioWave::setFrequency(uint16_t frequency)
{
    m_frequency = frequency;
}

uint16_t gbtest::AudioWave::getFrequency() const
{
    return m_frequency;
}

void gbtest::AudioWave::setVolume(uint8_t volume)
{
    m_volume = volume;
}

uint8_t gbtest::AudioWave::getVolume() const
{
    return m_volume;
}

void gbtest::AudioWave::writeWavePatternData(size_t idx, uint8_t val)
{
    m_wavePatternData[idx] = val;
}

uint8_t gbtest::AudioWave::readWavePatternData(size_t idx) const
{
    return m_wavePatternData[idx];
}

float gbtest::AudioWave::getSample() const
{
    return m_currentSample;
}

void gbtest::AudioWave::doTrigger()
{
    // Reset the sample index
    m_currentSampleIdx = 0;

    // Reset the timer
    m_tickCountdown = ((2048 - m_frequency) * 2);
}

void gbtest::AudioWave::tick()
{
    // Don't do anything if the channel is disabled
    if (!m_enabled) {
        return;
    }

    // Decrease the tick countdown
    --m_tickCountdown;

    // Check if we have to update the sample
    if (m_tickCountdown == 0) {
        // Reset the tick countdown
        m_tickCountdown = ((2048 - m_frequency) * 2);

        // Increase the current sample index
        ++m_currentSampleIdx;

        if (m_currentSampleIdx >= 32) {
            m_currentSampleIdx = 0;
        }

        // Don't do anything if the volume is zero
        if (m_volume == 0) {
            m_currentSample = 0.f;
            return;
        }

        // Get the nibble
        uint8_t sample;

        if (m_currentSampleIdx & 0x01) {
            // Sample is in the second nibble
            sample = (m_wavePatternData[m_currentSampleIdx / 2] & 0x0F);
        }
        else {
            // Sample is in the first nibble
            sample = (m_wavePatternData[m_currentSampleIdx / 2] >> 4);
        }

        // Apply the volume
        sample >>= (m_volume - 1);

        // Update the sample
        m_currentSample = (static_cast<float>(sample) / 15.f);
    }
}
