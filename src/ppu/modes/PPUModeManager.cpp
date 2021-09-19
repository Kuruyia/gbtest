#include "PPUModeManager.h"

gbtest::PPUModeManager::PPUModeManager(Bus& bus, PPURegisters& ppuRegisters, const OAM& oam, const VRAM& vram)
        : m_drawingPpuMode(ppuRegisters, vram)
        , m_oamSearchPpuMode(ppuRegisters, oam)
        , m_currentMode(PPUModeType::OAM_Search)
        , m_bus(bus)
        , m_ppuRegisters(ppuRegisters)
{
    // Start OAM Search right away
    getCurrentModeInstance().restart();
}

gbtest::PPUModeType gbtest::PPUModeManager::getCurrentMode() const
{
    return m_currentMode;
}

void gbtest::PPUModeManager::reset()
{
    // Go to the OAM Search mode
    m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate = 0;
    m_bus.setInterruptLineHigh(InterruptType::VBlank, false);

    m_currentMode = PPUModeType::OAM_Search;

    getCurrentModeInstance().restart();
    updateLcdStatusModeRegister();
    updateStatInterrupt();
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
                m_bus.setInterruptLineHigh(InterruptType::VBlank, true);

                m_currentMode = PPUModeType::VBlank;
            }

            break;

        case PPUModeType::VBlank:
            // Restart a frame
            m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate = 0;
            m_bus.setInterruptLineHigh(InterruptType::VBlank, false);

            m_currentMode = PPUModeType::OAM_Search;

            break;
        }

        getCurrentModeInstance().restart();
        updateLcdStatusModeRegister();
    }

    // Update the STAT interrupt on the bus
    updateStatInterrupt();
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

void gbtest::PPUModeManager::updateLcdStatusModeRegister()
{
    switch (m_currentMode) {
    case PPUModeType::OAM_Search:
        m_ppuRegisters.lcdStatus.mode = 2;
        break;

    case PPUModeType::Drawing:
        m_ppuRegisters.lcdStatus.mode = 3;
        break;

    case PPUModeType::HBlank:
        m_ppuRegisters.lcdStatus.mode = 0;
        break;

    case PPUModeType::VBlank:
        m_ppuRegisters.lcdStatus.mode = 1;
        break;
    }
}

void gbtest::PPUModeManager::updateStatInterrupt()
{
    LCDStatus& lcdStatus = m_ppuRegisters.lcdStatus;

    m_bus.setInterruptLineHigh(InterruptType::LCDSTAT,
            (lcdStatus.mode0InterruptSource && m_currentMode == PPUModeType::HBlank)
                    || (lcdStatus.mode1InterruptSource && m_currentMode == PPUModeType::VBlank)
                    || (lcdStatus.mode2InterruptSource && m_currentMode == PPUModeType::OAM_Search)
                    || lcdStatus.lycEqualsLy);
}
