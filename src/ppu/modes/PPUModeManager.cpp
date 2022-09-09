#include "PPUModeManager.h"

#include "../../exceptions/ppu/UnknownPPUModeException.h"

gbtest::PPUModeManager::PPUModeManager(Bus& bus, Framebuffer& framebuffer, PPURegisters& ppuRegisters, const OAM& oam,
        const VRAM& vram)
        : m_oamSearchPpuMode(ppuRegisters, oam)
        , m_drawingPpuMode(framebuffer, ppuRegisters, vram, m_oamSearchPpuMode.getSpriteBuffer())
        , m_currentMode(PPUModeType::OAM_Search)
        , m_cgbMode(false)
        , m_bus(bus)
        , m_framebuffer(framebuffer)
        , m_ppuRegisters(ppuRegisters)
{
    // Start OAM Search right away
    getCurrentModeInstance().restart();
}

gbtest::PPUModeType gbtest::PPUModeManager::getCurrentMode() const
{
    return m_currentMode;
}

void gbtest::PPUModeManager::setCGBMode(bool cgbMode)
{
    m_cgbMode = cgbMode;

    m_oamSearchPpuMode.setCGBMode(cgbMode);
    m_drawingPpuMode.setCGBMode(cgbMode);
    m_hblankPpuMode.setCGBMode(cgbMode);
    m_vblankPpuMode.setCGBMode(cgbMode);
}

bool gbtest::PPUModeManager::isCGBMode() const
{
    return m_cgbMode;
}

void gbtest::PPUModeManager::reset()
{
    // Go to the OAM Search mode
    updateYLcdCoordinate(0);
    m_bus.setInterruptLineHigh(InterruptType::VBlank, false);

    m_currentMode = PPUModeType::OAM_Search;

    getCurrentModeInstance().restart();
    updateLcdStatusModeRegister();
    updateStatInterrupt();
}

void gbtest::PPUModeManager::notifyLycRegisterChange()
{
    // Update the LYC == LY and STAT interrupt states when LYC was written to
    updateLycEqualsFlag();
    updateStatInterrupt();
}

void gbtest::PPUModeManager::notifyStatIntSourceChange()
{
    // Update the STAT interrupt state when its source changed
    updateStatInterrupt();
}

void gbtest::PPUModeManager::tick()
{
    // Tick the current instance
    PPUMode& currentModeInstance = getCurrentModeInstance();
    currentModeInstance.tick();

    // Start the next mode if the current one finished
    if (currentModeInstance.isFullyFinished()) {
        switch (m_currentMode) {
        case PPUModeType::OAM_Search:
            m_currentMode = PPUModeType::Drawing;

            break;

        case PPUModeType::Drawing:
            m_hblankPpuMode.setBlankingCycleCount(376 - m_drawingPpuMode.getTickCounter());
            m_currentMode = PPUModeType::HBlank;

            break;

        case PPUModeType::HBlank:
            // Increment the current line we're on
            updateYLcdCoordinate(m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate + 1);

            if (m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate < 144) {
                // We're still drawing to the LCD
                m_currentMode = PPUModeType::OAM_Search;
            }
            else {
                // Lines 144 to 153 are the vertical blanking interval
                m_bus.setInterruptLineHigh(InterruptType::VBlank, true);
                m_framebuffer.notifyReady();

                m_currentMode = PPUModeType::VBlank;
            }

            break;

        case PPUModeType::VBlank:
            if (m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate < 153) {
                // We're still VBlanking
                updateYLcdCoordinate(m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate + 1);
            }
            else {
                // Restart a frame
                updateYLcdCoordinate(0);
                m_bus.setInterruptLineHigh(InterruptType::VBlank, false);

                m_currentMode = PPUModeType::OAM_Search;
            }

            break;
        }

        getCurrentModeInstance().restart();

        // Update the STAT register and interrupt
        updateLcdStatusModeRegister();
        updateStatInterrupt();
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

    default: break;
    }

    throw gbtest::UnknownPPUModeException();
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

    default:
        throw gbtest::UnknownPPUModeException();
    }
}

void gbtest::PPUModeManager::updateStatInterrupt()
{
    LCDStatusReg& lcdStatus = m_ppuRegisters.lcdStatus;

    m_bus.setInterruptLineHigh(InterruptType::LCDSTAT,
            (lcdStatus.mode0InterruptSource && m_currentMode == PPUModeType::HBlank)
                    || (lcdStatus.mode1InterruptSource && m_currentMode == PPUModeType::VBlank)
                    || (lcdStatus.mode2InterruptSource && m_currentMode == PPUModeType::OAM_Search)
                    || (lcdStatus.lycEqualsLyInterruptSource && lcdStatus.lycEqualsLy));
}

void gbtest::PPUModeManager::updateYLcdCoordinate(uint8_t coordinate)
{
    // Set the coordinate and update the LYC == LY flag
    m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate = coordinate;

    updateLycEqualsFlag();
}

void gbtest::PPUModeManager::updateLycEqualsFlag()
{
    m_ppuRegisters.lcdStatus.lycEqualsLy =
            (m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate == m_ppuRegisters.lcdPositionAndScrolling.lyCompare);
}
