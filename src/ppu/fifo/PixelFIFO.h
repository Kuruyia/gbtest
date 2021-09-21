#ifndef GBTEST_PIXELFIFO_H
#define GBTEST_PIXELFIFO_H

#include <array>

#include "FIFOPixelData.h"

namespace gbtest {

class PixelFIFO {

public:
    PixelFIFO();

    void push(FIFOPixelData&& pixelData);
    void pop(FIFOPixelData& pixelData);

    [[nodiscard]] bool empty() const;
    void clear();

private:
    std::array<FIFOPixelData, 8> m_fifo;
    size_t m_size;

}; // class PixelFIFO

} // namespace gbtest

#endif //GBTEST_PIXELFIFO_H
