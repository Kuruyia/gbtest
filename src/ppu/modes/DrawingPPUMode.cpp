#include "DrawingPPUMode.h"

#include "../ColorUtils.h"

gbtest::DrawingPPUMode::DrawingPPUMode(Framebuffer& framebuffer, const PPURegisters& ppuRegisters, const VRAM& vram)
        : m_backgroundFetcher(ppuRegisters, vram, m_pixelFifo)
        , m_currentXCoordinate(0)
        , m_framebuffer(framebuffer)
        , m_ppuRegisters(ppuRegisters)
        , m_pixelsToDiscard(0)
        , m_tickCounter(0)
{

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

    m_currentXCoordinate = 0;
    m_pixelsToDiscard = (m_ppuRegisters.lcdPositionAndScrolling.xScroll % 8);
    m_tickCounter = 0;

    // Tell the fetcher that a line/frame has started
    if (m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate > 0) {
        m_backgroundFetcher.beginScanline();
    }
    else {
        m_backgroundFetcher.beginFrame();
    }

    // It should be empty, but just in case
    m_pixelFifo.clear();
}

void gbtest::DrawingPPUMode::executeMode()
{
    // Tick the fetcher
    m_backgroundFetcher.tick();

    // Try to draw a pixel
    drawPixel();

    // If we're on the 160th pixel, the scanline is finished
    if (m_currentXCoordinate == 160) {
        m_finished = true;
    }

    ++m_tickCounter;
}

void gbtest::DrawingPPUMode::drawPixel()
{
    // If the background pixel queue is empty, we can't do anything
    if (m_pixelFifo.empty()) { return; }

    // Retrieve the background pixel
    FIFOPixelData backgroundPixelData;
    m_pixelFifo.pop(backgroundPixelData);

    // Only draw the pixel to the screen if it's not to be discarded
    if (m_pixelsToDiscard == 0) {
        // Draw the pixel to the screen
        ColorUtils::ColorRGBA8888 backgroundPixelColor;

        if (m_ppuRegisters.lcdControl.bgAndWindowEnable == 1) {
            backgroundPixelColor = ColorUtils::dmgBGPaletteIndexToRGBA8888(
                    m_ppuRegisters.dmgPalettes.bgPaletteData,
                    backgroundPixelData.colorIndex);
        }
        else {
            backgroundPixelColor = ColorUtils::ColorRGBA8888(0xFF, 0xFF, 0xFF);
        }

        // Set the pixel in the framebuffer
        m_framebuffer.setPixel(m_currentXCoordinate, m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate,
                backgroundPixelColor.raw);

        // Go to the next pixel on the line
        ++m_currentXCoordinate;
    }
    else {
        --m_pixelsToDiscard;
    }
}