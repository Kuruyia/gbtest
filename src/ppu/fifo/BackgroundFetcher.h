#ifndef GBTEST_BACKGROUNDFETCHER_H
#define GBTEST_BACKGROUNDFETCHER_H

#include "Fetcher.h"
#include "PixelFIFO.h"

#include "../PPURegisters.h"
#include "../vram/VRAM.h"
#include "../vram/VRAMMapAttributesData.h"

namespace gbtest {

class BackgroundFetcher
        : public Fetcher {

public:
    BackgroundFetcher(const PPURegisters& ppuRegisters, const VRAM& vram, PixelFIFO& pixelFifo);
    ~BackgroundFetcher() override = default;

    void startFetchingWindow();
    [[nodiscard]] bool isFetchingWindow() const;

    void resetForSpriteFetch();

    void beginScanline() override;

    void executeState() override;
    void beginFrame() override;

private:
    uint8_t m_currentTileNumber;
    VRAMMapAttributesData m_currentTileAttributes;
    uint16_t m_currentTileData;

    uint8_t m_fetcherX;
    bool m_scanlineBeginSkip;

    bool m_fetchingWindow;
    uint8_t m_windowLineCounter;

    void fetchBackgroundTileMap();
    void fetchBackgroundTileData();

    void fetchWindowTileMap();
    void fetchWindowTileData();

}; // class BackgroundFetcher

} // namespace gbtest

#endif //GBTEST_BACKGROUNDFETCHER_H
