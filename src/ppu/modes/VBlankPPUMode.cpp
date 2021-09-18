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

void gbtest::VBlankPPUMode::executeMode()
{
    if (m_blanking) {
        // The entire VBlanking takes 4560 cycles
        m_cyclesToWait = 4560;
        m_blanking = false;
    }
    else {
        m_finished = true;
    }
}
