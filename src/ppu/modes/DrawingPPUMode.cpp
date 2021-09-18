#include <utility>
#include "raylib.h"

#include "DrawingPPUMode.h"

#include "../ColorUtils.h"

gbtest::DrawingPPUMode::DrawingPPUMode(const PPURegisters& ppuRegisters, const VRAM& vram)
        : m_backgroundFetcher(ppuRegisters, vram, m_backgroundPixelQueue)
        , m_currentXCoordinate(0)
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
    ColorUtils::ColorRGB888 pixelColor = ColorUtils::dmgBGPaletteIndexToRGB888(m_ppuRegisters.dmgPalettes.bgPaletteData,
            backgroundPixelData.colorIndex);

    // TODO: Abstract this
    Color raylibColor = {pixelColor.r, pixelColor.g, pixelColor.b, 255};
    DrawPixel(static_cast<int>(m_currentXCoordinate),
            static_cast<int>(m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate), raylibColor);

    // Go to the next pixel on the line
    ++m_currentXCoordinate;
}