#include "FrameSequencer.h"

gbtest::FrameSequencer::FrameSequencer()
        : m_tickCounter(0)
        , m_step(0)
        , m_unitsToTick(0)
{

}

void gbtest::FrameSequencer::tick(bool isDoubleSpeedTick)
{
    // Increase the tick counter
    ++m_tickCounter;

    // Don't tick units on this tick
    m_unitsToTick = static_cast<uint8_t>(APUUnit::None);

    // Check if there are units to tick on this tick
    if (m_tickCounter < TICK_COUNT) { return; }

    // Reset the tick counter
    m_tickCounter = 0;

    // Set the units to tick
    m_unitsToTick = 0x00;

    // Ticking the length counter unit at 256 Hz
    if ((m_step & 0x01) == 0x00) {
        m_unitsToTick |= static_cast<uint8_t>(APUUnit::LengthCounter);
    }

    // Ticking the volume envelope unit at 64 Hz
    if ((m_step & 0x07) == 0x07) {
        m_unitsToTick |= static_cast<uint8_t>(APUUnit::VolumeEnvelope);
    }

    // Ticking the sweep unit at 128 Hz
    if ((m_step & 0x07) == 0x02 || (m_step & 0x07) == 0x06) {
        m_unitsToTick |= static_cast<uint8_t>(APUUnit::Sweep);
    }

    // Go to the next step
    ++m_step;

    if (m_step == 8) {
        m_step = 0;
    }
}

uint8_t gbtest::FrameSequencer::getUnitsToTick() const
{
    return m_unitsToTick;
}

void gbtest::FrameSequencer::reset()
{
    m_tickCounter = 0;
    m_step = 0;
}
