#include <cmath>

#include "APUChannel2.h"

gbtest::APUChannel2::APUChannel2()
        : m_soundLengthWavePatternDuty()
        , m_volumeEnvelope()
        , m_frequencyLow()
        , m_frequencyHigh()
{

}

float gbtest::APUChannel2::sample() const
{
    // TODO: Return a sample
    return std::sinf(
            2 * static_cast<float>(M_PI) * (static_cast<float>(m_tickCount) / static_cast<float>(GAMEBOY_FREQUENCY))
                    * 440);
}

bool gbtest::APUChannel2::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // APU Channel 2 is in memory area from FF16h to FF19h
    if (addr < 0xFF16 || addr > 0xFF19) { return false; }

    switch (addr) {
    case 0xFF16:
        val = m_soundLengthWavePatternDuty.raw;

        break;

    case 0xFF17:
        val = m_volumeEnvelope.raw;

        break;

    case 0xFF19:
        val = m_frequencyHigh.raw;

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
        m_soundLengthWavePatternDuty.raw = val;

        break;

    case 0xFF17:
        m_volumeEnvelope.raw = val;

        break;

    case 0xFF18:
        m_frequencyLow.raw = val;

        break;

    case 0xFF19:
        // TODO: Handle write to Initial
        m_frequencyHigh.raw = val;

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
