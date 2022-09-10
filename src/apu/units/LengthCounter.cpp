#include "LengthCounter.h"

gbtest::LengthCounter::LengthCounter(uint16_t countdownReloadValue)
        : m_countdownReloadValue(countdownReloadValue)
        , m_countdown(0)
        , m_enabled(false)
        , m_channelDisabled(true)
{

}

void gbtest::LengthCounter::setCountdown(uint16_t countdown)
{
    m_countdown = countdown;
}

uint16_t gbtest::LengthCounter::getCountDown() const
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
    return m_channelDisabled;
}

void gbtest::LengthCounter::setChannelDisabled(bool channelDisabled)
{
    m_channelDisabled = channelDisabled;
}

void gbtest::LengthCounter::doTrigger(bool canTick)
{
    // Reload the countdown if necessary
    if (m_countdown == 0) {
        m_countdown = m_countdownReloadValue;

        // When the length counter got unfrozen and the frame sequencer allows ticking, tick the counter
        if (canTick) {
            tick(false);
        }
    }

    // Enable the channel
    m_channelDisabled = false;
}

void gbtest::LengthCounter::tick(bool isDoubleSpeedTick)
{
    // Decrease the countdown if necessary
    if (m_enabled && m_countdown > 0) {
        --m_countdown;
        m_channelDisabled = (m_countdown == 0);
    }
}
