#include <algorithm>

#include "APU.h"

gbtest::APU::APU()
        : m_soundControlRegisters()
        , m_framebuffer()
        , m_sampleCount(0)
        , m_sampleCountdown(SAMPLE_EVERY_X_TICK)
{

}

void gbtest::APU::sample(float& sampleLeft, float& sampleRight) const
{
    // Reset both samples
    sampleLeft = 0.f;
    sampleRight = 0.f;

    // Sample channel 1
    float channel1Sample = m_apuChannel1.sample();

    if (m_soundControlRegisters.soundOutputTerminalSelection.channel1So2Output) {
        sampleLeft += channel1Sample;
    }

    if (m_soundControlRegisters.soundOutputTerminalSelection.channel1So1Output) {
        sampleRight += channel1Sample;
    }

    // Sample channel 2
    float channel2Sample = m_apuChannel2.sample();

    if (m_soundControlRegisters.soundOutputTerminalSelection.channel2So2Output) {
        sampleLeft += channel2Sample;
    }

    if (m_soundControlRegisters.soundOutputTerminalSelection.channel2So1Output) {
        sampleRight += channel2Sample;
    }

    // Sample channel 3
    float channel3Sample = m_apuChannel3.sample();

    if (m_soundControlRegisters.soundOutputTerminalSelection.channel3So2Output) {
        sampleLeft += channel3Sample;
    }

    if (m_soundControlRegisters.soundOutputTerminalSelection.channel3So1Output) {
        sampleRight += channel3Sample;
    }

    // Sample channel 4
    float channel4Sample = m_apuChannel4.sample();

    if (m_soundControlRegisters.soundOutputTerminalSelection.channel4So2Output) {
        sampleLeft += channel4Sample;
    }

    if (m_soundControlRegisters.soundOutputTerminalSelection.channel4So1Output) {
        sampleRight += channel4Sample;
    }

    // Mix all channels
    sampleLeft /= 4.f;
    sampleRight /= 4.f;

    // Divide by the volume
    sampleLeft /= (static_cast<float>(m_soundControlRegisters.channelControl.so2OutputVolume) / 7.f);
    sampleRight /= (static_cast<float>(m_soundControlRegisters.channelControl.so1OutputVolume) / 7.f);
}

const gbtest::APU::AudioFramebuffer& gbtest::APU::getFramebuffer() const
{
    return m_framebuffer;
}

bool gbtest::APU::isFramebufferFull() const
{
    return m_sampleCount == m_framebuffer.size();
}

size_t gbtest::APU::getFrameCount() const
{
    return m_sampleCount / CHANNELS;
}

void gbtest::APU::consumeFrames(size_t frameCount)
{
    if ((frameCount * CHANNELS) <= m_sampleCount) {
        // Move the extra samples to the beginning of the buffer
        std::rotate(m_framebuffer.begin(), m_framebuffer.begin() + (frameCount * CHANNELS),
                m_framebuffer.begin() + m_sampleCount);
        m_sampleCount -= (frameCount * CHANNELS);
    }
}

gbtest::SoundControlRegisters& gbtest::APU::getSoundControlRegisters()
{
    return m_soundControlRegisters;
}

const gbtest::SoundControlRegisters& gbtest::APU::getSoundControlRegisters() const
{
    return m_soundControlRegisters;
}

gbtest::APUChannel1& gbtest::APU::getChannel1()
{
    return m_apuChannel1;
}

const gbtest::APUChannel1& gbtest::APU::getChannel1() const
{
    return m_apuChannel1;
}

gbtest::APUChannel2& gbtest::APU::getChannel2()
{
    return m_apuChannel2;
}

const gbtest::APUChannel2& gbtest::APU::getChannel2() const
{
    return m_apuChannel2;
}

gbtest::APUChannel3& gbtest::APU::getChannel3()
{
    return m_apuChannel3;
}

const gbtest::APUChannel3& gbtest::APU::getChannel3() const
{
    return m_apuChannel3;
}

gbtest::APUChannel4& gbtest::APU::getChannel4()
{
    return m_apuChannel4;
}

const gbtest::APUChannel4& gbtest::APU::getChannel4() const
{
    return m_apuChannel4;
}

