#ifndef GBTEST_SPRITEFETCHER_H
#define GBTEST_SPRITEFETCHER_H

#include "Fetcher.h"
#include "PixelFIFO.h"

#include "../PPURegisters.h"
#include "../oam/OAMEntry.h"
#include "../vram/VRAM.h"

namespace gbtest {

class SpriteFetcher
        : public Fetcher {

public:
    SpriteFetcher(const PPURegisters& ppuRegisters, const VRAM& vram, PixelFIFO& pixelFifo);

    void fetchSprite(const OAMEntry& spriteToFetch, size_t oamIndex);
    void stopFetchingSprite();
    [[nodiscard]] bool isFetchingSprite() const;
    [[nodiscard]] const OAMEntry& getSpriteToFetch() const;

    void executeState() override;

    void tick() override;

private:
    bool m_fetchingSprite;
    OAMEntry m_spriteToFetch;
    size_t m_oamIndex;

    uint16_t m_currentTileData;

}; // class SpriteFetcher

} // namespace gbtest

#endif //GBTEST_SPRITEFETCHER_H
