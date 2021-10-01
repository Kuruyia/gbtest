#include "SpriteFetcher.h"

gbtest::SpriteFetcher::SpriteFetcher(const gbtest::PPURegisters& ppuRegisters, const gbtest::VRAM& vram,
        gbtest::PixelFIFO& pixelFifo)
        : Fetcher(ppuRegisters, vram, pixelFifo)
        , m_fetchingSprite(false)
        , m_spriteToFetch()
        , m_currentTileData(0)
{

}

void gbtest::SpriteFetcher::fetchSprite(const OAMEntry& spriteToFetch)
{
    m_fetchingSprite = true;
    m_spriteToFetch = spriteToFetch;
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

    case FetcherState::FetchTileData:
        // Fetch the tile data
        uint8_t lineNumber;

        // Select the line number depending on the Y flip flag
        if (m_spriteToFetch.flags.yFlip == 0) {
            lineNumber = m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate + 16 - m_spriteToFetch.yPosition;
        }
        else {
            lineNumber = 7 - (m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate + 16 - m_spriteToFetch.yPosition);
        }

        m_currentTileData = m_vram.getVramTileData().getTileLineUsingFirstMethod(m_spriteToFetch.tileIndex, lineNumber);

        // Continue to the next state
        m_fetcherState = FetcherState::PushFIFO;
        m_cyclesToWait = 4;

        break;

    case FetcherState::PushFIFO:
        // Fill the queue with the fetched pixels
        // We start from "8 - m_pixelFifo.getSize()" to prevent overwriting any pixel already in the FIFO
        for (uint8_t i = 8 - m_pixelFifo.getSize(); i-- > 0;) {
            // Change the order on which we put pixels in the FIFO depending on the X flip flag
            uint8_t highBit, lowBit;

            if (m_spriteToFetch.flags.xFlip == 0) {
                lowBit = (m_currentTileData >> (8 + i)) & 0x1;
                highBit = (m_currentTileData >> i) & 0x1;
            }
            else {
                lowBit = (m_currentTileData >> (15 - i)) & 0x1;
                highBit = (m_currentTileData >> (7 - i)) & 0x1;
            }

            highBit &= 0x01;
            lowBit &= 0x01;

            m_pixelFifo.push(FIFOPixelData(
                    (highBit << 1) | lowBit,
                    m_spriteToFetch.flags.dmgPaletteNumber,
                    0,
                    m_spriteToFetch.flags.bgAndWindowsOverObj == 1));
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
