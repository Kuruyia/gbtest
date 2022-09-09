#include "DrawingPPUMode.h"

gbtest::DrawingPPUMode::DrawingPPUMode(Framebuffer& framebuffer, const PPURegisters& ppuRegisters, const VRAM& vram,
        SpriteBuffer& spriteBuffer)
        : m_backgroundFetcher(ppuRegisters, vram, m_backgroundPixelFifo)
        , m_spriteBuffer(spriteBuffer)
        , m_spriteFetcher(ppuRegisters, vram, m_spritePixelFifo)
        , m_spriteToCheckIdx(0)
        , m_currentXCoordinate(0)
        , m_pixelsToDiscard(0)
        , m_tickCounter(0)
        , m_reachedWindowLine(false)
        , m_framebuffer(framebuffer)
        , m_ppuRegisters(ppuRegisters)
{

}

void gbtest::DrawingPPUMode::setCGBMode(bool cgbMode)
{
    PPUMode::setCGBMode(cgbMode);

    m_backgroundFetcher.setCGBMode(cgbMode);
    m_spriteFetcher.setCGBMode(cgbMode);
}

inline gbtest::PPUModeType gbtest::DrawingPPUMode::getModeType()
{
    return PPUModeType::Drawing;
}

unsigned gbtest::DrawingPPUMode::getTickCounter() const
{
    return m_tickCounter;
}

void gbtest::DrawingPPUMode::restart()
{
    PPUMode::restart();

    m_spriteToCheckIdx = 0;
    m_currentXCoordinate = 0;
    m_pixelsToDiscard = (m_ppuRegisters.lcdPositionAndScrolling.xScroll % 8);
    m_tickCounter = 0;

    if (m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate == 0) {
        m_reachedWindowLine = false;
    }

    // Check if the window starts on the current line
    if (m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate
            == m_ppuRegisters.lcdPositionAndScrolling.yWindowPosition) {
        m_reachedWindowLine = true;
    }

    // Tell the fetchers that a line/frame has started
    if (m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate > 0) {
        m_backgroundFetcher.beginScanline();
        m_spriteFetcher.beginScanline();
    }
    else {
        m_backgroundFetcher.beginFrame();
        m_spriteFetcher.beginFrame();
    }

    // Stop the sprite fetcher
    m_spriteFetcher.stopFetchingSprite();

    // They should be empty, but just in case
    m_backgroundPixelFifo = {};
    m_spritePixelFifo = {};
}

void gbtest::DrawingPPUMode::executeMode()
{
    // Tick the fetchers
    m_spriteFetcher.tick();

    // Check for window and sprite
    if (!m_spriteFetcher.isFetchingSprite()) {
        checkWindow();

        if (m_cgbMode) {
            checkSpriteCGB();
        }
        else {
            checkSpriteDMG();
        }
    }

    // Only do the rest if we're not suspended due to sprite fetching
    if (!m_spriteFetcher.isFetchingSprite()) {
        m_backgroundFetcher.tick();

        // Try to draw a pixel
        drawPixel();

        // If we're on the 160th pixel, the scanline is finished
        if (m_currentXCoordinate == 160) {
            m_finished = true;
        }
    }

    ++m_tickCounter;
}

void gbtest::DrawingPPUMode::drawPixel()
{
    // If the background pixel queue is empty, we can't do anything
    if (m_backgroundPixelFifo.empty()) { return; }

    // Retrieve the background pixel
    FIFOPixelData backgroundPixelData = m_backgroundPixelFifo.front();
    m_backgroundPixelFifo.pop_front();

    // Only draw the pixel to the screen if it's not to be discarded
    if (m_pixelsToDiscard == 0) {
        // Retrieve the sprite pixel, if there is one
        FIFOPixelData spritePixelData;

        if (!m_spritePixelFifo.empty()) {
            spritePixelData = m_spritePixelFifo.front();
            m_spritePixelFifo.pop_front();
        }

        // Mix both pixels
        ColorUtils::ColorRGBA8888 mixedPixel{};
        mixPixels(backgroundPixelData, spritePixelData, mixedPixel);

        // Set the pixel in the framebuffer
        m_framebuffer.setPixel(m_currentXCoordinate, m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate,
                mixedPixel.raw);

        // Go to the next pixel on the line
        ++m_currentXCoordinate;
    }
    else {
        --m_pixelsToDiscard;
    }
}

