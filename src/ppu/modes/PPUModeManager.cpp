#include "PPUModeManager.h"

gbtest::PPUModeManager::PPUModeManager(PPURegisters& ppuRegisters, OAM& oam)
        : m_oamSearchPpuMode(oam)
        , m_currentMode(PPUModeType::OAM_Search)
        , m_ppuRegisters(ppuRegisters)
{
    // Start OAM Search right away
    getCurrentModeInstance().restart();
}

gbtest::PPUModeType gbtest::PPUModeManager::getCurrentMode() const
{
    return m_currentMode;
}

void gbtest::PPUModeManager::tick()
{
    // Tick the current instance
    PPUMode& currentModeInstance = getCurrentModeInstance();
    currentModeInstance.tick();

    // Start the next mode if the current one finished
    if (currentModeInstance.isFinished()) {
        switch (m_currentMode) {
        case PPUModeType::OAM_Search:
            m_currentMode = PPUModeType::Drawing;
            break;

        case PPUModeType::Drawing:
            m_currentMode = PPUModeType::HBlank;
            break;

        case PPUModeType::HBlank:
            // Increment the current line we're on
            ++m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate;

            if (m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate < 144) {
                // We're still drawing to the LCD
                m_currentMode = PPUModeType::OAM_Search;
            }
            else {
                // Lines 144 to 153 are the vertical blanking interval
                m_currentMode = PPUModeType::VBlank;
            }

            break;

        case PPUModeType::VBlank:
            // Restart a frame
            m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate = 0;

            m_currentMode = PPUModeType::OAM_Search;

            break;
        }

        getCurrentModeInstance().restart();
    }
}

gbtest::PPUMode& gbtest::PPUModeManager::getCurrentModeInstance()
{
    switch (m_currentMode) {
    case PPUModeType::OAM_Search:
        return m_oamSearchPpuMode;

    case PPUModeType::Drawing:
        return m_drawingPpuMode;

    case PPUModeType::HBlank:
        return m_hblankPpuMode;

    case PPUModeType::VBlank:
        return m_vblankPpuMode;
    }
}
