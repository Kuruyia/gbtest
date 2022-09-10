#include "VolumeEnvelope.h"

gbtest::VolumeEnvelope::VolumeEnvelope()
        : m_volume(0)
        , m_increasing(true)
        , m_period(0)
        , m_currentVolume(0)
        , m_countdown(0)
{

}

void gbtest::VolumeEnvelope::setVolume(uint8_t volume)
{
    m_volume = volume;
}

uint8_t gbtest::VolumeEnvelope::getVolume() const
{
    return m_volume;
}

void gbtest::VolumeEnvelope::setIncreasing(bool increasing)
{
    m_increasing = increasing;
}

bool gbtest::VolumeEnvelope::isIncreasing() const
{
    return m_increasing;
}

void gbtest::VolumeEnvelope::setPeriod(uint8_t period)
{
    m_period = period;
}

uint8_t gbtest::VolumeEnvelope::getPeriod() const
{
    return m_period;
}

uint8_t gbtest::VolumeEnvelope::getCurrentVolume() const
{
    return m_currentVolume;
}

void gbtest::VolumeEnvelope::doTrigger()
{
    // Reload the current volume and the countdown
    m_currentVolume = m_volume;
    m_countdown = m_period;
}

void gbtest::VolumeEnvelope::tick(bool isDoubleSpeedTick)
{
    // Decrease the countdown
    --m_countdown;

    if (m_countdown == 0) {
        // Reset the countdown
        m_countdown = m_period;

        // Update the current volume
        if (m_currentVolume > 0 && m_currentVolume < 15) {
            if (m_increasing) {
                ++m_currentVolume;
            }
            else {
                --m_currentVolume;
            }
        }
    }
}
