#ifndef GBTEST_PPUMODEMANAGER_H
#define GBTEST_PPUMODEMANAGER_H

#include "DrawingPPUMode.h"
#include "HBlankPPUMode.h"
#include "OAMSearchPPUMode.h"
#include "VBlankPPUMode.h"

#include "PPUModeType.h"

#include "../framebuffer/Framebuffer.h"
#include "../PPURegisters.h"
#include "../../platform/bus/Bus.h"
#include "../../utils/Tickable.h"

namespace gbtest {

class PPUModeManager
        : public Tickable {

public:
    PPUModeManager(Bus& bus, Framebuffer& framebuffer, PPURegisters& ppuRegisters, const OAM& oam, const VRAM& vram);
    ~PPUModeManager() override = default;

    [[nodiscard]] PPUModeType getCurrentMode() const;

    void setCGBMode(bool cgbMode);
    [[nodiscard]] bool isCGBMode() const;

    void reset();

    void notifyLycRegisterChange();
    void notifyStatIntSourceChange();

    void tick(bool isDoubleSpeedTick) override;

private:
    OAMSearchPPUMode m_oamSearchPpuMode;
    DrawingPPUMode m_drawingPpuMode;
    HBlankPPUMode m_hblankPpuMode;
    VBlankPPUMode m_vblankPpuMode;

    PPUModeType m_currentMode;

    bool m_cgbMode;

    Bus& m_bus;
    Framebuffer& m_framebuffer;
    PPURegisters& m_ppuRegisters;

    [[nodiscard]] PPUMode& getCurrentModeInstance();

    void updateLcdStatusModeRegister();
    void updateStatInterrupt();

    void updateYLcdCoordinate(uint8_t coordinate);
    void updateLycEqualsFlag();

}; // class PPUModeManager

} // namespace gbtest

#endif //GBTEST_PPUMODEMANAGER_H
