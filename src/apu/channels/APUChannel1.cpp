#include "APUChannel1.h"

gbtest::APUChannel1::APUChannel1()
        : m_channel1Registers()
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

float gbtest::APUChannel1::sample() const
{
    // If the channel is disabled, return 0
    if (isChannelDisabled()) {
        return 0.f;
    }

    return (m_audioPulseWave.getSample() * (static_cast<float>(m_volumeEnvelope.getVolume()) / 15.f));
}

bool gbtest::APUChannel1::isChannelDisabled() const
{
    return m_lengthCounter.isChannelDisabled();
}

bool gbtest::APUChannel1::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // APU Channel 1 is in memory area from FF10h to FF14h
    if (addr < 0xFF10 || addr > 0xFF14) { return false; }

    switch (addr) {
    case 0xFF10:
        val = m_channel1Registers.sweep.raw;

        break;

    case 0xFF11:
        val = m_channel1Registers.soundLengthWavePatternDuty.raw;

        break;

    case 0xFF12:
        val = m_channel1Registers.volumeEnvelope.raw;

        break;

    case 0xFF14:
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
    case 0xFF10:
        m_channel1Registers.sweep.raw = val;

        break;

    case 0xFF11:
        m_channel1Registers.soundLengthWavePatternDuty.raw = val;

        // Update the generator pattern duty
        updatePatternDuty();

        // Update the length counter
        m_lengthCounter.setCountdown(m_channel1Registers.soundLengthWavePatternDuty.soundLengthData);

        break;

    case 0xFF12:
        m_channel1Registers.volumeEnvelope.raw = val;

        // Update the volume envelope
        m_volumeEnvelope.setVolume(m_channel1Registers.volumeEnvelope.envelopeInitialVolume);
        m_volumeEnvelope.setIncreasing(m_channel1Registers.volumeEnvelope.envelopeDirection);
        m_volumeEnvelope.setPeriod(m_channel1Registers.volumeEnvelope.nbEnvelopeSweep);

        break;

    case 0xFF13:
        m_channel1Registers.frequencyLow.raw = val;

        // Update the generator frequency
        updateFrequency();

        break;

    case 0xFF14:
        // TODO: Handle write to Initial
        m_channel1Registers.frequencyHigh.raw = val;

        // Update the generator frequency
        updateFrequency();

        // Update the length counter enabled state
        m_lengthCounter.setEnabled(m_channel1Registers.frequencyHigh.counterConsecutiveSelection);

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

void gbtest::APUChannel1::tick()
{
    // Tick the base class
    APUChannel::tick();

    // Tick the units
    m_audioPulseWave.tick();

    uint8_t unitsToTick = m_frameSequencer.getUnitsToTick();

    if (unitsToTick & static_cast<uint8_t>(APUUnit::LengthCounter)) {
        m_lengthCounter.tick();
    }

    if (unitsToTick & static_cast<uint8_t>(APUUnit::VolumeEnvelope)) {
        m_volumeEnvelope.tick();
    }
}

inline void gbtest::APUChannel1::updateFrequency()
{
    m_audioPulseWave.setFrequency(131072
            / (2048 - (m_channel1Registers.frequencyLow.raw | (m_channel1Registers.frequencyHigh.frequencyHigh << 8))));
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