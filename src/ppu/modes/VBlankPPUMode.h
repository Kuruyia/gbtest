#ifndef GBTEST_VBLANKPPUMODE_H
#define GBTEST_VBLANKPPUMODE_H

#include "PPUMode.h"
#include "PPUModeType.h"

#include "../PPURegisters.h"

namespace gbtest {

class VBlankPPUMode
        : public PPUMode {

public:
    explicit VBlankPPUMode(PPURegisters& ppuRegisters);
    ~VBlankPPUMode() override = default;

    [[nodiscard]] static PPUModeType getModeType();

    void restart() override;

    void executeMode() override;

private:
    unsigned m_blankingLineCount;

    PPURegisters& m_ppuRegisters;

}; // class VBlankPPUMode

} // namespace gbtest

#endif //GBTEST_VBLANKPPUMODE_H
