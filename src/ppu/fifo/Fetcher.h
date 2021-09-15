#ifndef GBTEST_FETCHER_H
#define GBTEST_FETCHER_H

#include <deque>

#include "FetcherState.h"
#include "FIFOPixelData.h"

#include "../vram/VRAM.h"
#include "../PPURegisters.h"
#include "../../utils/Tickable.h"

namespace gbtest {

class Fetcher
        : public Tickable {

public:
    Fetcher(const PPURegisters& ppuRegisters, const VRAM& vram, std::deque<FIFOPixelData>& managedQueue);
    ~Fetcher() override = default;

    void setPaused(bool paused);
    [[nodiscard]] bool isPaused() const;

    virtual void resetState();
    virtual void beginScanline();
    virtual void beginFrame();

    virtual void executeState() = 0;

    void tick() override;

protected:
    FetcherState m_fetcherState;
    bool m_paused;
    unsigned m_cyclesToWait;

    const PPURegisters& m_ppuRegisters;
    const VRAM& m_vram;

    std::deque<FIFOPixelData>& m_managedQueue;
    std::deque<FIFOPixelData> m_fetchedPixels;

}; // class Fetcher

} // namespace Fetcher

#endif //GBTEST_FETCHER_H
