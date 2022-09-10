#include "CartridgeRTCPeripheral.h"

#include "../../platform/GameBoyFrequencies.h"

gbtest::CartridgeRTCPeripheral::CartridgeRTCPeripheral()
        : m_registers()
        , m_latchedRegisters()
        , m_tickCounter(0)
{

}

void gbtest::CartridgeRTCPeripheral::tick(bool isDoubleSpeedTick)
{
    // Don't do anything if the RTC is halted
    if (m_registers.isHalted()) {
        return;
    }

    // Increment the tick counter
    ++m_tickCounter;

    // Check if a second has elapsed
    if (m_tickCounter >= GAMEBOY_FREQUENCY) {
        // Increment the registers
        m_registers.increment();

        // Reset the tick counter
        m_tickCounter = 0;
    }
}

void gbtest::CartridgeRTCPeripheral::latch()
{
    // Update the latched registers
    m_latchedRegisters = m_registers;
}

const gbtest::CartridgeRTCPeripheralRegisters& gbtest::CartridgeRTCPeripheral::getRegisters() const
{
    return m_registers;
}

gbtest::CartridgeRTCPeripheralRegisters& gbtest::CartridgeRTCPeripheral::getRegisters()
{
    return m_registers;
}

const gbtest::CartridgeRTCPeripheralRegisters& gbtest::CartridgeRTCPeripheral::getLatchedRegisters() const
{
    return m_latchedRegisters;
}

gbtest::CartridgeRTCPeripheralRegisters& gbtest::CartridgeRTCPeripheral::getLatchedRegisters()
{
    return m_latchedRegisters;
}
