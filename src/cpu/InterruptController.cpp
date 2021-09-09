#include "InterruptController.h"

gbtest::InterruptController::InterruptController()
        : m_interruptMasterEnable(true)
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

void gbtest::InterruptController::tick()
{
    // TODO: Manage interrupts
}
