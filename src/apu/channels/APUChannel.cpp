#include "APUChannel.h"

gbtest::APUChannel::APUChannel()
        : m_dacDisabledChannel(false)
        , m_lastUnitsTicked(0)
{

}

void gbtest::APUChannel::tickUnits(uint8_t unitsToTick, bool isDoubleSpeedTick)
{
    // Remember the ticked units
    m_lastUnitsTicked = unitsToTick;
}
