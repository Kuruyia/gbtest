#include "PPUModeManager.h"

gbtest::PPUModeManager::PPUModeManager()
        : m_currentMode(PPUModeType::OAM_Search)
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
            // TODO: Support VBlank
            m_currentMode = PPUModeType::OAM_Search;
            break;

        case PPUModeType::VBlank:
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
