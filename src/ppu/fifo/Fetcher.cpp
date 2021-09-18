#include "Fetcher.h"

gbtest::Fetcher::Fetcher(const PPURegisters& ppuRegisters, const VRAM& vram, std::deque<FIFOPixelData>& managedQueue)
        : m_fetcherState(FetcherState::FetchTileMap)
        , m_paused(false)
        , m_cyclesToWait(0)
        , m_ppuRegisters(ppuRegisters)
        , m_vram(vram)
        , m_managedQueue(managedQueue)
{

}

void gbtest::Fetcher::setPaused(bool paused)
{
    m_paused = paused;
}

bool gbtest::Fetcher::isPaused() const
{
    return m_paused;
}

void gbtest::Fetcher::resetState()
{
    m_fetcherState = FetcherState::FetchTileMap;
    m_cyclesToWait = 0;
}

void gbtest::Fetcher::beginScanline()
{
    resetState();
}

void gbtest::Fetcher::beginFrame()
{
    beginScanline();
}

void gbtest::Fetcher::tick()
{
    // Don't do anything if the fetcher is paused
    if (m_paused) { return; }

    if (m_cyclesToWait == 0) {
        // Do the work
        executeState();
    }

    if (m_cyclesToWait > 0) {
        --m_cyclesToWait;
    }
}
