#include "APUChannel.h"

gbtest::APUChannel::APUChannel()
        : m_dacDisabledChannel(false)
        , m_lastUnitsTicked(0)
        , m_globalOn(false)
{

}

void gbtest::APUChannel::tickUnits(uint8_t unitsToTick, bool isDoubleSpeedTick)
{
    // Remember the ticked units if there are
    if ((unitsToTick & static_cast<uint8_t>(APUUnit::None)) == 0x00) {
        m_lastUnitsTicked = unitsToTick;
    }
}

void gbtest::APUChannel::setGlobalOn(bool globalOn)
{
    m_globalOn = globalOn;
}

void gbtest::APUChannel::reset()
{
    // Reset the last ticked units
    m_lastUnitsTicked = 0;
}
