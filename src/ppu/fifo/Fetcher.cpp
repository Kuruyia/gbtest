#include "Fetcher.h"

gbtest::Fetcher::Fetcher(std::deque<FIFOPixelData>& managedQueue)
        : m_fetcherState(FetcherState::FetchTileMap)
        , m_paused(false)
        , m_cyclesToWait(0)
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

void gbtest::Fetcher::reset()
{
    m_fetcherState = FetcherState::FetchTileMap;
    m_cyclesToWait = 0;
}

void gbtest::Fetcher::tick()
{
    // Don't do anything if the fetcher is paused
    if (m_paused) { return; }

    if (m_cyclesToWait == 0) {
        // Do the work
        executeState();
    }

    --m_cyclesToWait;
}
