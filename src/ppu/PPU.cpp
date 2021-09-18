#include "PPU.h"

gbtest::PPU::PPU(Bus& bus)
        : m_modeManager(m_ppuRegisters, m_oam)
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

bool gbtest::PPU::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Dispatch the read request
    if (m_oam.busRead(addr, val, requestSource)) { return true; }
    if (m_oamDma.busRead(addr, val, requestSource)) { return true; }
    if (m_vram.busRead(addr, val, requestSource)) { return true; }

    return false;
}

bool gbtest::PPU::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Dispatch the write request
    if (m_oam.busWrite(addr, val, requestSource)) { return true; }
    if (m_oamDma.busWrite(addr, val, requestSource)) { return true; }
    if (m_vram.busWrite(addr, val, requestSource)) { return true; }

    return false;
}

bool gbtest::PPU::busReadOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Dispatch the read override request
    if (m_oam.busReadOverride(addr, val, requestSource)) { return true; }
    if (m_oamDma.busReadOverride(addr, val, requestSource)) { return true; }
    if (m_vram.busReadOverride(addr, val, requestSource)) { return true; }

    return false;
}

bool gbtest::PPU::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Dispatch the write override request
    if (m_oam.busWriteOverride(addr, val, requestSource)) { return true; }
    if (m_oamDma.busWriteOverride(addr, val, requestSource)) { return true; }
    if (m_vram.busWriteOverride(addr, val, requestSource)) { return true; }

    return false;
}

void gbtest::PPU::tick()
{
    // Dispatch the tick
    m_modeManager.tick();
    m_oamDma.tick();
}
