#include "Divider.h"

#include "../platform/GameBoyFrequencies.h"

gbtest::Divider::Divider()
        : m_dividerRegister()
        , m_tickCountdown(GAMEBOY_FREQUENCY / 16384)
{

}

void gbtest::Divider::reset()
{
    // Reset the register
    // TODO: Reset this register when STOP is executed
    m_dividerRegister.value = 0x00;
}

bool gbtest::Divider::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Divider is in memory address FF04h
    if (addr != 0xFF04) { return false; }

    // Read the value from the register
    val = m_dividerRegister.value;

    return true;
}

bool gbtest::Divider::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Divider is in memory address FF04h
    if (addr != 0xFF04) { return false; }

    // Reset the value of the register
    m_dividerRegister.value = 0x00;

    return true;
}

bool gbtest::Divider::busReadOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Divider never overrides read requests
    return false;
}

bool gbtest::Divider::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Divider never overrides write requests
    return false;
}

void gbtest::Divider::tick()
{
    // Decrease the tick countdown
    --m_tickCountdown;

    if (m_tickCountdown == 0) {
        // Reset the tick countdown
        m_tickCountdown = (GAMEBOY_FREQUENCY / 16384);

        // Increment the register value
        ++m_dividerRegister.value;
    }
}
