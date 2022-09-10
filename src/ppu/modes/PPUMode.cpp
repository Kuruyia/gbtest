#include "PPUMode.h"

gbtest::PPUMode::PPUMode()
        : m_cgbMode(false)
        , m_finished(true)
        , m_cyclesToWait(0)
{

}

void gbtest::PPUMode::setCGBMode(bool cgbMode)
{
    m_cgbMode = cgbMode;
}

bool gbtest::PPUMode::isCGBMode() const
{
    return m_cgbMode;
}

void gbtest::PPUMode::restart()
{
    m_finished = false;
}

bool gbtest::PPUMode::isFinished() const
{
    return m_finished;
}

bool gbtest::PPUMode::isFullyFinished() const
{
    return m_finished && m_cyclesToWait == 0;
}

void gbtest::PPUMode::tick(bool isDoubleSpeedTick)
{
    if (m_cyclesToWait == 0 && !m_finished) {
        // Execute a step of the mode
        executeMode(isDoubleSpeedTick);
    }

    if (m_cyclesToWait > 0) {
        --m_cyclesToWait;
    }
}