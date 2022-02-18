#include "APUChannel1.h"

gbtest::APUChannel1::APUChannel1()
        : m_channel1Registers()
        , m_lengthCounter(64)
        , m_sweep(m_audioPulseWave)
{

}

gbtest::Channel1Registers& gbtest::APUChannel1::getRegisters()
{
    return m_channel1Registers;
}

const gbtest::Channel1Registers& gbtest::APUChannel1::getRegisters() const
{
    return m_channel1Registers;
}

void gbtest::APUChannel1::tickUnits(uint8_t unitsToTick)
{
    // Tick the units
    m_audioPulseWave.tick();

    if (unitsToTick & static_cast<uint8_t>(APUUnit::LengthCounter)) {
        m_lengthCounter.tick();
    }

    if (unitsToTick & static_cast<uint8_t>(APUUnit::VolumeEnvelope)) {
        m_volumeEnvelope.tick();
    }

    if (unitsToTick & static_cast<uint8_t>(APUUnit::Sweep)) {
        m_sweep.tick();
    }
}

float gbtest::APUChannel1::sample() const
{
    // If the channel is disabled, return 0
    if (isChannelDisabled()) {
        return 0.f;
    }

    return (m_audioPulseWave.getSample() * (static_cast<float>(m_volumeEnvelope.getCurrentVolume()) / 15.f));
}

bool gbtest::APUChannel1::isChannelDisabled() const
{
    return (m_lengthCounter.isChannelDisabled() || m_sweep.isChannelDisabled());
}

bool gbtest::APUChannel1::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // APU Channel 1 is in memory area from FF10h to FF14h
    if (addr < 0xFF10 || addr > 0xFF14) { return false; }

    switch (addr) {
    case 0xFF10: // [NR10] Channel 1 Sweep register
        val = m_channel1Registers.sweep.raw;

        break;

    case 0xFF11: // [NR11] Channel 1 Sound Length/Wave Pattern Duty register
        val = m_channel1Registers.soundLengthWavePatternDuty.raw;

        break;

    case 0xFF12: // [NR12] Channel 1 Volume Envelope
        val = m_channel1Registers.volumeEnvelope.raw;

        break;

    case 0xFF14: // [NR14] Channel 1 Frequency High
        val = m_channel1Registers.frequencyHigh.raw;

        break;

    default:
        break;
    }

    return true;
}

bool gbtest::APUChannel1::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // APU Channel 1 is in memory area from FF10h to FF14h
    if (addr < 0xFF10 || addr > 0xFF14) { return false; }

    switch (addr) {
    case 0xFF10: // [NR10] Channel 1 Sweep register
        m_channel1Registers.sweep.raw = val;

        // Update the sweep
        m_sweep.setPeriod(m_channel1Registers.sweep.sweepTime);
        m_sweep.setIncreasing(m_channel1Registers.sweep.sweepDirection);
        m_sweep.setSweepShift(m_channel1Registers.sweep.nbSweepShift);

        break;

    case 0xFF11: // [NR11] Channel 1 Sound Length/Wave Pattern Duty register
        m_channel1Registers.soundLengthWavePatternDuty.raw = val;

        // Update the generator pattern duty
        updatePatternDuty();

        // Update the length counter
        m_lengthCounter.setCountdown(m_channel1Registers.soundLengthWavePatternDuty.soundLengthData);

        break;

    case 0xFF12: // [NR12] Channel 1 Volume Envelope
        m_channel1Registers.volumeEnvelope.raw = val;

        // Update the volume envelope
        m_volumeEnvelope.setVolume(m_channel1Registers.volumeEnvelope.envelopeInitialVolume);
        m_volumeEnvelope.setIncreasing(m_channel1Registers.volumeEnvelope.envelopeDirection);
        m_volumeEnvelope.setPeriod(m_channel1Registers.volumeEnvelope.nbEnvelopeSweep);

        break;

    case 0xFF13: // [NR13] Channel 1 Frequency Low
        m_channel1Registers.frequencyLow.raw = val;

        // Update the generator frequency
        updateFrequency();

        break;

    case 0xFF14: // [NR14] Channel 1 Frequency High
        m_channel1Registers.frequencyHigh.raw = val;

        // Update the generator frequency
        updateFrequency();

        // Update the length counter enabled state
        m_lengthCounter.setEnabled(m_channel1Registers.frequencyHigh.counterConsecutiveSelection);

        // Handle the trigger
        if (m_channel1Registers.frequencyHigh.trigger) {
            m_channel1Registers.frequencyHigh.trigger = 0;
            doTrigger();
        }

        break;

    default:
        break;
    }

    return true;
}

bool gbtest::APUChannel1::busReadOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // APU Channel 1 never overrides read requests
    return false;
}

bool gbtest::APUChannel1::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // APU Channel 1 never overrides write requests
    return false;
}

inline void gbtest::APUChannel1::updateFrequency()
{
    m_audioPulseWave.setFrequency(
            m_channel1Registers.frequencyLow.raw | (m_channel1Registers.frequencyHigh.frequencyHigh << 8));
}

inline void gbtest::APUChannel1::updatePatternDuty()
{
    switch (m_channel1Registers.soundLengthWavePatternDuty.wavePatternDuty) {
    case 0:
        m_audioPulseWave.setPulseWavePatternDuty(PulseWavePatternDuty::Duty_12_5);
        break;

    case 1:
        m_audioPulseWave.setPulseWavePatternDuty(PulseWavePatternDuty::Duty_25);
        break;

    case 2:
        m_audioPulseWave.setPulseWavePatternDuty(PulseWavePatternDuty::Duty_50);
        break;

    case 3:
        m_audioPulseWave.setPulseWavePatternDuty(PulseWavePatternDuty::Duty_75);
        break;

    default:
        break;
    }
}

void gbtest::APUChannel1::doTrigger()
{
    // Dispatch the trigger event to the units
    m_audioPulseWave.doTrigger();
    m_lengthCounter.doTrigger();
    m_sweep.doTrigger(m_channel1Registers.sweep.sweepTime);
    m_volumeEnvelope.doTrigger();
}
