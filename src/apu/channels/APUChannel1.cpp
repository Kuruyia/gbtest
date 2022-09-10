#include "APUChannel1.h"

gbtest::APUChannel1::APUChannel1()
        : APUChannel()
        , m_channel1Registers()
        , m_lengthCounter(64)
        , m_frequencySweep(m_audioPulseWave)
{

}

void gbtest::APUChannel1::commitNR10()
{
    // Update the sweep
    m_frequencySweep.setPeriod(m_channel1Registers.sweep.sweepTime);
    m_frequencySweep.setDecreasing(m_channel1Registers.sweep.sweepDirection);
    m_frequencySweep.setSweepShift(m_channel1Registers.sweep.nbSweepShift);
}

void gbtest::APUChannel1::commitNR11()
{
    // Update the generator pattern duty
    updatePatternDuty();

    // Fix the length counter value
    uint8_t soundLength = ~m_channel1Registers.soundLengthWavePatternDuty.soundLengthData;
    ++soundLength;
    soundLength &= 0x3F;

    // Update the length counter
    if (soundLength != 0) {
        m_lengthCounter.setCountdown(soundLength);
    }
    else {
        m_lengthCounter.setCountdown(64);
    }
}

void gbtest::APUChannel1::commitNR12()
{
    // Update the volume envelope
    m_volumeEnvelope.setVolume(m_channel1Registers.volumeEnvelope.envelopeInitialVolume);
    m_volumeEnvelope.setIncreasing(m_channel1Registers.volumeEnvelope.envelopeDirection);
    m_volumeEnvelope.setPeriod(m_channel1Registers.volumeEnvelope.nbEnvelopeSweep);

    // Disable channel if DAC is disabled
    if (!isDACOn()) {
        m_dacDisabledChannel = true;
    }
}

void gbtest::APUChannel1::commitNR13()
{
    // Update the generator frequency
    updateFrequency();
}

void gbtest::APUChannel1::commitNR14()
{
    // Update the generator frequency
    updateFrequency();

    // Check if the length counter must be ticked after enabling it
    bool tickLengthCounter = false;

    if (!m_lengthCounter.isEnabled() && m_channel1Registers.frequencyHigh.counterConsecutiveSelection) {
        // Disabled -> enabled
        if (m_lastUnitsTicked & static_cast<uint8_t>(APUUnit::LengthCounter)) {
            tickLengthCounter = true;
        }
    }

    // Update the length counter enabled state
    m_lengthCounter.setEnabled(m_channel1Registers.frequencyHigh.counterConsecutiveSelection);

    if (tickLengthCounter) {
        m_lengthCounter.tick(false);
    }

    // Handle the trigger
    if (m_channel1Registers.frequencyHigh.trigger) {
        m_channel1Registers.frequencyHigh.trigger = 0;
        doTrigger();
    }
}

void gbtest::APUChannel1::commitRegisters()
{
    // Commit all the registers
    commitNR10();
    commitNR11();
    commitNR12();
    commitNR13();
    commitNR14();
}

gbtest::Channel1Registers& gbtest::APUChannel1::getRegisters()
{
    return m_channel1Registers;
}

const gbtest::Channel1Registers& gbtest::APUChannel1::getRegisters() const
{
    return m_channel1Registers;
}

void gbtest::APUChannel1::tickUnits(uint8_t unitsToTick, bool isDoubleSpeedTick)
{
    // Call the base class method
    APUChannel::tickUnits(unitsToTick, isDoubleSpeedTick);

    // Tick the units
    m_audioPulseWave.tick(isDoubleSpeedTick);

    if (unitsToTick & static_cast<uint8_t>(APUUnit::LengthCounter)) {
        m_lengthCounter.tick(isDoubleSpeedTick);
    }

    if (unitsToTick & static_cast<uint8_t>(APUUnit::VolumeEnvelope)) {
        m_volumeEnvelope.tick(isDoubleSpeedTick);
    }

    if (unitsToTick & static_cast<uint8_t>(APUUnit::Sweep)) {
        m_frequencySweep.tick(isDoubleSpeedTick);
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
    return m_lengthCounter.isChannelDisabled() || m_dacDisabledChannel;
}

bool gbtest::APUChannel1::isDACOn() const
{
    return (m_channel1Registers.volumeEnvelope.raw & 0xF8);
}

void gbtest::APUChannel1::reset()
{
    // Reset the registers
    for (uint16_t addr = 0xFF10; addr <= 0xFF14; ++addr) {
        busWrite(addr, 0x00, BusRequestSource::APUChannel);
    }

    // Turn off the channel
    m_lengthCounter.setChannelDisabled(true);
}

bool gbtest::APUChannel1::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // APU Channel 1 is in memory area from FF10h to FF14h
    if (addr < 0xFF10 || addr > 0xFF14) { return false; }

    switch (addr) {
    case 0xFF10: // [NR10] Channel 1 Sweep register
        val = (m_channel1Registers.sweep.raw | 0x80);

        break;

    case 0xFF11: // [NR11] Channel 1 Sound Length/Wave Pattern Duty register
        val = (m_channel1Registers.soundLengthWavePatternDuty.raw | 0x3F);

        break;

    case 0xFF12: // [NR12] Channel 1 Volume Envelope
        val = m_channel1Registers.volumeEnvelope.raw;

        break;

    case 0xFF14: // [NR14] Channel 1 Frequency High
        val = (m_channel1Registers.frequencyHigh.raw | 0xBF);

        break;

    default:
        // Default value
        val = 0xFF;

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
        commitNR10();

        break;

    case 0xFF11: // [NR11] Channel 1 Sound Length/Wave Pattern Duty register
        m_channel1Registers.soundLengthWavePatternDuty.raw = val;
        commitNR11();

        break;

    case 0xFF12: // [NR12] Channel 1 Volume Envelope
        m_channel1Registers.volumeEnvelope.raw = val;
        commitNR12();

        break;

    case 0xFF13: // [NR13] Channel 1 Frequency Low
        m_channel1Registers.frequencyLow.raw = val;
        commitNR13();

        break;

    case 0xFF14: // [NR14] Channel 1 Frequency High
        m_channel1Registers.frequencyHigh.raw = val;
        commitNR14();

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
    // Don't do anything if the DAC is off
    if (!isDACOn()) { return; }

    // Dispatch the trigger event to the units
    m_audioPulseWave.doTrigger();
    m_lengthCounter.doTrigger();
    m_frequencySweep.doTrigger();
    m_volumeEnvelope.doTrigger();

    // Enable the channel
    m_dacDisabledChannel = false;
}
