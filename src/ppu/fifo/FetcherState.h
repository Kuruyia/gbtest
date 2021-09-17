#ifndef GBTEST_FETCHERSTATE_H
#define GBTEST_FETCHERSTATE_H

namespace gbtest {

enum class FetcherState {
    FetchTileMap,
    FetchTileData,
    PushFIFO,
}; // enum class FetcherState

} // namespace gbtest

#endif //GBTEST_FETCHERSTATE_H
