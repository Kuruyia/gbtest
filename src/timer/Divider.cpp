#include "Divider.h"

#include "../platform/GameBoyFrequencies.h"

gbtest::Divider::Divider(const gbtest::LR35902HaltState& haltState)
        : m_haltState(haltState)
        , m_dividerRegister()
        , m_tickCountdown(GAMEBOY_FREQUENCY / 16384)
{

}

gbtest::DividerReg& gbtest::Divider::getRegister()
{
    return m_dividerRegister;
}

const gbtest::DividerReg& gbtest::Divider::getRegister() const
{
    return m_dividerRegister;
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

void gbtest::Divider::tick(bool isDoubleSpeedTick)
{
    // Don't do anything if the CPU is stopped
    if (m_haltState == LR35902HaltState::Stopped) {
        return;
    }

    // Decrease the tick countdown
    --m_tickCountdown;

    if (m_tickCountdown == 0) {
        // Reset the tick countdown
        m_tickCountdown = (GAMEBOY_FREQUENCY / 16384);

        // Increment the register value
        ++m_dividerRegister.value;
    }
}
