#include "FrameSequencer.h"

gbtest::FrameSequencer::FrameSequencer()
        : m_tickCounter(0)
{

}

void gbtest::FrameSequencer::tick()
{
    ++m_tickCounter;
}

uint8_t gbtest::FrameSequencer::getUnitsToTick() const
{
    uint8_t res = 0;

    // Ticking the length counter unit at 256 Hz
    if ((m_tickCounter & 0x01) == 0x00) {
        res |= static_cast<uint8_t>(APUUnit::LengthCounter);
    }

    // Ticking the volume envelope unit at 64 Hz
    if ((m_tickCounter & 0x07) == 0x07) {
        res |= static_cast<uint8_t>(APUUnit::VolumeEnvelope);
    }

    // Ticking the sweep unit at 128 Hz
    if ((m_tickCounter & 0x07) == 0x02 || (m_tickCounter & 0x07) == 0x06) {
        res |= static_cast<uint8_t>(APUUnit::Sweep);
    }

    return res;
}
