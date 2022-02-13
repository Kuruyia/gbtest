#include "APUChannel2.h"

gbtest::APUChannel2::APUChannel2()
        : m_channel2Registers()
{

}

gbtest::Channel2Registers& gbtest::APUChannel2::getRegisters()
{
    return m_channel2Registers;
}

const gbtest::Channel2Registers& gbtest::APUChannel2::getRegisters() const
{
    return m_channel2Registers;
}

void gbtest::APUChannel2::tickUnits(uint8_t unitsToTick)
{
    // Tick the units
    m_audioPulseWave.tick();

    if (unitsToTick & static_cast<uint8_t>(APUUnit::LengthCounter)) {
        m_lengthCounter.tick();
    }

    if (unitsToTick & static_cast<uint8_t>(APUUnit::VolumeEnvelope)) {
        m_volumeEnvelope.tick();
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
    return m_lengthCounter.isChannelDisabled();
}

bool gbtest::APUChannel2::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // APU Channel 2 is in memory area from FF16h to FF19h
    if (addr < 0xFF16 || addr > 0xFF19) { return false; }

    switch (addr) {
    case 0xFF16:
        val = m_channel2Registers.soundLengthWavePatternDuty.raw;

        break;

    case 0xFF17:
        val = m_channel2Registers.volumeEnvelope.raw;

        break;

    case 0xFF19:
        val = m_channel2Registers.frequencyHigh.raw;

        break;

    default:
        break;
    }

    return true;
}

bool gbtest::APUChannel2::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // APU Channel 2 is in memory area from FF16h to FF19h
    if (addr < 0xFF16 || addr > 0xFF19) { return false; }

    switch (addr) {
    case 0xFF16:
        m_channel2Registers.soundLengthWavePatternDuty.raw = val;

        // Update the generator pattern duty
        updatePatternDuty();

        // Update the length counter
        m_lengthCounter.setCountdown(m_channel2Registers.soundLengthWavePatternDuty.soundLengthData);

        break;

    case 0xFF17:
        m_channel2Registers.volumeEnvelope.raw = val;

        // Update the volume envelope
        m_volumeEnvelope.setVolume(m_channel2Registers.volumeEnvelope.envelopeInitialVolume);
        m_volumeEnvelope.setIncreasing(m_channel2Registers.volumeEnvelope.envelopeDirection);
        m_volumeEnvelope.setPeriod(m_channel2Registers.volumeEnvelope.nbEnvelopeSweep);

        break;

    case 0xFF18:
        m_channel2Registers.frequencyLow.raw = val;

        // Update the generator frequency
        updateFrequency();

        break;

    case 0xFF19:
        m_channel2Registers.frequencyHigh.raw = val;

        // Update the generator frequency
        updateFrequency();

        // Update the length counter enabled state
        m_lengthCounter.setEnabled(m_channel2Registers.frequencyHigh.counterConsecutiveSelection);

        // Handle the trigger
        if (m_channel2Registers.frequencyHigh.trigger) {
            m_channel2Registers.frequencyHigh.trigger = 0;
            doTrigger();
        }

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
    // Dispatch the trigger event to the units
    m_audioPulseWave.doTrigger();
    m_lengthCounter.doTrigger();
    m_volumeEnvelope.doTrigger();
}
