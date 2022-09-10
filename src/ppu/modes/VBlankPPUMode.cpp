#include "VBlankPPUMode.h"

gbtest::VBlankPPUMode::VBlankPPUMode()
        : m_blanking(true)
{

}

inline gbtest::PPUModeType gbtest::VBlankPPUMode::getModeType()
{
    return PPUModeType::VBlank;
}

void gbtest::VBlankPPUMode::restart()
{
    PPUMode::restart();

    m_blanking = true;
}

void gbtest::VBlankPPUMode::executeMode(bool isDoubleSpeedTick)
{
    if (m_blanking) {
        // Wait for a complete line worth of cycles
        m_cyclesToWait = 455;
        m_blanking = false;
    }
    else {
        m_finished = true;
    }
}
