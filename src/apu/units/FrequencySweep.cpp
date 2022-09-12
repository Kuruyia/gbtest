#include "FrequencySweep.h"

gbtest::FrequencySweep::FrequencySweep(gbtest::AudioPulseWave& audioPulseWave)
        : m_audioPulseWave(audioPulseWave)
        , m_shadowFrequency(0)
        , m_enabled(false)
        , m_channelDisabled(true)
        , m_period(0)
        , m_decreasing(true)
        , m_sweepShift(0)
        , m_tickCounter(0)
{

}

unsigned gbtest::FrequencySweep::getShadowFrequency() const
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
}

uint8_t gbtest::FrequencySweep::getPeriod() const
{
    return m_period;
}

void gbtest::FrequencySweep::setDecreasing(bool decreasing)
{
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

    // Reset the counter
    m_tickCounter = 0;

    // Update the internal enabled flag and enable the channel
    m_enabled = (m_sweepShift > 0 || m_period > 0);
    m_channelDisabled = false;

    if (m_sweepShift > 0) {
        // Calculate the next frequency
        unsigned nextFrequency = calculateNextFrequency(m_shadowFrequency);

        // Perform the overflow check
        checkOverflow(nextFrequency);
    }
}

void gbtest::FrequencySweep::tick(bool isDoubleSpeedTick)
{
    // Don't do anything if the sweep is disabled or the sweep period is zero
    if (!m_enabled || m_period == 0) {
        return;
    }

    // Increase and check the counter
    ++m_tickCounter;

    if (m_tickCounter < m_period) {
        return;
    }

    // Reset the counter
    m_tickCounter = 0;

    // Calculate the next frequency
    unsigned nextFrequency = calculateNextFrequency(m_shadowFrequency);

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

unsigned gbtest::FrequencySweep::calculateNextFrequency(unsigned frequency) const
{
    // Calculate the next frequency
    int shiftedFrequency = (static_cast<int>(frequency) >> m_sweepShift);
    unsigned nextFrequency = frequency;

    if (m_decreasing) {
        nextFrequency -= shiftedFrequency;
    }
    else {
        nextFrequency += shiftedFrequency;
    }

    return nextFrequency;
}

void gbtest::FrequencySweep::checkOverflow(unsigned frequency)
{
    // Do the overflow check
    if (frequency > 2047) {
        m_enabled = false;
    }

    m_channelDisabled = !m_enabled;
}
