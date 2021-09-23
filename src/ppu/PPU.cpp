#include "PPU.h"

#include "modes/PPUModeType.h"

gbtest::PPU::PPU(Bus& bus)
        : m_modeManager(bus, m_framebuffer, m_ppuRegisters, m_oam, m_vram)
        , m_ppuRegisters()
        , m_oamDma(bus, m_oam)
{

}

gbtest::PPUModeManager& gbtest::PPU::getModeManager()
{
    return m_modeManager;
}

const gbtest::PPUModeManager& gbtest::PPU::getModeManager() const
{
    return m_modeManager;
}

gbtest::PPURegisters& gbtest::PPU::getPpuRegisters()
{
    return m_ppuRegisters;
}

const gbtest::PPURegisters& gbtest::PPU::getPpuRegisters() const
{
    return m_ppuRegisters;
}

gbtest::OAM& gbtest::PPU::getOam()
{
    return m_oam;
}

const gbtest::OAM& gbtest::PPU::getOam() const
{
    return m_oam;
}

gbtest::OAMDMA& gbtest::PPU::getOamDma()
{
    return m_oamDma;
}

const gbtest::OAMDMA& gbtest::PPU::getOamDma() const
{
    return m_oamDma;
}

gbtest::VRAM& gbtest::PPU::getVram()
{
    return m_vram;
}

const gbtest::VRAM& gbtest::PPU::getVram() const
{
    return m_vram;
}

gbtest::Framebuffer& gbtest::PPU::getFramebuffer()
{
    return m_framebuffer;
}

const gbtest::Framebuffer& gbtest::PPU::getFramebuffer() const
{
    return m_framebuffer;
}

void gbtest::PPU::reset()
{
    m_modeManager.reset();
}

bool gbtest::PPU::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Check if it's for one of our registers
    switch (addr) {
    case 0xFF40: // [LCDC] LCD Control
        val = m_ppuRegisters.lcdControl.raw;
        return true;

    case 0xFF41: // [STAT] LCD Status
        val = m_ppuRegisters.lcdStatus.raw;
        return true;

    case 0xFF42: // [SCY] BG Y scroll coordinate
        val = m_ppuRegisters.lcdPositionAndScrolling.yScroll;
        return true;

    case 0xFF43: // [SCX] BG X scroll coordinate
        val = m_ppuRegisters.lcdPositionAndScrolling.xScroll;
        return true;

    case 0xFF44: // [ LY] LCD Y coordinate
        val = m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate;
        return true;

    case 0xFF45: // [LYC] LY compare
        val = m_ppuRegisters.lcdPositionAndScrolling.lyCompare;
        return true;

    case 0xFF47: // [ BGP] Data for the BG palette
        val = m_ppuRegisters.dmgPalettes.bgPaletteData.raw;
        return true;

    case 0xFF48: // [OBP0] Data for the first OBJ palette
        val = m_ppuRegisters.dmgPalettes.objectPaletteData0.raw;
        return true;

    case 0xFF49: // [OBP1] Data for the second OBJ palette
        val = m_ppuRegisters.dmgPalettes.objectPaletteData1.raw;
        return true;

    case 0xFF4A: // [ WY] Window Y position
        val = m_ppuRegisters.lcdPositionAndScrolling.yWindowPosition;
        return true;

    case 0xFF4B: // [ WX] Window X position
        val = m_ppuRegisters.lcdPositionAndScrolling.xWindowPosition;
        return true;

    default:
        break;
    }

    // Dispatch the read request
    if (m_oam.busRead(addr, val, requestSource)) { return true; }
    if (m_oamDma.busRead(addr, val, requestSource)) { return true; }
    if (m_vram.busRead(addr, val, requestSource)) { return true; }

    return false;
}

