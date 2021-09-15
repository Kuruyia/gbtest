#include "BackgroundFetcher.h"

gbtest::BackgroundFetcher::BackgroundFetcher(const PPURegisters& ppuRegisters, const VRAM& vram,
        std::deque<FIFOPixelData>& managedQueue)
        : Fetcher(ppuRegisters, vram, managedQueue)
        , m_currentTileNumber(0)
        , m_fetcherX(0)
        , m_fetcherY(0)
{

}

void gbtest::BackgroundFetcher::beginScanline()
{
    Fetcher::beginScanline();

    m_fetcherX = 0;
    ++m_fetcherY;
}

void gbtest::BackgroundFetcher::beginFrame()
{
    Fetcher::beginFrame();

    m_fetcherY = 0;
}

void gbtest::BackgroundFetcher::executeState()
{
    // TODO: Support Window
    switch (m_fetcherState) {
    case FetcherState::FetchTileMap: {
        // Get the correct tile map address
        const uint8_t x = ((m_ppuRegisters.lcdPositionAndScrolling.xScroll / 8) + m_fetcherX) & 0x1F;
        const uint8_t y =
                (m_ppuRegisters.lcdPositionAndScrolling.yScroll + m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate)
                        & 0xFF;
        const uint8_t offset = ((32 * (y / 8)) + x) & 0x3FF;

        // Fetch the tile number
        if (!m_vram.isReadBlocked()) {
            m_currentTileNumber = m_vram.getVramTileMaps().getTileNumberFromTileMap(offset,
                    m_ppuRegisters.lcdControl.bgTileMapArea);
        }
        else {
            m_currentTileNumber = 0xFF;
        }

        // Continue to the next state
        m_fetcherState = FetcherState::FetchTileDataLow;
        m_cyclesToWait = 2;

        break;
    }

    case FetcherState::FetchTileDataLow:
        // Continue to the next state
        m_fetcherState = FetcherState::FetchTileDataHigh;
        m_cyclesToWait = 2;

        break;

    case FetcherState::FetchTileDataHigh:
        // Continue to the next state
        m_fetcherState = FetcherState::PushFIFO;
        m_cyclesToWait = 2;

        break;

    case FetcherState::PushFIFO:
        if (m_managedQueue.empty()) {
            // We need to fill the queue
            std::swap(m_managedQueue, m_fetchedPixels);

            ++m_fetcherX;
            m_fetcherState = FetcherState::FetchTileMap;
        }

        break;
    }
}
