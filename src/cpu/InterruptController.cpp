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

void gbtest::InterruptController::tick()
{
    // TODO: Manage interrupts
}
