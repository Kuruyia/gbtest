#include "BackgroundFetcher.h"

gbtest::BackgroundFetcher::BackgroundFetcher(const PPURegisters& ppuRegisters, const VRAM& vram,
        PixelFIFO& pixelFifo)
        : Fetcher(ppuRegisters, vram, pixelFifo)
        , m_currentTileNumber(0)
        , m_currentTileData(0)
        , m_fetcherX(0)
        , m_scanlineBeginSkip(true)
        , m_fetchingWindow(false)
        , m_windowLineCounter(0)
{

}

void gbtest::BackgroundFetcher::startFetchingWindow()
{
    // Reset the state of the fetcher to start fetching the window
    m_fetcherState = FetcherState::FetchTileMap;
    m_fetcherX = 0;
    m_fetchingWindow = true;
}

bool gbtest::BackgroundFetcher::isFetchingWindow() const
{
    return m_fetchingWindow;
}

void gbtest::BackgroundFetcher::resetForSpriteFetch()
{
    // Reset to step 1
    m_fetcherState = FetcherState::FetchTileMap;
}

void gbtest::BackgroundFetcher::beginScanline()
{
    Fetcher::beginScanline();

    if (m_fetchingWindow) {
        // Previous scanline had a window, increment the window line counter
        ++m_windowLineCounter;
    }

    m_fetcherX = 0;
    m_scanlineBeginSkip = true;
    m_fetchingWindow = false;
}

void gbtest::BackgroundFetcher::beginFrame()
{
    Fetcher::beginFrame();

    m_windowLineCounter = 0;
}

void gbtest::BackgroundFetcher::executeState()
{
    // The first fetch of a scanline is always wasted
    if (m_scanlineBeginSkip) {
        m_cyclesToWait = 6;
        m_scanlineBeginSkip = false;

        return;
    }

    switch (m_fetcherState) {
    case FetcherState::FetchTileMap: {
        // Fetch the tile map
        if (!m_fetchingWindow) {
            fetchBackgroundTileMap();
        }
        else {
            fetchWindowTileMap();
        }

        // Continue to the next state
        m_fetcherState = FetcherState::FetchTileData;
        m_cyclesToWait = 2;

        break;
    }

    case FetcherState::FetchTileData:
        // Fetch the tile data
        if (!m_fetchingWindow) {
            fetchBackgroundTileData();
        }
        else {
            fetchWindowTileData();
        }

        // Continue to the next state
        m_fetcherState = FetcherState::PushFIFO;
        m_cyclesToWait = 4;

        break;

    case FetcherState::PushFIFO:
        if (m_pixelFifo.empty()) {
            // Get the palette number for CGB mode
            uint8_t paletteNumber = m_currentTileAttributes.backgroundPaletteNumber;

            // Fill the queue with the fetched pixels
            for (uint8_t i = 8; i-- > 0;) {
                // Push the pixel to the FIFO
                m_pixelFifo.emplace_back(
                        getPixelFromTileData(m_currentTileData, i, m_currentTileAttributes.xFlip),
                        paletteNumber,
                        0,
                        m_currentTileAttributes.bgToOAMPriority == 1);
            }

            ++m_fetcherX;
            m_fetcherState = FetcherState::FetchTileMap;
        }

        break;
    }
}

void gbtest::BackgroundFetcher::fetchBackgroundTileMap()
{
    // Get the correct tile map address
    const uint8_t x = ((m_ppuRegisters.lcdPositionAndScrolling.xScroll / 8) + m_fetcherX) & 0x1F;
    const uint8_t y =
            (m_ppuRegisters.lcdPositionAndScrolling.yScroll + m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate)
                    & 0xFF;
    const size_t offset = ((32 * (y / 8)) + x) & 0x3FF;

    // Fetch the tile number and attributes
    if (!m_vram.isReadBlocked()) {
        m_currentTileNumber = m_vram.getVramTileMaps().getTileNumberFromTileMap(offset,
                m_ppuRegisters.lcdControl.bgTileMapArea);

        m_currentTileAttributes = m_vram.getVramMapAttributes().getTileAttributesFromTileMap(offset,
                m_ppuRegisters.lcdControl.bgTileMapArea);
    }
    else {
        m_currentTileNumber = 0xFF;
        m_currentTileAttributes.raw = 0x00;
    }
}

void gbtest::BackgroundFetcher::fetchBackgroundTileData()
{
    // Compute the line number to fetch
    uint8_t lineNumber = ((m_ppuRegisters.lcdPositionAndScrolling.yScroll +
            m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate) % 8);

    if (m_currentTileAttributes.yFlip == 1) {
        lineNumber = (7 - lineNumber);
    }

    // Emulation shortcut: Fetch both bytes during this step
    if (m_ppuRegisters.lcdControl.bgAndWindowTileDataArea == 1) {
        m_currentTileData = m_vram.getVramTileDataBanks()[m_currentTileAttributes.tileVRAMBankNumber]
                .getTileLineUsingFirstMethod(m_currentTileNumber, lineNumber);
    }
    else {
        m_currentTileData = m_vram.getVramTileDataBanks()[m_currentTileAttributes.tileVRAMBankNumber]
                .getTileLineUsingSecondMethod(static_cast<int8_t>(m_currentTileNumber), lineNumber);
    }
}

void gbtest::BackgroundFetcher::fetchWindowTileMap()
{
    // Get the correct tile map address
    const uint8_t x = m_fetcherX;
    const uint8_t y = m_windowLineCounter;
    const size_t offset = (32 * (y / 8)) + x;

    // Fetch the tile number and attributes
    if (!m_vram.isReadBlocked()) {
        m_currentTileNumber = m_vram.getVramTileMaps().getTileNumberFromTileMap(offset,
                m_ppuRegisters.lcdControl.windowTileMapArea);

        m_currentTileAttributes = m_vram.getVramMapAttributes().getTileAttributesFromTileMap(offset,
                m_ppuRegisters.lcdControl.windowTileMapArea);
    }
    else {
        m_currentTileNumber = 0xFF;
        m_currentTileAttributes.raw = 0x00;
    }
}

void gbtest::BackgroundFetcher::fetchWindowTileData()
{
    // Compute the line number to fetch
    uint8_t lineNumber = (m_windowLineCounter % 8);

    if (m_currentTileAttributes.yFlip == 1) {
        lineNumber = (7 - lineNumber);
    }

    // Emulation shortcut: Fetch both bytes during this step
    if (m_ppuRegisters.lcdControl.bgAndWindowTileDataArea == 1) {
        m_currentTileData = m_vram.getVramTileDataBanks()[m_currentTileAttributes.tileVRAMBankNumber]
                .getTileLineUsingFirstMethod(m_currentTileNumber, lineNumber);
    }
    else {
        m_currentTileData = m_vram.getVramTileDataBanks()[m_currentTileAttributes.tileVRAMBankNumber]
                .getTileLineUsingSecondMethod(static_cast<int8_t>(m_currentTileNumber), lineNumber);
    }
}
