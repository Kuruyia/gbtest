#include "PixelFIFO.h"

gbtest::PixelFIFO::PixelFIFO()
        : m_size(0)
{

}

void gbtest::PixelFIFO::push(gbtest::FIFOPixelData&& pixelData)
{
    if (m_size < 8) {
        // Move the pixel to the array
        m_fifo.at(m_size) = pixelData;
        ++m_size;
    }
}

void gbtest::PixelFIFO::pop(gbtest::FIFOPixelData& pixelData)
{
    if (m_size > 0) {
        // Move a pixel out of the array
        pixelData = m_fifo.at(m_fifo.size() - m_size);
        --m_size;
    }
}

bool gbtest::PixelFIFO::empty() const
{
    return m_size == 0;
}

void gbtest::PixelFIFO::clear()
{
    m_size = 0;
}
