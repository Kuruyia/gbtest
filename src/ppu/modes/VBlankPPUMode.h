#ifndef GBTEST_VBLANKPPUMODE_H
#define GBTEST_VBLANKPPUMODE_H

#include "PPUMode.h"
#include "PPUModeType.h"

namespace gbtest {

class VBlankPPUMode
        : public PPUMode {

public:
    VBlankPPUMode() = default;
    ~VBlankPPUMode() override = default;

    [[nodiscard]] static PPUModeType getModeType();

    void tick() override;

}; // class VBlankPPUMode

} // namespace gbtest

#endif //GBTEST_VBLANKPPUMODE_H
