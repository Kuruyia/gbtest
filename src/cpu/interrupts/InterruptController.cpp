#include "InterruptController.h"

gbtest::InterruptController::InterruptController()
        : m_interruptMasterEnable(true)
        , m_delayedInterruptEnableCountdown(0)
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
    m_interruptEnable.set(static_cast<size_t>(interruptType), enabled);
}

bool gbtest::InterruptController::isInterruptEnabled(InterruptType interruptType)
{
    return m_interruptEnable.test(static_cast<size_t>(interruptType));
}

void gbtest::InterruptController::setInterruptRequested(InterruptType interruptType, bool requested)
{
    m_interruptFlag.set(static_cast<size_t>(interruptType), requested);
}

bool gbtest::InterruptController::isInterruptRequested(InterruptType interruptType)
{
    return m_interruptFlag.test(static_cast<size_t>(interruptType));
}

void gbtest::InterruptController::tick()
{
    // TODO: Manage interrupts
}

bool gbtest::InterruptController::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Interrupt Flag register
    if (addr == 0xFF0F) {
        val = m_interruptFlag.to_ulong();
        return true;
    }

    // Interrupt Enable register
    if (addr == 0xFFFF) {
        val = m_interruptEnable.to_ulong();
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
