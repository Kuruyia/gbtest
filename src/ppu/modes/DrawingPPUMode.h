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
#include "../oam/OAMEntry.h"
#include "../oam/SpriteBuffer.h"
#include "../vram/VRAM.h"
#include "../ColorUtils.h"
#include "../PPURegisters.h"

namespace gbtest {

class DrawingPPUMode
        : public PPUMode {

public:
    DrawingPPUMode(Framebuffer& framebuffer, const PPURegisters& ppuRegisters, const VRAM& vram,
            SpriteBuffer& spriteBuffer);
    ~DrawingPPUMode() override = default;

    [[nodiscard]] static PPUModeType getModeType();

    [[nodiscard]] unsigned getTickCounter() const;

    void restart() override;

    void executeMode() override;
    void setCGBMode(bool cgbMode) override;

private:
    PixelFIFO m_backgroundPixelFifo;
    BackgroundFetcher m_backgroundFetcher;

    SpriteBuffer& m_spriteBuffer;
    PixelFIFO m_spritePixelFifo;
    SpriteFetcher m_spriteFetcher;

    size_t m_spriteToCheckIdx;

    unsigned m_currentXCoordinate;
    unsigned m_pixelsToDiscard;
    unsigned m_tickCounter;
    bool m_reachedWindowLine;

    Framebuffer& m_framebuffer;
    const PPURegisters& m_ppuRegisters;

    void drawPixel();
    void mixPixelsDMG(const FIFOPixelData& backgroundPixelData, const FIFOPixelData& spritePixelData,
            ColorUtils::ColorRGBA8888& mixedPixel);
    void mixPixelsCGB(const FIFOPixelData& backgroundPixelData, const FIFOPixelData& spritePixelData,
            ColorUtils::ColorRGBA8888& mixedPixel);

    void checkWindow();
    void checkSpriteDMG();
    void checkSpriteCGB();

}; // class DrawingPPUMode

} // namespace gbtest

#endif //GBTEST_DRAWINGPPUMODE_H
