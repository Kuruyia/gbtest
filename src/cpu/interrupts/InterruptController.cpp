#include "InterruptController.h"

gbtest::InterruptController::InterruptController(Bus& bus)
        : m_interruptMasterEnable(false)
        , m_delayedInterruptEnableCountdown(0)
        , m_interruptEnable(0)
        , m_interruptFlag(0)
        , m_bus(bus)
        , m_previousInterruptLines(0)
{

}

void gbtest::InterruptController::setInterruptMasterEnable(bool interruptMasterEnable)
{
    m_interruptMasterEnable = interruptMasterEnable;
}

bool gbtest::InterruptController::isInterruptMasterEnabled() const
{
    return m_interruptMasterEnable;
}

void gbtest::InterruptController::setDelayedInterruptEnableCountdown(int delayedInterruptEnableCountdown)
{
    m_delayedInterruptEnableCountdown = delayedInterruptEnableCountdown;
}

void gbtest::InterruptController::handleDelayedInterrupt()
{
    // Enable the interrupt if the countdown is at 0
    if (m_delayedInterruptEnableCountdown >= 0) {
        if (--m_delayedInterruptEnableCountdown == 0) {
            m_interruptMasterEnable = true;
        }
    }
}

void gbtest::InterruptController::setInterruptEnabled(InterruptType interruptType, bool enabled)
{
    if (enabled) {
        m_interruptEnable |= static_cast<uint8_t>(interruptType);
    }
    else {
        m_interruptEnable &= ~(static_cast<uint8_t>(interruptType));
    }
}

bool gbtest::InterruptController::isInterruptEnabled(InterruptType interruptType) const
{
    return (m_interruptEnable & static_cast<uint8_t>(interruptType)) != 0;
}

uint8_t gbtest::InterruptController::getEnabledInterrupts() const
{
    return m_interruptEnable;
}

void gbtest::InterruptController::setInterruptRequested(InterruptType interruptType, bool requested)
{
    if (requested) {
        m_interruptFlag |= static_cast<uint8_t>(interruptType);
    }
    else {
        m_interruptFlag &= ~(static_cast<uint8_t>(interruptType));
    }
}

bool gbtest::InterruptController::isInterruptRequested(InterruptType interruptType) const
{
    return (m_interruptFlag & static_cast<uint8_t>(interruptType)) != 0;
}

uint8_t gbtest::InterruptController::getRequestedInterrupts() const
{
    return m_interruptFlag;
}

uint8_t gbtest::InterruptController::getPendingInterrupts() const
{
    return (m_interruptFlag & m_interruptEnable & 0x1F);
}

void gbtest::InterruptController::tick()
{
    // Detect which interrupt lines became high at this tick, and set the Interrupt Flag register accordingly
    uint8_t interruptLines = m_bus.getInterruptLines();

    m_interruptFlag |= (m_previousInterruptLines ^ interruptLines) & interruptLines;
    m_previousInterruptLines = interruptLines;
}

bool gbtest::InterruptController::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Interrupt Flag register
    if (addr == 0xFF0F) {
        val = (m_interruptFlag | 0xE0);
        return true;
    }

    // Interrupt Enable register
    if (addr == 0xFFFF) {
        val = m_interruptEnable;
        return true;
    }

    return false;
}

bool gbtest::InterruptController::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Interrupt Flag register
    if (addr == 0xFF0F) {
        m_interruptFlag = val;
        return true;
    }

    // Interrupt Enable register
    if (addr == 0xFFFF) {
        m_interruptEnable = val;
        return true;
    }

    return false;
}

bool
gbtest::InterruptController::busReadOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Interrupt controller never overrides read requests
    return false;
}

bool gbtest::InterruptController::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Interrupt controller never overrides write requests
    return false;
}
