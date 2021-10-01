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
        m_currentTileData = m_vram.getVramTileData().getTileLineUsingFirstMethod(m_spriteToFetch.tileIndex,
                m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate + 16 - m_spriteToFetch.yPosition);

        // Continue to the next state
        m_fetcherState = FetcherState::PushFIFO;
        m_cyclesToWait = 4;

        break;

    case FetcherState::PushFIFO:
        // Fill the queue with the fetched pixels
        // We start from "8 - m_pixelFifo.getSize()" to prevent overwriting any pixel already in the FIFO
        for (uint8_t i = 8 - m_pixelFifo.getSize(); i-- > 0;) {
            const uint8_t lowBit = (m_currentTileData >> (8 + i)) & 0x1;
            const uint8_t highBit = (m_currentTileData >> i) & 0x1;

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
