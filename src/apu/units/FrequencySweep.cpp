#include "FrequencySweep.h"

gbtest::FrequencySweep::FrequencySweep(gbtest::AudioPulseWave& audioPulseWave)
        : m_audioPulseWave(audioPulseWave)
        , m_shadowFrequency(0)
        , m_enabled(false)
        , m_period(0)
        , m_decreasing(true)
        , m_sweepShift(0)
        , m_tickCountdown(0)
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

    // Reload the period
    m_tickCountdown = m_period;

    // Update the internal enabled flag
    m_enabled = true;

    if (m_sweepShift > 0) {
        // Calculate the next frequency
        m_enabled = calculateNewFrequency();
    }
}

void gbtest::FrequencySweep::tick(bool isDoubleSpeedTick)
{
    // Don't do anything if the sweep is disabled or the sweep period is zero
    if (!m_enabled || m_period == 0) {
        return;
    }

    // Decrease and check the countdown
    --m_tickCountdown;

    if (m_tickCountdown != 0) {
        return;
    }

    // Reload the countdown
    m_tickCountdown = m_period;

    // Set the new frequency
    m_audioPulseWave.setFrequency(m_shadowFrequency);

    // Calculate the next frequency
    m_enabled = calculateNewFrequency();
}

bool gbtest::FrequencySweep::calculateNewFrequency()
{
    // Calculate the new frequency
    int shiftedFrequency = (static_cast<int>(m_shadowFrequency) >> m_sweepShift);

    if (m_decreasing) {
        m_shadowFrequency -= shiftedFrequency;
    }
    else {
        m_shadowFrequency += shiftedFrequency;
    }

    // Do the overflow check
    return (m_shadowFrequency <= 2047);
}