void gbtest::APU::tick()
{
    // Tick the frame sequencer
    m_frameSequencer.tick();
    const uint8_t unitsToTick = m_frameSequencer.getUnitsToTick();

    // Tick the channels
    m_apuChannel1.tickUnits(unitsToTick);
    m_apuChannel2.tickUnits(unitsToTick);
    m_apuChannel3.tickUnits(unitsToTick);
    m_apuChannel4.tickUnits(unitsToTick);

    // Check if we have to sample
    if (m_sampleCount < m_framebuffer.size() && --m_sampleCountdown == 0) {
        // Take a sample
        sample(m_framebuffer[m_sampleCount], m_framebuffer[m_sampleCount + 1]);
        m_sampleCount += 2;

        // Reset the countdown
        m_sampleCountdown = SAMPLE_EVERY_X_TICK;
    }
}

bool gbtest::APU::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // APU is in memory area from FF10h to FF3Fh
    if (addr < 0xFF10 || addr > 0xFF3F) { return false; }

    // Dispatch to the channels or the APU registers
    if (addr >= 0xFF10 && addr <= 0xFF14) {
        m_apuChannel1.busRead(addr, val, requestSource);
    }
    else if (addr >= 0xFF16 && addr <= 0xFF19) {
        m_apuChannel2.busRead(addr, val, requestSource);
    }
    else if ((addr >= 0xFF1A && addr <= 0xFF1E) || (addr >= 0xFF30 && addr <= 0xFF3F)) {
        m_apuChannel3.busRead(addr, val, requestSource);
    }
    else if (addr >= 0xFF20 && addr <= 0xFF23) {
        m_apuChannel4.busRead(addr, val, requestSource);
    }
    else if (addr >= 0xFF24 && addr <= 0xFF26) {
        switch (addr) {
        case 0xFF24: // [NR50] Channel control / ON-OFF / Volume
            val = m_soundControlRegisters.channelControl.raw;

            break;

        case 0xFF25: // [NR51] Selection of Sound output terminal
            val = m_soundControlRegisters.soundOutputTerminalSelection.raw;

            break;

        case 0xFF26: // [NR52] Sound on/off
            val = (m_soundControlRegisters.soundOnOff.raw & 0xF0);

            // Set channel statuses
            val |= (m_apuChannel1.isChannelDisabled()) << 0;
            val |= (m_apuChannel2.isChannelDisabled()) << 1;
            val |= (m_apuChannel3.isChannelDisabled()) << 2;
            val |= (m_apuChannel4.isChannelDisabled()) << 3;

            break;

        default:
            break;
        }
    }

    return true;
}

bool gbtest::APU::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // APU is in memory area from FF10h to FF3Fh
    if (addr < 0xFF10 || addr > 0xFF3F) { return false; }

    // Dispatch to the channels or the APU registers
    if (addr >= 0xFF10 && addr <= 0xFF14) {
        m_apuChannel1.busWrite(addr, val, requestSource);
    }
    else if (addr >= 0xFF16 && addr <= 0xFF19) {
        m_apuChannel2.busWrite(addr, val, requestSource);
    }
    else if ((addr >= 0xFF1A && addr <= 0xFF1E) || (addr >= 0xFF30 && addr <= 0xFF3F)) {
        m_apuChannel3.busWrite(addr, val, requestSource);
    }
    else if (addr >= 0xFF20 && addr <= 0xFF23) {
        m_apuChannel4.busWrite(addr, val, requestSource);
    }
    else if (addr >= 0xFF24 && addr <= 0xFF26) {
        switch (addr) {
        case 0xFF24: // [NR50] Channel control / ON-OFF / Volume
            m_soundControlRegisters.channelControl.raw = val;

            break;

        case 0xFF25: // [NR51] Selection of Sound output terminal
            m_soundControlRegisters.soundOutputTerminalSelection.raw = val;

            break;

        case 0xFF26: // [NR52] Sound on/off
            m_soundControlRegisters.soundOnOff.raw = (val & 0xF0);

            break;

        default:
            break;
        }
    }

    return true;
}

bool gbtest::APU::busReadOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // APU is in memory area from FF10h to FF3Fh
    if (addr < 0xFF10 || addr > 0xFF3F) { return false; }

    // Disable access when the APU is disabled
    return m_soundControlRegisters.soundOnOff.globalOn == 0;
}

bool gbtest::APU::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // APU is in memory area from FF10h to FF3Fh
    if (addr < 0xFF10 || addr > 0xFF3F) { return false; }

    // Disable access when the APU is disabled
    return m_soundControlRegisters.soundOnOff.globalOn == 0;
}
