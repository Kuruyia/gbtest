#include "Fetcher.h"

gbtest::Fetcher::Fetcher(const PPURegisters& ppuRegisters, const VRAM& vram, PixelFIFO& pixelFifo)
        : m_fetcherState(FetcherState::FetchTileMap)
        , m_cgbMode(false)
        , m_paused(false)
        , m_cyclesToWait(0)
        , m_ppuRegisters(ppuRegisters)
        , m_vram(vram)
        , m_pixelFifo(pixelFifo)
{

}

void gbtest::Fetcher::setCGBMode(bool cgbMode)
{
    m_cgbMode = cgbMode;
}

bool gbtest::Fetcher::isCGBMode() const
{
    return m_cgbMode;
}

void gbtest::Fetcher::setPaused(bool paused)
{
    m_paused = paused;
}

bool gbtest::Fetcher::isPaused() const
{
    return m_paused;
}

void gbtest::Fetcher::resetState()
{
    m_fetcherState = FetcherState::FetchTileMap;
    m_cyclesToWait = 0;
}

void gbtest::Fetcher::beginScanline()
{
    resetState();
}

void gbtest::Fetcher::beginFrame()
{
    beginScanline();
}

void gbtest::Fetcher::tick(bool isDoubleSpeedTick)
{
    // Don't do anything if the fetcher is paused
    if (m_paused) { return; }

    if (m_cyclesToWait == 0) {
        // Do the work
        executeState();
    }

    if (m_cyclesToWait > 0) {
        --m_cyclesToWait;
    }
}

uint8_t gbtest::Fetcher::getPixelFromTileData(uint16_t tileData, uint8_t bitNb, bool xFlipped)
{
    // Extract the bits from the tile data
    uint8_t highBit, lowBit;

    if (!xFlipped) {
        lowBit = (tileData >> (8 + bitNb)) & 0x1;
        highBit = (tileData >> bitNb) & 0x1;
    }
    else {
        lowBit = (tileData >> (15 - bitNb)) & 0x1;
        highBit = (tileData >> (7 - bitNb)) & 0x1;
    }

    // Merge the two bits
    return (((highBit << 1) | lowBit) & 0x03);
}
