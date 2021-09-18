#include "PPUMode.h"

gbtest::PPUMode::PPUMode()
        : m_finished(true)
        , m_cyclesToWait(0)
{

}

void gbtest::PPUMode::restart()
{
    m_finished = false;
}

bool gbtest::PPUMode::isFinished() const
{
    return m_finished;
}

void gbtest::PPUMode::tick()
{
    // Don't do anything if the mode has finished
    if (m_finished) { return; }

    if (m_cyclesToWait == 0) {
        // Execute a step of the mode
        executeMode();
    }

    if (m_cyclesToWait > 0) {
        --m_cyclesToWait;
    }
}