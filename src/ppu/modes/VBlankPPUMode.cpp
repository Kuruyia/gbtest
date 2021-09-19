#include "VBlankPPUMode.h"

gbtest::VBlankPPUMode::VBlankPPUMode(PPURegisters& ppuRegisters)
        : m_blankingLineCount(0)
        , m_ppuRegisters(ppuRegisters)
{

}

inline gbtest::PPUModeType gbtest::VBlankPPUMode::getModeType()
{
    return PPUModeType::VBlank;
}

void gbtest::VBlankPPUMode::restart()
{
    PPUMode::restart();

    m_blankingLineCount = 0;
}

void gbtest::VBlankPPUMode::executeMode()
{
    if (m_blankingLineCount < 10) {
        // Blank for 10 lines
        m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate = (144 + m_blankingLineCount);

        m_cyclesToWait = 456;
        ++m_blankingLineCount;
    }
    else {
        m_finished = true;
    }
}
