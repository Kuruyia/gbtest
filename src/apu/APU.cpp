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

    // TODO: Mix all channels
    float channel1Sample = m_apuChannel1.sample();

    sampleLeft += channel1Sample;
    sampleRight += channel1Sample;

    float channel2Sample = m_apuChannel2.sample();

    sampleLeft += channel2Sample;
    sampleRight += channel2Sample;

    float channel4Sample = m_apuChannel4.sample();

    sampleLeft += channel4Sample;
    sampleRight += channel4Sample;

    sampleLeft /= 3.f;
    sampleRight /= 3.f;
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

    // TODO: Dispatch to all the channels
    if (addr >= 0xFF10 && addr <= 0xFF14) {
        m_apuChannel1.busRead(addr, val, requestSource);
    }
    else if (addr >= 0xFF16 && addr <= 0xFF19) {
        m_apuChannel2.busRead(addr, val, requestSource);
    }
    else if (addr >= 0xFF20 && addr <= 0xFF23) {
        m_apuChannel4.busRead(addr, val, requestSource);
    }
    else if (addr >= 0xFF24 && addr <= 0xFF26) {
        switch (addr) {
        case 0xFF24:
            val = m_soundControlRegisters.channelControl.raw;

            break;

        case 0xFF25:
            val = m_soundControlRegisters.soundOutputTerminalSelection.raw;

            break;

        case 0xFF26:
            val = (m_soundControlRegisters.soundOnOff.raw & 0xF0);

            // Set channel statuses
            // TODO: Do that for all 4 channels
            val |= (m_apuChannel1.isChannelDisabled()) << 0;
            val |= (m_apuChannel2.isChannelDisabled()) << 1;
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

    // TODO: Dispatch to all the channels
    if (addr >= 0xFF10 && addr <= 0xFF14) {
        m_apuChannel1.busWrite(addr, val, requestSource);
    }
    else if (addr >= 0xFF16 && addr <= 0xFF19) {
        m_apuChannel2.busWrite(addr, val, requestSource);
    }
    else if (addr >= 0xFF20 && addr <= 0xFF23) {
        m_apuChannel4.busWrite(addr, val, requestSource);
    }
    else if (addr >= 0xFF24 && addr <= 0xFF26) {
        switch (addr) {
        case 0xFF24:
            m_soundControlRegisters.channelControl.raw = val;

            break;

        case 0xFF25:
            m_soundControlRegisters.soundOutputTerminalSelection.raw = val;

            break;

        case 0xFF26:
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
