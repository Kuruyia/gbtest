#include "APUChannel2.h"

gbtest::APUChannel2::APUChannel2()
        : APUChannel()
        , m_channel2Registers()
        , m_lengthCounter(64)
{

}

void gbtest::APUChannel2::commitNR21()
{
    // Update the generator pattern duty
    updatePatternDuty();

    // Fix the length counter value
    uint8_t soundLength = ~m_channel2Registers.soundLengthWavePatternDuty.soundLengthData;
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

void gbtest::APUChannel2::commitNR22()
{
    // Update the volume envelope
    m_volumeEnvelope.setVolume(m_channel2Registers.volumeEnvelope.envelopeInitialVolume);
    m_volumeEnvelope.setIncreasing(m_channel2Registers.volumeEnvelope.envelopeDirection);
    m_volumeEnvelope.setPeriod(m_channel2Registers.volumeEnvelope.nbEnvelopeSweep);

    // Disable channel if DAC is disabled
    if (!isDACOn()) {
        m_dacDisabledChannel = true;
    }
}

void gbtest::APUChannel2::commitNR23()
{
    // Update the generator frequency
    updateFrequency();
}

void gbtest::APUChannel2::commitNR24()
{
    // Update the generator frequency
    updateFrequency();

    // Check if the length counter must be ticked after enabling it
    bool tickLengthCounter = false;

    if (m_channel2Registers.frequencyHigh.counterConsecutiveSelection
            && (!m_lengthCounter.isEnabled() || m_channel2Registers.frequencyHigh.trigger)) {
        // Disabled -> enabled or trigger while enabled
        if (m_lastUnitsTicked & static_cast<uint8_t>(APUUnit::LengthCounter)) {
            tickLengthCounter = true;
        }
    }

    // Update the length counter enabled state
    m_lengthCounter.setEnabled(m_channel2Registers.frequencyHigh.counterConsecutiveSelection);

    if (tickLengthCounter) {
        m_lengthCounter.tick(false);
    }

    // Handle the trigger
    if (m_channel2Registers.frequencyHigh.trigger) {
        m_channel2Registers.frequencyHigh.trigger = 0;
        doTrigger();
    }
}

void gbtest::APUChannel2::commitRegisters()
{
    // Commit all the registers
    commitNR21();
    commitNR22();
    commitNR23();
    commitNR24();
}

gbtest::Channel2Registers& gbtest::APUChannel2::getRegisters()
{
    return m_channel2Registers;
}

const gbtest::Channel2Registers& gbtest::APUChannel2::getRegisters() const
{
    return m_channel2Registers;
}

void gbtest::APUChannel2::tickUnits(uint8_t unitsToTick, bool isDoubleSpeedTick)
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
}

float gbtest::APUChannel2::sample() const
{
    // If the channel is disabled, return 0
    if (isChannelDisabled()) {
        return 0.f;
    }

    return (m_audioPulseWave.getSample() * (static_cast<float>(m_volumeEnvelope.getCurrentVolume()) / 15.f));
}

bool gbtest::APUChannel2::isChannelDisabled() const
{
    return m_lengthCounter.isChannelDisabled() || m_dacDisabledChannel;
}

bool gbtest::APUChannel2::isDACOn() const
{
    return (m_channel2Registers.volumeEnvelope.raw & 0xF8);
}

void gbtest::APUChannel2::reset()
{
    // Reset the registers
    for (uint16_t addr = 0xFF15; addr <= 0xFF19; ++addr) {
        busWrite(addr, 0x00, BusRequestSource::APUChannel);
    }

    // Turn off the channel
    m_lengthCounter.setChannelDisabled(true);
}

bool gbtest::APUChannel2::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // APU Channel 2 is in memory area from FF15h to FF19h
    if (addr < 0xFF15 || addr > 0xFF19) { return false; }

    switch (addr) {
    case 0xFF16: // [NR21] Channel 2 Sound Length/Wave Pattern Duty register
        val = (m_channel2Registers.soundLengthWavePatternDuty.raw | 0x3F);

        break;

    case 0xFF17: // [NR22] Channel 2 Volume Envelope
        val = m_channel2Registers.volumeEnvelope.raw;

        break;

    case 0xFF19: // [NR24] Channel 2 Frequency High
        val = (m_channel2Registers.frequencyHigh.raw | 0xBF);

        break;

    default:
        // Default value
        val = 0xFF;

        break;
    }

    return true;
}

bool gbtest::APUChannel2::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // APU Channel 2 is in memory area from FF15h to FF19h
    if (addr < 0xFF15 || addr > 0xFF19) { return false; }

    switch (addr) {
    case 0xFF16: // [NR21] Channel 2 Sound Length/Wave Pattern Duty register
        m_channel2Registers.soundLengthWavePatternDuty.raw = val;
        commitNR21();

        break;

    case 0xFF17: // [NR22] Channel 2 Volume Envelope
        m_channel2Registers.volumeEnvelope.raw = val;
        commitNR22();

        break;

    case 0xFF18: // [NR23] Channel 2 Frequency Low
        m_channel2Registers.frequencyLow.raw = val;
        commitNR23();

        break;

    case 0xFF19: // [NR24] Channel 2 Frequency High
        m_channel2Registers.frequencyHigh.raw = val;
        commitNR24();

        break;

    default:
        break;
    }

    return true;
}

bool gbtest::APUChannel2::busReadOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // APU Channel 2 never overrides read requests
    return false;
}

bool gbtest::APUChannel2::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // APU Channel 2 never overrides write requests
    return false;
}

inline void gbtest::APUChannel2::updateFrequency()
{
    m_audioPulseWave.setFrequency(
            m_channel2Registers.frequencyLow.raw | (m_channel2Registers.frequencyHigh.frequencyHigh << 8));
}

inline void gbtest::APUChannel2::updatePatternDuty()
{
    switch (m_channel2Registers.soundLengthWavePatternDuty.wavePatternDuty) {
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

void gbtest::APUChannel2::doTrigger()
{
    // Don't do anything if the DAC is off
    if (!isDACOn()) { return; }

    // Dispatch the trigger event to the units
    m_audioPulseWave.doTrigger();
    m_lengthCounter.doTrigger();
    m_volumeEnvelope.doTrigger();

    // Enable the channel
    m_dacDisabledChannel = false;
}
