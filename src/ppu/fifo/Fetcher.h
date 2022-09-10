#ifndef GBTEST_FETCHER_H
#define GBTEST_FETCHER_H

#include "FetcherState.h"
#include "FIFOPixelData.h"
#include "PixelFIFO.h"

#include "../vram/VRAM.h"
#include "../PPURegisters.h"
#include "../../utils/Tickable.h"

namespace gbtest {

class Fetcher
        : public Tickable {

public:
    Fetcher(const PPURegisters& ppuRegisters, const VRAM& vram, PixelFIFO& pixelFifo);
    ~Fetcher() override = default;

    virtual void setCGBMode(bool cgbMode);
    [[nodiscard]] bool isCGBMode() const;

    void setPaused(bool paused);
    [[nodiscard]] bool isPaused() const;

    virtual void resetState();
    virtual void beginScanline();
    virtual void beginFrame();

    virtual void executeState() = 0;

    void tick(bool isDoubleSpeedTick) override;

protected:
    static uint8_t getPixelFromTileData(uint16_t tileData, uint8_t bitNb, bool xFlipped);

    FetcherState m_fetcherState;
    bool m_cgbMode;
    bool m_paused;
    unsigned m_cyclesToWait;

    const PPURegisters& m_ppuRegisters;
    const VRAM& m_vram;

    PixelFIFO& m_pixelFifo;

}; // class Fetcher

} // namespace Fetcher

#endif //GBTEST_FETCHER_H
