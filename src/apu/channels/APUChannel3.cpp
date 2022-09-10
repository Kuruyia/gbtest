#include "APUChannel3.h"

gbtest::APUChannel3::APUChannel3()
        : APUChannel()
        , m_channel3Registers()
        , m_lengthCounter(256)
{

}

void gbtest::APUChannel3::commitNR30()
{
    // Update the wave unit
    m_audioWave.setEnabled(m_channel3Registers.soundOnOff.soundOff);

    // Disable channel if DAC is disabled
    if (!isDACOn()) {
        m_dacDisabledChannel = true;
    }
}

void gbtest::APUChannel3::commitNR31()
{
    // Fix the length counter value
    uint8_t soundLength = ~m_channel3Registers.soundLength.soundLengthData;
    ++soundLength;

    // Update the length counter
    if (soundLength != 0) {
        m_lengthCounter.setCountdown(soundLength);
    }
    else {
        m_lengthCounter.setCountdown(256);
    }
}

void gbtest::APUChannel3::commitNR32()
{
    // Update the wave unit
    m_audioWave.setVolume(m_channel3Registers.selectOutputLevel.selectOutputLevel);
}

void gbtest::APUChannel3::commitNR33()
{
    // Update the generator frequency
    updateFrequency();
}

void gbtest::APUChannel3::commitNR34()
{
    // Update the generator frequency
    updateFrequency();

    // Check if the length counter must be ticked after enabling it
    bool tickLengthCounter = false;

    if (m_channel3Registers.frequencyHigh.counterConsecutiveSelection && !m_lengthCounter.isEnabled()) {
        // Disabled -> enabled
        if (m_lastUnitsTicked & static_cast<uint8_t>(APUUnit::LengthCounter)) {
            tickLengthCounter = true;
        }
    }

    // Update the length counter enabled state
    m_lengthCounter.setEnabled(m_channel3Registers.frequencyHigh.counterConsecutiveSelection);

    if (tickLengthCounter) {
        m_lengthCounter.tick(false);
    }

    // Handle the trigger
    if (m_channel3Registers.frequencyHigh.trigger) {
        m_channel3Registers.frequencyHigh.trigger = 0;
        doTrigger();
    }
}

void gbtest::APUChannel3::commitRegisters()
{
    // Commit all the registers
    commitNR30();
    commitNR31();
    commitNR32();
    commitNR33();
    commitNR34();
}

gbtest::Channel3Registers& gbtest::APUChannel3::getRegisters()
{
    return m_channel3Registers;
}

const gbtest::Channel3Registers& gbtest::APUChannel3::getRegisters() const
{
    return m_channel3Registers;
}

gbtest::AudioWave::WavePatternData& gbtest::APUChannel3::getWavePatternData()
{
    return m_audioWave.getWavePatternData();
}

const gbtest::AudioWave::WavePatternData& gbtest::APUChannel3::getWavePatternData() const
{
    return m_audioWave.getWavePatternData();
}

void gbtest::APUChannel3::tickUnits(uint8_t unitsToTick, bool isDoubleSpeedTick)
{
    // Call the base class method
    APUChannel::tickUnits(unitsToTick, isDoubleSpeedTick);

    // Tick the units
    m_audioWave.tick(isDoubleSpeedTick);

    // Don't continue if there are no units to tick
    if (unitsToTick & static_cast<uint8_t>(APUUnit::None)) { return; }

    if (unitsToTick & static_cast<uint8_t>(APUUnit::LengthCounter)) {
        m_lengthCounter.tick(isDoubleSpeedTick);
    }
}

float gbtest::APUChannel3::sample() const
{
    // If the channel is disabled or not playing back, return 0
    if (isChannelDisabled() || !m_audioWave.isEnabled()) {
        return 0.f;
    }

    return m_audioWave.getSample();
}

bool gbtest::APUChannel3::isChannelDisabled() const
{
    return m_lengthCounter.isChannelDisabled() || m_dacDisabledChannel;
}

bool gbtest::APUChannel3::isDACOn() const
{
    return m_channel3Registers.soundOnOff.soundOff;
}

void gbtest::APUChannel3::reset()
{
    // Reset the registers
    for (uint16_t addr = 0xFF1A; addr <= 0xFF1E; ++addr) {
        busWrite(addr, 0x00, BusRequestSource::APUChannel);
    }

    // Turn off the channel
    m_lengthCounter.setChannelDisabled(true);
}

bool gbtest::APUChannel3::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // APU Channel 3 is in memory area from FF1Ah to FF1Eh and FF30h to FF3Fh
    if ((addr < 0xFF1A || addr > 0xFF1E) && (addr < 0xFF30 || addr > 0xFF3F)) { return false; }

    // Check if the read request is for the wave pattern data
    if (addr >= 0xFF30 && addr <= 0xFF3F) {
        val = m_audioWave.readWavePatternData(addr - 0xFF30);
        return true;
    }

    switch (addr) {
    case 0xFF1A: // [NR30] Channel 3 Sound on/off
        val = (m_channel3Registers.soundOnOff.raw | 0x7F);

        break;

    case 0xFF1C: // [NR32] Channel 3 Select output level
        val = (m_channel3Registers.selectOutputLevel.raw | 0x9F);

        break;

    case 0xFF1E: // [NR34] Channel 3 Frequency High
        val = (m_channel3Registers.frequencyHigh.raw | 0xBF);

        break;

    default:
        // Default value
        val = 0xFF;

        break;
    }

    return true;
}

bool gbtest::APUChannel3::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // APU Channel 3 is in memory area from FF1Ah to FF1Eh and FF30h to FF3Fh
    if ((addr < 0xFF1A || addr > 0xFF1E) && (addr < 0xFF30 || addr > 0xFF3F)) { return false; }

    // Check if the write request is for the wave pattern data
    if (addr >= 0xFF30 && addr <= 0xFF3F) {
        m_audioWave.writeWavePatternData(addr - 0xFF30, val);
        return true;
    }

    switch (addr) {
    case 0xFF1A: // [NR30] Channel 3 Sound on/off
        m_channel3Registers.soundOnOff.raw = val;
        commitNR30();

        break;

    case 0xFF1B: // [NR31] Channel 3 Sound Length
        m_channel3Registers.soundLength.raw = val;
        commitNR31();

        break;

    case 0xFF1C: // [NR32] Channel 3 Select output level
        m_channel3Registers.selectOutputLevel.raw = val;
        commitNR32();

        break;

    case 0xFF1D: // [NR33] Channel 3 Frequency Low
        m_channel3Registers.frequencyLow.raw = val;
        commitNR33();

        break;

    case 0xFF1E: // [NR34] Channel 3 Frequency High
        m_channel3Registers.frequencyHigh.raw = val;
        commitNR34();

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
    m_audioWave.setFrequency(
            m_channel3Registers.frequencyLow.raw | (m_channel3Registers.frequencyHigh.frequencyHigh << 8));
}

void gbtest::APUChannel3::doTrigger()
{
    // Dispatch the trigger event to the units
    m_audioWave.doTrigger();
    m_lengthCounter.doTrigger(m_lastUnitsTicked & static_cast<uint8_t>(APUUnit::LengthCounter));

    // Enable the channel if the DAC is on
    if (isDACOn()) {
        m_dacDisabledChannel = false;
    }
}
