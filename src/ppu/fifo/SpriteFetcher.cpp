#include <algorithm>

#include "SpriteFetcher.h"

gbtest::SpriteFetcher::SpriteFetcher(const gbtest::PPURegisters& ppuRegisters, const gbtest::VRAM& vram,
        gbtest::PixelFIFO& pixelFifo)
        : Fetcher(ppuRegisters, vram, pixelFifo)
        , m_fetchingSprite(false)
        , m_spriteToFetch()
        , m_oamIndex(0)
        , m_currentTileData(0)
{

}

void gbtest::SpriteFetcher::fetchSprite(const OAMEntry& spriteToFetch, size_t oamIndex)
{
    m_fetchingSprite = true;
    m_spriteToFetch = spriteToFetch;
    m_oamIndex = oamIndex;
}

void gbtest::SpriteFetcher::stopFetchingSprite()
{
    m_fetchingSprite = false;
}

bool gbtest::SpriteFetcher::isFetchingSprite() const
{
    return m_fetchingSprite;
}

const gbtest::OAMEntry& gbtest::SpriteFetcher::getSpriteToFetch() const
{
    return m_spriteToFetch;
}

void gbtest::SpriteFetcher::executeState()
{
    switch (m_fetcherState) {
    case FetcherState::FetchTileMap: {
        // Nothing to do here, the tile map is already in the OAM entry

        // Continue to the next state
        m_fetcherState = FetcherState::FetchTileData;
        m_cyclesToWait = 2;

        break;
    }

    case FetcherState::FetchTileData: {
        // Fetch the tile data
        uint8_t lineNumber;

        // Select the line number depending on the Y flip flag
        if (m_spriteToFetch.flags.yFlip == 0) {
            lineNumber = m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate + 16 - m_spriteToFetch.yPosition;
        }
        else {
            // Where the sprite ends depends on the current object size flag
            if (m_ppuRegisters.lcdControl.objSize == 0) {
                lineNumber =
                        7 - (m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate + 16 - m_spriteToFetch.yPosition);
            }
            else {
                lineNumber =
                        15 - (m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate + 16 - m_spriteToFetch.yPosition);
            }
        }

        // Correct the tile index if needed
        uint8_t tileIndex = m_spriteToFetch.tileIndex;

        if (m_ppuRegisters.lcdControl.objSize == 1) {
            tileIndex &= 0xFE;
        }

        // Get the VRAM bank if in CGB mode
        uint8_t tileBank = 0;

        if (m_cgbMode) {
            tileBank = m_spriteToFetch.flags.tileVramBank;
        }

        m_currentTileData = m_vram.getVramTileDataBanks()[tileBank].getTileLineUsingFirstMethod(tileIndex, lineNumber);

        // Continue to the next state
        m_fetcherState = FetcherState::PushFIFO;
        m_cyclesToWait = 4;

        break;
    }

    case FetcherState::PushFIFO:
        // Fill the queue with the fetched pixels
        uint8_t currentPixel = 8;

        // Get the amount of pixels that's going to be overwritten
        uint8_t endPixelOverwrite = (8 - m_pixelFifo.size());

        // If the sprite starts before the "beginning of the line", we need not push its pixels outside the viewport
        if (m_spriteToFetch.xPosition < 8) {
            currentPixel -= (8 - m_spriteToFetch.xPosition);
            endPixelOverwrite -= std::min<uint8_t>(8 - m_spriteToFetch.xPosition, endPixelOverwrite);
        }

        // Get the palette number according to the current CGB mode
        uint8_t paletteNumber;

        if (!m_cgbMode) {
            paletteNumber = m_spriteToFetch.flags.dmgPaletteNumber;
        }
        else {
            paletteNumber = m_spriteToFetch.flags.cgbPaletteNumber;
        }

        // First, overwrite any "invisible" pixel already in the FIFO
        auto fifoIter = m_pixelFifo.begin();

        for (; currentPixel-- > endPixelOverwrite;) {
            if (fifoIter->colorIndex == 0x00) {
                // Overwrite the pixel
                fifoIter->colorIndex = getPixelFromTileData(m_currentTileData, currentPixel, m_spriteToFetch.flags.xFlip);
                fifoIter->palette = paletteNumber;
                fifoIter->spriteOamIndex = m_oamIndex;
                fifoIter->backgroundPriority = (m_spriteToFetch.flags.bgAndWindowsOverObj == 1);
            }

            ++fifoIter;
        }

        // Then, add the remaining pixels
        ++currentPixel;

        for (; currentPixel-- > 0;) {
            // Push the pixel to the FIFO
            m_pixelFifo.emplace_back(
                    getPixelFromTileData(m_currentTileData, currentPixel, m_spriteToFetch.flags.xFlip),
                    paletteNumber,
                    m_oamIndex,
                    m_spriteToFetch.flags.bgAndWindowsOverObj == 1);
        }

        // Stop sprite fetching and reset to the first mode
        m_fetchingSprite = false;
        m_fetcherState = FetcherState::FetchTileMap;

        break;
    }
}

void gbtest::SpriteFetcher::tick()
{
    // Only tick if we're fetching a sprite
    if (m_fetchingSprite) {
        Fetcher::tick();
    }
}
