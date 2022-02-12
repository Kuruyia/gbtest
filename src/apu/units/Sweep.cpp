#include "Sweep.h"

gbtest::Sweep::Sweep(gbtest::AudioPulseWave& audioPulseWave)
        : m_audioPulseWave(audioPulseWave)
        , m_shadowFrequency(0)
        , m_channelDisabled(true)
        , m_period(0)
        , m_increasing(true)
        , m_sweepShift(0)
{

}

unsigned gbtest::Sweep::getShadowFrequency() const
{
    return m_shadowFrequency;
}

bool gbtest::Sweep::isChannelDisabled() const
{
    return m_channelDisabled;
}

void gbtest::Sweep::setPeriod(uint8_t period)
{
    m_period = period;
}

uint8_t gbtest::Sweep::getPeriod() const
{
    return m_period;
}

void gbtest::Sweep::setIncreasing(bool increasing)
{
    m_increasing = increasing;
}

bool gbtest::Sweep::isIncreasing() const
{
    return m_increasing;
}

void gbtest::Sweep::setSweepShift(uint8_t sweepShift)
{
    m_sweepShift = sweepShift;
}

uint8_t gbtest::Sweep::getSweepShift() const
{
    return m_sweepShift;
}

void gbtest::Sweep::doTrigger(uint8_t period)
{
    // Update the shadow frequency
    m_shadowFrequency = m_audioPulseWave.getFrequency();

    // Reload the period
    setPeriod(period);

    // Update the channel disabled flag
    m_channelDisabled = false;

    if (m_sweepShift != 0) {
        // Calculate a new frequency
        unsigned shiftedFrequency = (m_shadowFrequency >> m_sweepShift);

        if (!m_increasing) {
            shiftedFrequency = -shiftedFrequency;
        }

        unsigned newFrequency = (m_shadowFrequency + shiftedFrequency);

        // Do the overflow check
        if (newFrequency > 2047) {
            m_channelDisabled = true;
        }
    }
}

void gbtest::Sweep::tick()
{
    // Don't do anything if the sweep is disabled or the sweep period is zero or the sweep shift is zero
    if (m_channelDisabled || m_period == 0 || m_sweepShift == 0) {
        return;
    }

    // Decrease the period
    --m_period;

    // Calculate the new frequency
    unsigned shiftedFrequency = (m_shadowFrequency >> m_sweepShift);

    if (!m_increasing) {
        shiftedFrequency = -shiftedFrequency;
    }

    unsigned newFrequency = (m_shadowFrequency + shiftedFrequency);

    // Do the overflow check
    if (newFrequency > 2047) {
        m_channelDisabled = true;
        return;
    }

    // Set the new frequency
    m_audioPulseWave.setFrequency(newFrequency);
    m_shadowFrequency = newFrequency;

    // Calculate a new frequency again
    shiftedFrequency = (m_shadowFrequency >> m_sweepShift);

    if (!m_increasing) {
        shiftedFrequency = -shiftedFrequency;
    }

    newFrequency = (m_shadowFrequency + shiftedFrequency);

    // Do the overflow check again
    if (newFrequency > 2047) {
        m_channelDisabled = true;
    }
}