bool gbtest::PPU::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Check if it's for one of our registers
    switch (addr) {
    case 0xFF40: // [LCDC] LCD Control
        if (m_ppuRegisters.lcdControl.lcdAndPpuEnable == 1 && (val & 0x80) == 0x00) {
            // PPU just stopped, reset it
            reset();
        }

        m_ppuRegisters.lcdControl.raw = val;
        return true;

    case 0xFF41: // [STAT] LCD Status
        m_ppuRegisters.lcdStatus.raw = (val & 0xF8);
        return true;

    case 0xFF42: // [SCY] BG Y scroll coordinate
        m_ppuRegisters.lcdPositionAndScrolling.yScroll = val;
        return true;

    case 0xFF43: // [SCX] BG X scroll coordinate
        m_ppuRegisters.lcdPositionAndScrolling.xScroll = val;
        return true;

    case 0xFF44: // [ LY] LCD Y coordinate
        return true;

    case 0xFF45: // [LYC] LY compare
        m_ppuRegisters.lcdPositionAndScrolling.lyCompare = val;

        // Update the LYC == LY flag
        m_ppuRegisters.lcdStatus.lycEqualsLy =
                (m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate
                        == m_ppuRegisters.lcdPositionAndScrolling.lyCompare);

        return true;

    case 0xFF47: // [ BGP] Data for the BG palette
        m_ppuRegisters.dmgPalettes.bgPaletteData.raw = val;
        return true;

    case 0xFF48: // [OBP0] Data for the first OBJ palette
        m_ppuRegisters.dmgPalettes.objectPaletteData0.raw = val;
        return true;

    case 0xFF49: // [OBP1] Data for the second OBJ palette
        m_ppuRegisters.dmgPalettes.objectPaletteData1.raw = val;
        return true;

    case 0xFF4A: // [ WY] Window Y position
        m_ppuRegisters.lcdPositionAndScrolling.yWindowPosition = val;
        return true;

    case 0xFF4B: // [ WX] Window X position
        m_ppuRegisters.lcdPositionAndScrolling.xWindowPosition = val;
        return true;

    default:
        break;
    }

    // Dispatch the write request
    if (m_oam.busWrite(addr, val, requestSource)) { return true; }
    if (m_oamDma.busWrite(addr, val, requestSource)) { return true; }
    if (m_vram.busWrite(addr, val, requestSource)) { return true; }

    return false;
}

bool gbtest::PPU::busReadOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    PPUModeType currentMode = m_modeManager.getCurrentMode();

    /*
     * Prevent reads on OAM during modes 2 and 3
     * Prevent reads on VRAM and CGB palette registers during mode 3
     */
    if (m_ppuRegisters.lcdControl.lcdAndPpuEnable == 1
            && ((addr >= 0xFE00 && addr <= 0xFE9F
                    && (currentMode == PPUModeType::OAM_Search || currentMode == PPUModeType::Drawing))
                    || (((addr >= 0x8000 && addr <= 0x9FFF) || addr == 0xFF69 || addr == 0xFF6B)
                            && currentMode == PPUModeType::Drawing))) {
        val = 0xFF;
        return true;
    }

    // Dispatch the read override request
    if (m_oam.busReadOverride(addr, val, requestSource)) { return true; }
    if (m_oamDma.busReadOverride(addr, val, requestSource)) { return true; }
    if (m_vram.busReadOverride(addr, val, requestSource)) { return true; }

    return false;
}

bool gbtest::PPU::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    PPUModeType currentMode = m_modeManager.getCurrentMode();

    /*
     * Prevent writes on OAM during modes 2 and 3
     * Prevent writes on VRAM and CGB palette registers during mode 3
     */
    if (m_ppuRegisters.lcdControl.lcdAndPpuEnable == 1
            && ((addr >= 0xFE00 && addr <= 0xFE9F
                    && (currentMode == PPUModeType::OAM_Search || currentMode == PPUModeType::Drawing))
                    || (((addr >= 0x8000 && addr <= 0x9FFF) || addr == 0xFF69 || addr == 0xFF6B)
                            && currentMode == PPUModeType::Drawing))) {
        return true;
    }

    // Dispatch the write override request
    if (m_oam.busWriteOverride(addr, val, requestSource)) { return true; }
    if (m_oamDma.busWriteOverride(addr, val, requestSource)) { return true; }
    if (m_vram.busWriteOverride(addr, val, requestSource)) { return true; }

    return false;
}

void gbtest::PPU::tick()
{
    // Tick the OAM DMA engine
    m_oamDma.tick();

    // Don't continue if the PPU is stopped
    if (m_ppuRegisters.lcdControl.lcdAndPpuEnable == 0) { return; }

    m_modeManager.tick();
}