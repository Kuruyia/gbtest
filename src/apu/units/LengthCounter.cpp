#include "LengthCounter.h"

gbtest::LengthCounter::LengthCounter()
        : m_countdown(0)
        , m_enabled(false)
{

}

void gbtest::LengthCounter::setCountdown(uint8_t countdown)
{
    m_countdown = countdown;
}

uint8_t gbtest::LengthCounter::getCountDown() const
{
    return m_countdown;
}

void gbtest::LengthCounter::setEnabled(bool enabled)
{
    m_enabled = enabled;
}

bool gbtest::LengthCounter::isEnabled() const
{
    return m_enabled;
}

bool gbtest::LengthCounter::isChannelDisabled() const
{
    return (m_enabled && m_countdown == 0);
}

void gbtest::LengthCounter::tick()
{
    // Decrease the countdown if necessary
    if (m_enabled && m_countdown > 0) {
        --m_countdown;
    }
}
