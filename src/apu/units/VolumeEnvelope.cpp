#include "VolumeEnvelope.h"

gbtest::VolumeEnvelope::VolumeEnvelope()
        : m_volume(0)
        , m_increasing(true)
        , m_period(0)
        , m_currentVolume(0)
        , m_currentIncreasing(true)
        , m_tickCountdown(0)
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

bool gbtest::VolumeEnvelope::isCurrentlyIncreasing() const
{
    return m_currentIncreasing;
}

void gbtest::VolumeEnvelope::setPeriod(uint8_t period)
{
    m_period = period;

    // Prevent problems on next tick
    if (m_tickCountdown == 0) {
        ++m_tickCountdown;
    }
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
    m_currentIncreasing = m_increasing;
    m_tickCountdown = m_period;
}

void gbtest::VolumeEnvelope::tick(bool isDoubleSpeedTick)
{
    // Decrease and check the countdown
    --m_tickCountdown;

    if (m_tickCountdown > 0) {
        return;
    }

    // Reset the countdown
    m_tickCountdown = m_period;

    // Update the current volume
    if (m_currentIncreasing && m_currentVolume < 15) {
        ++m_currentVolume;
    }
    else if (!m_currentIncreasing && m_currentVolume > 0) {
        --m_currentVolume;
    }
}
