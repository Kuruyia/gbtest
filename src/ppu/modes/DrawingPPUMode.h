#ifndef GBTEST_DRAWINGPPUMODE_H
#define GBTEST_DRAWINGPPUMODE_H

#include "PPUMode.h"
#include "PPUModeType.h"

namespace gbtest {

class DrawingPPUMode
        : public PPUMode {

public:
    DrawingPPUMode() = default;
    ~DrawingPPUMode() override = default;

    [[nodiscard]] static PPUModeType getModeType();

    void tick() override;

}; // class DrawingPPUMode

} // namespace gbtest

#endif //GBTEST_DRAWINGPPUMODE_H
