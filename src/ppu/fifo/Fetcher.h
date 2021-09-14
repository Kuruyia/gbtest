#ifndef GBTEST_FETCHER_H
#define GBTEST_FETCHER_H

#include <deque>

#include "FetcherState.h"
#include "FIFOPixelData.h"

#include "../../utils/Tickable.h"

namespace gbtest {

class Fetcher
        : public Tickable {

public:
    explicit Fetcher(std::deque<FIFOPixelData>& managedQueue);
    ~Fetcher() override = default;

    void setPaused(bool paused);
    [[nodiscard]] bool isPaused() const;

    virtual void reset();
    virtual void executeState() = 0;

    void tick() override;

protected:
    FetcherState m_fetcherState;
    bool m_paused;
    unsigned m_cyclesToWait;

    std::deque<FIFOPixelData>& m_managedQueue;
    std::deque<FIFOPixelData> m_fetchedPixels;

}; // class Fetcher

} // namespace Fetcher

#endif //GBTEST_FETCHER_H
