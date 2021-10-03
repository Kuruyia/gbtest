#define _USE_MATH_DEFINES
#include <cmath>

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

float gbtest::APUChannel2::sample() const
{
    // Compute the square wave frequency
    const unsigned frequency = 131072
            / (2048 - (m_channel2Registers.frequencyLow.raw | (m_channel2Registers.frequencyHigh.frequencyHigh << 8)));

    /*
     * Compute the Fourier series pulse wave:
     *  - k: Pulse width (duty cycle)
     *  - t: Time when to compute the sample
     */
    float fourierSum = 0.f;
    const float t = static_cast<float>(m_tickCount) / static_cast<float>(GAMEBOY_FREQUENCY);

    const uint8_t wavePatternDuty = m_channel2Registers.soundLengthWavePatternDuty.wavePatternDuty;
    const float k = (wavePatternDuty == 0 ? 1.f : 2.f * static_cast<float>(wavePatternDuty)) / 8.f;

    for (unsigned n = 1; n <= NB_HARMONICS; ++n) {
        fourierSum += (2.f / (static_cast<float>(n) * static_cast<float>(M_PI)))
                * ::sinf(static_cast<float>(n) * static_cast<float>(M_PI) * k)
                * ::cosf(2.f * static_cast<float>(n) * static_cast<float>(M_PI) * t * static_cast<float>(frequency));
    }

    return k + fourierSum;
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

        break;

    case 0xFF17:
        m_channel2Registers.volumeEnvelope.raw = val;

        break;

    case 0xFF18:
        m_channel2Registers.frequencyLow.raw = val;

        break;

    case 0xFF19:
        // TODO: Handle write to Initial
        m_channel2Registers.frequencyHigh.raw = val;

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
