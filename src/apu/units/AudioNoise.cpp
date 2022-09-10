#include "AudioNoise.h"

gbtest::AudioNoise::AudioNoise()
        : m_divideRatio(0)
        , m_halfWidth(false)
        , m_shiftClockFrequency(0)
        , m_lfsr(0x7FFF)
        , m_tickCountdown(getDivisor() << m_shiftClockFrequency)
{

}

void gbtest::AudioNoise::setDivideRatio(uint8_t divideRatio)
{
    m_divideRatio = divideRatio;
}

uint8_t gbtest::AudioNoise::getDivideRatio() const
{
    return m_divideRatio;
}

void gbtest::AudioNoise::setHalfWidth(bool halfWidth)
{
    m_halfWidth = halfWidth;
}

bool gbtest::AudioNoise::isHalfWidth() const
{
    return m_halfWidth;
}

void gbtest::AudioNoise::setShiftClockFrequency(uint8_t shiftClockFrequency)
{
    m_shiftClockFrequency = shiftClockFrequency;
}

uint8_t gbtest::AudioNoise::getShiftClockFrequency() const
{
    return m_shiftClockFrequency;
}

float gbtest::AudioNoise::getSample() const
{
    if ((~m_lfsr) & 0x0001) {
        return 1.f;
    }

    return 0.f;
}

void gbtest::AudioNoise::doTrigger()
{
    // Reset the LFSR
    m_lfsr = 0x7FFF;

    // Reset the timer
    m_tickCountdown = (getDivisor() << m_shiftClockFrequency);
}

void gbtest::AudioNoise::tick(bool isDoubleSpeedTick)
{
    // Decrease the tick countdown
    --m_tickCountdown;

    // Check if we have to decrease the shift clock countdown
    if (m_tickCountdown == 0) {
        // Reset the tick countdown
        m_tickCountdown = (getDivisor() << m_shiftClockFrequency);

        // Update the sample
        updateSample();
    }
}

uint8_t gbtest::AudioNoise::getDivisor() const
{
    // Return the correct divisor depending on the stored divide ratio
    if (m_divideRatio == 0) {
        return 8;
    }

    return 16 * m_divideRatio;
}

void gbtest::AudioNoise::updateSample()
{
    // XOR the two low bits of the LFSR and shift it right by one
    uint16_t xorRes = m_lfsr;
    m_lfsr >>= 1;
    xorRes ^= m_lfsr;
    xorRes &= 0x0001;

    // Put the result in the 15th bit
    m_lfsr &= 0x3FFF;
    m_lfsr |= (xorRes << 14);

    // If the LFSR is half width, put the result in the 7th bit
    if (m_halfWidth) {
        m_lfsr &= 0x7FBF;
        m_lfsr |= (xorRes << 6);
    }
}
