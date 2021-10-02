#include "APUChannel.h"

gbtest::APUChannel::APUChannel()
        : m_tickCount(0)
{

}

void gbtest::APUChannel::tick()
{
    ++m_tickCount;
}
