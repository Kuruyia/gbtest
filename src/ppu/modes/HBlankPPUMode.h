#ifndef GBTEST_HBLANKPPUMODE_H
#define GBTEST_HBLANKPPUMODE_H

#include "PPUMode.h"
#include "PPUModeType.h"

namespace gbtest {

class HBlankPPUMode
        : public PPUMode {

public:
    HBlankPPUMode() = default;
    ~HBlankPPUMode() override = default;

    [[nodiscard]] static PPUModeType getModeType();

    void tick() override;

}; // class HBlankPPUMode

} // namespace gbtest

#endif //GBTEST_HBLANKPPUMODE_H
