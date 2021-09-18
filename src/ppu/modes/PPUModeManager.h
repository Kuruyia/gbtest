#ifndef GBTEST_PPUMODEMANAGER_H
#define GBTEST_PPUMODEMANAGER_H

#include "DrawingPPUMode.h"
#include "HBlankPPUMode.h"
#include "OAMSearchPPUMode.h"
#include "VBlankPPUMode.h"

#include "PPUModeType.h"

#include "../PPURegisters.h"
#include "../../utils/Tickable.h"

namespace gbtest {

class PPUModeManager
        : public Tickable {

public:
    PPUModeManager(PPURegisters& ppuRegisters, OAM& oam);
    ~PPUModeManager() override = default;

    [[nodiscard]] PPUModeType getCurrentMode() const;

    void tick() override;

private:
    DrawingPPUMode m_drawingPpuMode;
    HBlankPPUMode m_hblankPpuMode;
    OAMSearchPPUMode m_oamSearchPpuMode;
    VBlankPPUMode m_vblankPpuMode;

    PPUModeType m_currentMode;

    PPURegisters& m_ppuRegisters;

    [[nodiscard]] PPUMode& getCurrentModeInstance();

}; // class PPUModeManager

} // namespace gbtest

#endif //GBTEST_PPUMODEMANAGER_H
