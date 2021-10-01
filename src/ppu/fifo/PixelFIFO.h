#ifndef GBTEST_PIXELFIFO_HPP
#define GBTEST_PIXELFIFO_HPP

#include <array>

#include "FIFOPixelData.h"
#include "../../utils/CircularBuffer.hpp"

namespace gbtest {

using PixelFIFO = CircularBuffer<FIFOPixelData, 8>;

} // namespace gbtest

#endif //GBTEST_PIXELFIFO_HPP
