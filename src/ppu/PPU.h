#ifndef GBTEST_PPU_H
#define GBTEST_PPU_H

#include "framebuffer/Framebuffer.h"
#include "modes/PPUModeManager.h"
#include "oam/OAM.h"
#include "oam/OAMDMA.h"
#include "vram/VRAM.h"
#include "PPURegisters.h"

#include "../platform/bus/BusProvider.h"
#include "../platform/bus/Bus.h"
#include "../utils/Tickable.h"

namespace gbtest {

class PPU
        : public BusProvider, public Tickable {

public:
    explicit PPU(Bus& bus);
    ~PPU() override = default;

    void setCGBMode(bool cgbMode);
    [[nodiscard]] bool isCGBMode() const;

    [[nodiscard]] PPUModeManager& getModeManager();
    [[nodiscard]] const PPUModeManager& getModeManager() const;

    [[nodiscard]] PPURegisters& getPpuRegisters();
    [[nodiscard]] const PPURegisters& getPpuRegisters() const;

    [[nodiscard]] OAM& getOam();
    [[nodiscard]] const OAM& getOam() const;

    [[nodiscard]] OAMDMA& getOamDma();
    [[nodiscard]] const OAMDMA& getOamDma() const;

    [[nodiscard]] VRAM& getVram();
    [[nodiscard]] const VRAM& getVram() const;

    [[nodiscard]] Framebuffer& getFramebuffer();
    [[nodiscard]] const Framebuffer& getFramebuffer() const;

    void reset();

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    void tick(bool isDoubleSpeedTick) override;

private:
    bool m_cgbMode;

    PPUModeManager m_modeManager;
    PPURegisters m_ppuRegisters;

    OAM m_oam;
    OAMDMA m_oamDma;

    VRAM m_vram;

    Framebuffer m_framebuffer;

}; // class PPU

} // namespace gbtest

#endif //GBTEST_PPU_H