void gbtest::DrawingPPUMode::mixPixels(const FIFOPixelData& backgroundPixelData, const FIFOPixelData& spritePixelData,
        ColorUtils::ColorRGBA8888& mixedPixel)
{
    /*
     * Choose the background pixel if:
     *  - The sprite pixel color index == 0 (pixel considered transparent), or
     *  - The background pixel has priority over the sprite pixel and its color index != 0, or
     *  - Sprites are disabled
     */
    if (m_ppuRegisters.lcdControl.bgAndWindowEnable
            && (spritePixelData.colorIndex == 0
                    || (spritePixelData.backgroundPriority && backgroundPixelData.colorIndex != 0)
                    || m_ppuRegisters.lcdControl.objEnable == 0)) {
        // Use the background pixel
        ColorUtils::dmgPaletteIndexToRGBA8888(
                m_ppuRegisters.dmgPalettes.bgPaletteData,
                backgroundPixelData.colorIndex,
                mixedPixel);
    }
    else if (m_ppuRegisters.lcdControl.objEnable == 1) {
        // Use the sprite pixel
        ColorUtils::dmgPaletteIndexToRGBA8888(
                (spritePixelData.palette == 0) ? m_ppuRegisters.dmgPalettes.objectPaletteData0
                                               : m_ppuRegisters.dmgPalettes.objectPaletteData1,
                spritePixelData.colorIndex,
                mixedPixel);
    }
    else {
        // Neither sprite nor background is enabled
        mixedPixel.raw = 0xFFFFFFFF;
    }
}

void gbtest::DrawingPPUMode::checkWindow()
{
    /*
     * In order to fetch the window, we must check that:
     *  - We reached the window line during the current frame (WY == LY at some point)
     *  - The window is enabled in LCDC
     *  - We reached the X window position (minus 7)
     */
    if (!m_reachedWindowLine || m_ppuRegisters.lcdControl.windowEnable == 0
            || m_currentXCoordinate + 7 < m_ppuRegisters.lcdPositionAndScrolling.xWindowPosition
            || m_backgroundFetcher.isFetchingWindow()) {
        return;
    }

    // Start fetching the window
    m_backgroundFetcher.startFetchingWindow();
    m_backgroundPixelFifo = {};
    m_pixelsToDiscard = 0;
}

void gbtest::DrawingPPUMode::checkSpriteDMG()
{
    /*
     * In order to fetch a sprite, we must check that:
     *  - We reached the X position of any sprite (minus 8)
     *
     *  We expect the sprite buffer to be sorted by the X position of the sprites it contains,
     *  so we can just check one sprite each time instead of all of them.
     */
    if (m_spriteToCheckIdx < m_spriteBuffer.getSize()
            && m_spriteBuffer[m_spriteToCheckIdx].xPosition <= m_currentXCoordinate + 8) {
        // Background fetched is paused and reset to step 1, pixel shifting is paused
        m_backgroundFetcher.resetForSpriteFetch();

        // Fetch the sprite
        m_spriteFetcher.fetchSprite(m_spriteBuffer[m_spriteToCheckIdx], m_spriteToCheckIdx);

        // Next time, check the next sprite
        ++m_spriteToCheckIdx;
    }
}

void gbtest::DrawingPPUMode::checkSpriteCGB()
{
    /*
     * In order to fetch a sprite, we must check that:
     *  - We reached the X position of any sprite (minus 8)
     */
    for (size_t i = 0; i < m_spriteBuffer.getSize(); ++i) {
        OAMEntry& currentEntry = m_spriteBuffer[i];

        if (currentEntry.xPosition <= m_currentXCoordinate + 8) {
            // Background fetched is paused and reset to step 1, pixel shifting is paused
            m_backgroundFetcher.resetForSpriteFetch();

            // Fetch the sprite
            m_spriteFetcher.fetchSprite(currentEntry, i);

            // Ensure that we're not going to process the same sprite again
            currentEntry.xPosition = 255;
        }
    }
}
