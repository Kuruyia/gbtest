#ifndef GBTEST_SPRITEFETCHER_H
#define GBTEST_SPRITEFETCHER_H

#include "Fetcher.h"
#include "PixelFIFO.h"

#include "../PPURegisters.h"
#include "../vram/VRAM.h"

namespace gbtest {

class SpriteFetcher
        : public Fetcher {

public:
    SpriteFetcher(const PPURegisters& ppuRegisters, const VRAM& vram, PixelFIFO& pixelFifo);

    void fetchSprite(uint8_t spriteIdx);
    [[nodiscard]] bool isFetchingSprite() const;
    [[nodiscard]] uint8_t getFetchedSpriteIdx() const;

    void executeState() override;

private:
    bool m_fetchingSprite;
    uint8_t m_fetchedSpriteIdx;

}; // class SpriteFetcher

} // namespace gbtest

#endif //GBTEST_SPRITEFETCHER_H
