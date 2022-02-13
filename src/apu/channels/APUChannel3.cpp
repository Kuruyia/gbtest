#include "APUChannel3.h"

gbtest::APUChannel3::APUChannel3()
        : m_channel3Registers()
{

}

gbtest::Channel3Registers& gbtest::APUChannel3::getRegisters()
{
    return m_channel3Registers;
}

const gbtest::Channel3Registers& gbtest::APUChannel3::getRegisters() const
{
    return m_channel3Registers;
}

void gbtest::APUChannel3::tickUnits(uint8_t unitsToTick)
{
    // Tick the units
    // TODO: Tick the wave unit

    if (unitsToTick & static_cast<uint8_t>(APUUnit::LengthCounter)) {
        m_lengthCounter.tick();
    }

    if (unitsToTick & static_cast<uint8_t>(APUUnit::VolumeEnvelope)) {
        m_volumeEnvelope.tick();
    }
}

float gbtest::APUChannel3::sample() const
{
    // If the channel is disabled, return 0
    if (isChannelDisabled()) {
        return 0.f;
    }

    // TODO: Return the wave sample
    return 0.f;
}

bool gbtest::APUChannel3::isChannelDisabled() const
{
    return m_lengthCounter.isChannelDisabled();
}

bool gbtest::APUChannel3::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // APU Channel 3 is in memory area from FF1Ah to FF1Eh and FF30h to FF3Fh
    if ((addr < 0xFF1A || addr > 0xFF1E) && (addr < 0xFF30 || addr > 0xFF3F)) { return false; }

    switch (addr) {
    case 0xFF1A:
        val = m_channel3Registers.soundOnOff.raw;

        break;

    case 0xFF1C:
        val = m_channel3Registers.selectOutputLevel.raw;

        break;

    case 0xFF1E:
        val = m_channel3Registers.frequencyHigh.raw;

        break;

    default:
        break;
    }

    return true;
}

bool gbtest::APUChannel3::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // APU Channel 3 is in memory area from FF1Ah to FF1Eh and FF30h to FF3Fh
    if ((addr < 0xFF1A || addr > 0xFF1E) && (addr < 0xFF30 || addr > 0xFF3F)) { return false; }

    switch (addr) {
    case 0xFF1A:
        m_channel3Registers.soundOnOff.raw = val;

        break;

    case 0xFF1B:
        m_channel3Registers.soundLength.raw = val;

        // Update the length counter
        m_lengthCounter.setCountdown(m_channel3Registers.soundLength.soundLengthData);

        break;

    case 0xFF1C:
        m_channel3Registers.selectOutputLevel.raw = val;

        break;

    case 0xFF1D:
        m_channel3Registers.frequencyLow.raw = val;

        // Update the generator frequency
        updateFrequency();

        break;

    case 0xFF1E:
        m_channel3Registers.frequencyHigh.raw = val;

        // Update the generator frequency
        updateFrequency();

        // Update the length counter enabled state
        m_lengthCounter.setEnabled(m_channel3Registers.frequencyHigh.counterConsecutiveSelection);

        // Handle the trigger
        if (m_channel3Registers.frequencyHigh.trigger) {
            m_channel3Registers.frequencyHigh.trigger = 0;
            doTrigger();
        }

        break;

    default:
        break;
    }

    return true;
}

bool gbtest::APUChannel3::busReadOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // APU Channel 3 never overrides read requests
    return false;
}

bool gbtest::APUChannel3::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // APU Channel 3 never overrides write requests
    return false;
}

void gbtest::APUChannel3::updateFrequency()
{
    // TODO: Update the wave frequency
}

void gbtest::APUChannel3::doTrigger()
{
    // Dispatch the trigger event to the units
    // TODO: Dispatch the event to the wave unit
    m_lengthCounter.doTrigger();
    m_volumeEnvelope.doTrigger();
}
