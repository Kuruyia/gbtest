#include "DrawingPPUMode.h"

#include "../ColorUtils.h"

gbtest::DrawingPPUMode::DrawingPPUMode(Framebuffer& framebuffer, const PPURegisters& ppuRegisters, const VRAM& vram)
        : m_backgroundFetcher(ppuRegisters, vram, m_backgroundPixelQueue)
        , m_currentXCoordinate(0)
        , m_framebuffer(framebuffer)
        , m_ppuRegisters(ppuRegisters)
{

}

inline gbtest::PPUModeType gbtest::DrawingPPUMode::getModeType()
{
    return PPUModeType::Drawing;
}

void gbtest::DrawingPPUMode::restart()
{
    PPUMode::restart();

    m_currentXCoordinate = 0;

    // Tell the fetcher that a line/frame has started
    if (m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate > 0) {
        m_backgroundFetcher.beginScanline();
    }
    else {
        m_backgroundFetcher.beginFrame();
    }

    // It should be empty, but just in case
    m_backgroundPixelQueue.clear();
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
}

void gbtest::DrawingPPUMode::drawPixel()
{
    // If the background pixel queue is empty, we can't do anything
    if (m_backgroundPixelQueue.empty()) { return; }

    // Retrieve the background pixel
    FIFOPixelData backgroundPixelData = std::move(m_backgroundPixelQueue.front());
    m_backgroundPixelQueue.pop_front();

    // Draw the pixel to the screen
    ColorUtils::ColorRGBA8888 pixelColor = ColorUtils::dmgBGPaletteIndexToRGBA8888(
            m_ppuRegisters.dmgPalettes.bgPaletteData,
            backgroundPixelData.colorIndex);

    // Set the pixel in the framebuffer
    m_framebuffer.setPixel(m_currentXCoordinate, m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate, pixelColor.raw);

    // Go to the next pixel on the line
    ++m_currentXCoordinate;
}