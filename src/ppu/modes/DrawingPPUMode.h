#ifndef GBTEST_DRAWINGPPUMODE_H
#define GBTEST_DRAWINGPPUMODE_H

#include <deque>

#include "PPUMode.h"
#include "PPUModeType.h"

#include "../fifo/BackgroundFetcher.h"
#include "../fifo/FIFOPixelData.h"
#include "../fifo/PixelFIFO.h"
#include "../fifo/SpriteFetcher.h"
#include "../framebuffer/Framebuffer.h"
#include "../oam/OAM.h"
#include "../vram/VRAM.h"
#include "../PPURegisters.h"

namespace gbtest {

class DrawingPPUMode
        : public PPUMode {

public:
    DrawingPPUMode(Framebuffer& framebuffer, const PPURegisters& ppuRegisters, const VRAM& vram, const OAM& oam,
            const std::array<uint8_t, 10>& spriteBuffer);
    ~DrawingPPUMode() override = default;

    [[nodiscard]] static PPUModeType getModeType();

    [[nodiscard]] unsigned getTickCounter() const;

    void restart() override;

    void executeMode() override;

private:
    PixelFIFO m_backgroundPixelFifo;
    BackgroundFetcher m_backgroundFetcher;

    const std::array<uint8_t, 10>& m_spriteBuffer;
    PixelFIFO m_spritePixelFifo;
    SpriteFetcher m_spriteFetcher;

    unsigned m_currentXCoordinate;
    unsigned m_pixelsToDiscard;
    unsigned m_tickCounter;
    bool m_reachedWindowLine;

    Framebuffer& m_framebuffer;
    const PPURegisters& m_ppuRegisters;
    const OAM& m_oam;

    void drawPixel();

    void checkWindow();
    void checkSprite();

}; // class DrawingPPUMode

} // namespace gbtest

#endif //GBTEST_DRAWINGPPUMODE_H
