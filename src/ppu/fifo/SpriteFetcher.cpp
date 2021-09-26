#include "SpriteFetcher.h"

gbtest::SpriteFetcher::SpriteFetcher(const gbtest::PPURegisters& ppuRegisters, const gbtest::VRAM& vram,
        gbtest::PixelFIFO& pixelFifo)
        : Fetcher(ppuRegisters, vram, pixelFifo)
        , m_fetchingSprite(false)
        , m_fetchedSpriteIdx(0)
{

}

void gbtest::SpriteFetcher::fetchSprite(uint8_t spriteIdx)
{
    m_fetchingSprite = true;
    m_fetchedSpriteIdx = spriteIdx;
}

bool gbtest::SpriteFetcher::isFetchingSprite() const
{
    return m_fetchingSprite;
}

uint8_t gbtest::SpriteFetcher::getFetchedSpriteIdx() const
{
    return m_fetchedSpriteIdx;
}

void gbtest::SpriteFetcher::executeState()
{
    switch (m_fetcherState) {
    case FetcherState::FetchTileMap: {
        // Fetch the tile map
        // TODO: Implement that

        // Continue to the next state
        m_fetcherState = FetcherState::FetchTileData;
        m_cyclesToWait = 2;

        break;
    }

    case FetcherState::FetchTileData:
        // Fetch the tile data
        // TODO: Implement that

        // Continue to the next state
        m_fetcherState = FetcherState::PushFIFO;
        m_cyclesToWait = 4;

        break;

    case FetcherState::PushFIFO:
        // TODO: Implement that
        m_fetchingSprite = false;
        m_fetcherState = FetcherState::FetchTileMap;

        break;
    }
}
