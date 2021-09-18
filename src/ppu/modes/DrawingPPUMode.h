#ifndef GBTEST_DRAWINGPPUMODE_H
#define GBTEST_DRAWINGPPUMODE_H

#include <deque>

#include "PPUMode.h"
#include "PPUModeType.h"

#include "../fifo/BackgroundFetcher.h"
#include "../fifo/FIFOPixelData.h"
#include "../vram/VRAM.h"
#include "../PPURegisters.h"

namespace gbtest {

class DrawingPPUMode
        : public PPUMode {

public:
    DrawingPPUMode(const PPURegisters& ppuRegisters, const VRAM& vram);
    ~DrawingPPUMode() override = default;

    [[nodiscard]] static PPUModeType getModeType();

    void restart() override;

    void executeMode() override;

private:
    std::deque<FIFOPixelData> m_backgroundPixelQueue;
    BackgroundFetcher m_backgroundFetcher;

    unsigned m_currentXCoordinate;

    const PPURegisters& m_ppuRegisters;

    void drawPixel();

}; // class DrawingPPUMode

} // namespace gbtest

#endif //GBTEST_DRAWINGPPUMODE_H
