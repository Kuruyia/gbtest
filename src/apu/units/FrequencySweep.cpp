#include "FrequencySweep.h"

gbtest::FrequencySweep::FrequencySweep(gbtest::AudioPulseWave& audioPulseWave)
        : m_audioPulseWave(audioPulseWave)
        , m_shadowFrequency(0)
        , m_enabled(false)
        , m_channelDisabled(true)
        , m_period(0)
        , m_effectivePeriod(0)
        , m_decreasing(true)
        , m_sweepShift(0)
        , m_tickCountdown(0)
        , m_calculationMadeInNegateMode(false)
{

}

uint16_t gbtest::FrequencySweep::getShadowFrequency() const
{
    return m_shadowFrequency;
}

bool gbtest::FrequencySweep::isEnabled() const
{
    return m_enabled;
}

bool gbtest::FrequencySweep::isChannelDisabled() const
{
    return m_channelDisabled;
}

void gbtest::FrequencySweep::setPeriod(uint8_t period)
{
    m_period = period;
    m_effectivePeriod = period;

    // Prevent problems on next tick
    if (m_tickCountdown == 0) {
        ++m_tickCountdown;
    }

    // Emulate sweep treating a period of 0 as 8
    if (period == 0) {
        m_effectivePeriod = 8;
    }
}

uint8_t gbtest::FrequencySweep::getPeriod() const
{
    return m_period;
}

uint8_t gbtest::FrequencySweep::getEffectivePeriod() const
{
    return m_effectivePeriod;
}

void gbtest::FrequencySweep::setDecreasing(bool decreasing)
{
    // Disable the channel if leaving negate mode while a calculation already has been made
    if (m_decreasing && !decreasing && m_calculationMadeInNegateMode) {
        m_enabled = false;
        m_channelDisabled = true;
    }

    m_decreasing = decreasing;
}

bool gbtest::FrequencySweep::isDecreasing() const
{
    return m_decreasing;
}

void gbtest::FrequencySweep::setSweepShift(uint8_t sweepShift)
{
    m_sweepShift = sweepShift;
}

uint8_t gbtest::FrequencySweep::getSweepShift() const
{
    return m_sweepShift;
}

void gbtest::FrequencySweep::doTrigger()
{
    // Update the shadow frequency
    m_shadowFrequency = m_audioPulseWave.getFrequency();

    // Reset the countdown with the effective period
    m_tickCountdown = m_effectivePeriod;

    // Reset the negate mode calculation flag
    m_calculationMadeInNegateMode = false;

    // Update the internal enabled flag and enable the channel
    m_enabled = (m_sweepShift > 0 || m_period > 0);
    m_channelDisabled = false;

    if (m_sweepShift > 0) {
        // Calculate the next frequency
        uint16_t nextFrequency = calculateNextFrequency(m_shadowFrequency);

        // Perform the overflow check
        checkOverflow(nextFrequency);
    }
}

void gbtest::FrequencySweep::tick(bool isDoubleSpeedTick)
{
    // Don't do anything if the sweep is disabled
    if (!m_enabled) {
        return;
    }

    // Decrease and check the countdown
    --m_tickCountdown;

    if (m_tickCountdown > 0) {
        return;
    }

    // Reset the countdown with the effective period
    m_tickCountdown = m_effectivePeriod;

    // Don't continue if the intended period is 0
    if (m_period == 0) {
        return;
    }

    // Calculate the next frequency
    uint16_t nextFrequency = calculateNextFrequency(m_shadowFrequency);

    // Perform the overflow check
    checkOverflow(nextFrequency);

    // Only continue if the new frequency is <= 2047 and the sweep shift is not 0
    if (nextFrequency > 2047 || m_sweepShift == 0) {
        return;
    }

    // Update the shadow frequency register
    m_shadowFrequency = nextFrequency;

    // Set the new frequency
    m_audioPulseWave.setFrequency(m_shadowFrequency);

    // Calculate the next frequency and do the overflow check again, without updating the shadow frequency register
    nextFrequency = calculateNextFrequency(m_shadowFrequency);
    checkOverflow(nextFrequency);
}

uint16_t gbtest::FrequencySweep::calculateNextFrequency(uint16_t frequency)
{
    // Calculate the next frequency
    uint16_t shiftedFrequency = (frequency >> m_sweepShift);
    uint16_t nextFrequency = frequency;

    if (m_decreasing) {
        nextFrequency -= shiftedFrequency;
        m_calculationMadeInNegateMode = true;
    }
    else {
        nextFrequency += shiftedFrequency;
    }

    return nextFrequency;
}

void gbtest::FrequencySweep::checkOverflow(uint16_t frequency)
{
    // Do the overflow check
    if (frequency > 2047) {
        m_enabled = false;
    }

    m_channelDisabled = !m_enabled;
}
