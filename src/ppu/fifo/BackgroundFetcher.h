#ifndef GBTEST_BACKGROUNDFETCHER_H
#define GBTEST_BACKGROUNDFETCHER_H

#include <deque>

#include "Fetcher.h"

#include "../PPURegisters.h"
#include "../vram/VRAM.h"

namespace gbtest {

class BackgroundFetcher
        : public Fetcher {

public:
    BackgroundFetcher(const PPURegisters& ppuRegisters, const VRAM& vram, std::deque<FIFOPixelData>& managedQueue);
    ~BackgroundFetcher() override = default;

    void beginScanline() override;

    void executeState() override;

private:
    uint8_t m_currentTileNumber;
    uint16_t m_currentTileData;

    uint8_t m_fetcherX;
    bool m_scanlineBeginSkip;

}; // class BackgroundFetcher

} // namespace gbtest

#endif //GBTEST_BACKGROUNDFETCHER_H
