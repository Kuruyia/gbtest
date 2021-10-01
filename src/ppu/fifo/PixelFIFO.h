#ifndef GBTEST_PIXELFIFO_HPP
#define GBTEST_PIXELFIFO_HPP

#include <queue>

#include "FIFOPixelData.h"

namespace gbtest {

using PixelFIFO = std::queue<FIFOPixelData>;

} // namespace gbtest

#endif //GBTEST_PIXELFIFO_HPP
