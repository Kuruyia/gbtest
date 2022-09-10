#include "APUChannel4.h"

gbtest::APUChannel4::APUChannel4()
        : m_channel4Registers()
        , m_lengthCounter(64)
{

}

gbtest::Channel4Registers& gbtest::APUChannel4::getRegisters()
{
    return m_channel4Registers;
}

const gbtest::Channel4Registers& gbtest::APUChannel4::getRegisters() const
{
    return m_channel4Registers;
}

void gbtest::APUChannel4::tickUnits(uint8_t unitsToTick, bool isDoubleSpeedTick)
{
    // Tick the units
    m_audioNoise.tick(isDoubleSpeedTick);

    if (unitsToTick & static_cast<uint8_t>(APUUnit::LengthCounter)) {
        m_lengthCounter.tick(isDoubleSpeedTick);
    }

    if (unitsToTick & static_cast<uint8_t>(APUUnit::VolumeEnvelope)) {
        m_volumeEnvelope.tick(isDoubleSpeedTick);
    }
}

float gbtest::APUChannel4::sample() const
{
    // If the channel is disabled, return 0
    if (isChannelDisabled()) {
        return 0.f;
    }

    return (m_audioNoise.getSample() * (static_cast<float>(m_volumeEnvelope.getCurrentVolume()) / 15.f));
}

bool gbtest::APUChannel4::isChannelDisabled() const
{
    return m_lengthCounter.isChannelDisabled();
}

void gbtest::APUChannel4::reset()
{
    // Reset the registers
    for (uint16_t addr = 0xFF1F; addr <= 0xFF23; ++addr) {
        busWrite(addr, 0x00, BusRequestSource::APUChannel);
    }

    // Turn off the channel
    m_lengthCounter.setChannelDisabled(true);
}

bool gbtest::APUChannel4::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // APU Channel 4 is in memory area from FF1Fh to FF23h
    if (addr < 0xFF1F || addr > 0xFF23) { return false; }

    switch (addr) {
    case 0xFF21: // [NR42] Channel 4 Volume Envelope
        val = m_channel4Registers.volumeEnvelope.raw;

        break;

    case 0xFF22: // [NR43] Channel 4 Polynomial Counter
        val = m_channel4Registers.polynomialCounter.raw;

        break;

    case 0xFF23: // [NR44] Channel 4 Counter/consecutive; Initial
        val = (m_channel4Registers.counterConsecutiveAndInitial.raw | 0xBF);

        break;

    default:
        // Default value
        val = 0xFF;

        break;
    }

    return true;
}

bool gbtest::APUChannel4::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // APU Channel 4 is in memory area from FF1Fh to FF23h
    if (addr < 0xFF1F || addr > 0xFF23) { return false; }

    switch (addr) {
    case 0xFF20: // [NR41] Channel 4 Sound Length
        m_channel4Registers.soundLength.raw = val;

        // Fix the length counter value
        m_channel4Registers.soundLength.soundLengthData = ~m_channel4Registers.soundLength.soundLengthData;
        ++m_channel4Registers.soundLength.soundLengthData;

        // Update the length counter
        if (m_channel4Registers.soundLength.soundLengthData != 0) {
            m_lengthCounter.setCountdown(m_channel4Registers.soundLength.soundLengthData);
        }
        else {
            m_lengthCounter.setCountdown(64);
        }

        break;

    case 0xFF21: // [NR42] Channel 4 Volume Envelope
        m_channel4Registers.volumeEnvelope.raw = val;

        // Update the volume envelope
        m_volumeEnvelope.setVolume(m_channel4Registers.volumeEnvelope.envelopeInitialVolume);
        m_volumeEnvelope.setIncreasing(m_channel4Registers.volumeEnvelope.envelopeDirection);
        m_volumeEnvelope.setPeriod(m_channel4Registers.volumeEnvelope.nbEnvelopeSweep);

        break;

    case 0xFF22: // [NR43] Channel 4 Polynomial Counter
        m_channel4Registers.polynomialCounter.raw = val;

        // Update the noise generator
        m_audioNoise.setDivideRatio(m_channel4Registers.polynomialCounter.dividingRatio);
        m_audioNoise.setHalfWidth(m_channel4Registers.polynomialCounter.counterWidth);
        m_audioNoise.setShiftClockFrequency(m_channel4Registers.polynomialCounter.shiftClockFrequency);

        break;

    case 0xFF23: // [NR44] Channel 4 Counter/consecutive; Initial
        m_channel4Registers.counterConsecutiveAndInitial.raw = val;

        // Update the length counter enabled state
        m_lengthCounter.setEnabled(m_channel4Registers.counterConsecutiveAndInitial.counterConsecutiveSelection);

        // Handle the trigger
        if (m_channel4Registers.counterConsecutiveAndInitial.trigger) {
            m_channel4Registers.counterConsecutiveAndInitial.trigger = 0;
            doTrigger();
        }

        break;

    default:
        break;
    }

    return true;
}

bool gbtest::APUChannel4::busReadOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // APU Channel 4 never overrides read requests
    return false;
}

bool gbtest::APUChannel4::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // APU Channel 4 never overrides write requests
    return false;
}

void gbtest::APUChannel4::doTrigger()
{
    // Dispatch the trigger event to the units
    m_audioNoise.doTrigger();
    m_lengthCounter.doTrigger();
    m_volumeEnvelope.doTrigger();
}
