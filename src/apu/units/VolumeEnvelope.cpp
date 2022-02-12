#include "VolumeEnvelope.h"

gbtest::VolumeEnvelope::VolumeEnvelope()
        : m_increasing(true)
        , m_volume(0)
        , m_period(0)
{

}

void gbtest::VolumeEnvelope::setIncreasing(bool increasing)
{
    m_increasing = increasing;
}

bool gbtest::VolumeEnvelope::isIncreasing() const
{
    return m_increasing;
}

void gbtest::VolumeEnvelope::setVolume(uint8_t volume)
{
    m_volume = volume;
}

uint8_t gbtest::VolumeEnvelope::getVolume() const
{
    return m_volume;
}

void gbtest::VolumeEnvelope::setPeriod(uint8_t period)
{
    m_period = period;
}

uint8_t gbtest::VolumeEnvelope::getPeriod() const
{
    return m_period;
}

void gbtest::VolumeEnvelope::tick()
{
    // Update the volume if the period is not zero and the volume is > 0 and < 15
    if (m_period > 0) {
        --m_period;

        if (m_volume > 0 && m_volume < 15) {
            if (m_increasing) {
                ++m_volume;
            }
            else {
                --m_volume;
            }
        }
    }
}
