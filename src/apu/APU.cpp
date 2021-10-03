#include <algorithm>

#include "APU.h"

gbtest::APU::APU()
        : m_soundControlRegisters()
        , m_framebuffer()
        , m_frameCount(0)
        , m_sampleCountdown(SAMPLE_EVERY_X_TICK)
{

}

float gbtest::APU::sample() const
{
    // TODO: Mix all channels
    return m_apuChannel2.sample();
}

const gbtest::APU::AudioFramebuffer& gbtest::APU::getFramebuffer() const
{
    return m_framebuffer;
}

bool gbtest::APU::isFramebufferFull() const
{
    return m_frameCount == m_framebuffer.size();
}

size_t gbtest::APU::getFrameCount() const
{
    return m_frameCount;
}

void gbtest::APU::consumeFrames(size_t frameCount)
{
    if (frameCount <= m_frameCount) {
        // Move the extra samples to the beginning of the buffer
        std::rotate(m_framebuffer.begin(), m_framebuffer.begin() + frameCount, m_framebuffer.begin() + m_frameCount);
        m_frameCount -= frameCount;
    }
}

void gbtest::APU::tick()
{
    // Tick the channels
    m_apuChannel2.tick();

    // Check if we have to sample
    if (m_frameCount < m_framebuffer.size() && --m_sampleCountdown == 0) {
        // Take a sample
        m_framebuffer[m_frameCount] = sample();
        ++m_frameCount;

        // Reset the countdown
        m_sampleCountdown = SAMPLE_EVERY_X_TICK;
    }
}

bool gbtest::APU::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // APU is in memory area from FF10h to FF3Fh
    if (addr < 0xFF10 || addr > 0xFF3F) { return false; }

    // TODO: Dispatch to all the channels
    if (addr >= 0xFF16 && addr <= 0xFF19) {
        m_apuChannel2.busRead(addr, val, requestSource);
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
            val = m_soundControlRegisters.soundOnOff.raw;

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
    if (addr >= 0xFF16 && addr <= 0xFF19) {
        m_apuChannel2.busWrite(addr, val, requestSource);
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
