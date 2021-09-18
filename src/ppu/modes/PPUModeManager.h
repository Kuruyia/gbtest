#ifndef GBTEST_PPUMODEMANAGER_H
#define GBTEST_PPUMODEMANAGER_H

#include "DrawingPPUMode.h"
#include "HBlankPPUMode.h"
#include "OAMSearchPPUMode.h"
#include "VBlankPPUMode.h"

#include "PPUModeType.h"

#include "../PPURegisters.h"
#include "../../platform/bus/Bus.h"
#include "../../utils/Tickable.h"

namespace gbtest {

class PPUModeManager
        : public Tickable {

public:
    PPUModeManager(Bus& bus, PPURegisters& ppuRegisters, const OAM& oam, const VRAM& vram);
    ~PPUModeManager() override = default;

    [[nodiscard]] PPUModeType getCurrentMode() const;

    void tick() override;

private:
    DrawingPPUMode m_drawingPpuMode;
    HBlankPPUMode m_hblankPpuMode;
    OAMSearchPPUMode m_oamSearchPpuMode;
    VBlankPPUMode m_vblankPpuMode;

    PPUModeType m_currentMode;

    Bus& m_bus;
    PPURegisters& m_ppuRegisters;

    [[nodiscard]] PPUMode& getCurrentModeInstance();

    void updateLcdStatusModeRegister();
    void updateStatInterrupt();

}; // class PPUModeManager

} // namespace gbtest

#endif //GBTEST_PPUMODEMANAGER_H
