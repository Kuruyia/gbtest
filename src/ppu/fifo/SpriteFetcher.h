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

    void executeState() override;

}; // class SpriteFetcher

} // namespace gbtest

#endif //GBTEST_SPRITEFETCHER_H
