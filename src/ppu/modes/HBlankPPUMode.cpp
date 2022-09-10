#include "HBlankPPUMode.h"

gbtest::HBlankPPUMode::HBlankPPUMode()
        : m_blanking(true)
        , m_blankingCycleCount(0)
{

}

inline gbtest::PPUModeType gbtest::HBlankPPUMode::getModeType()
{
    return PPUModeType::HBlank;
}

void gbtest::HBlankPPUMode::setBlankingCycleCount(unsigned int blankingCycleCount)
{
    m_blankingCycleCount = blankingCycleCount;
}

unsigned gbtest::HBlankPPUMode::getBlankingCycleCount() const
{
    return m_blankingCycleCount;
}

void gbtest::HBlankPPUMode::restart()
{
    PPUMode::restart();

    m_blanking = true;
}

void gbtest::HBlankPPUMode::executeMode(bool isDoubleSpeedTick)
{
    if (m_blanking) {
        // Wait for the amount of cycles we were given
        m_cyclesToWait = (m_blankingCycleCount - 1);
        m_blanking = false;
    }
    else {
        m_finished = true;
    }
}