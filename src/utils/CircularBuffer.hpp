#ifndef GBTEST_CIRCULARBUFFER_HPP
#define GBTEST_CIRCULARBUFFER_HPP

#include <cstddef>
#include <iterator>

namespace gbtest {

template<class ContainedItem, size_t BufferSize>
class CircularBuffer {

public:
    using RawBuffer = std::array<ContainedItem, BufferSize + 1>;

    CircularBuffer();

    void push(ContainedItem&& pixelData);
    void pop(ContainedItem& pixelData);

    [[nodiscard]] bool empty() const;
    [[nodiscard]] size_t getSize() const;
    void clear();

private:
    RawBuffer m_fifo;
    size_t m_size;

    typename RawBuffer::iterator m_readIterator;
    typename RawBuffer::iterator m_writeIterator;

    typename RawBuffer::iterator increaseIterator(typename RawBuffer::iterator iter);

}; // class CircularBuffer

template<class ContainedItem, size_t BufferSize>
gbtest::CircularBuffer<ContainedItem, BufferSize>::CircularBuffer()
        : m_size(0)
        , m_readIterator(m_fifo.begin())
        , m_writeIterator(m_fifo.begin())
{

}

template<class ContainedItem, size_t BufferSize>
void gbtest::CircularBuffer<ContainedItem, BufferSize>::push(ContainedItem&& pixelData)
{
    // Get the iterator after the current end iterator
    auto afterWriteIterator = increaseIterator(m_writeIterator);

    // Check that the array is not full
    if (afterWriteIterator != m_readIterator) {
        // Move the pixel to the array
        *m_writeIterator = pixelData;

        m_writeIterator = afterWriteIterator;
        ++m_size;
    }
    else {
        // TODO: What to do?
    }
}

template<class ContainedItem, size_t BufferSize>
void gbtest::CircularBuffer<ContainedItem, BufferSize>::pop(ContainedItem& pixelData)
{
    // Get the iterator after the current begin iterator
    auto afterReadIterator = increaseIterator(m_readIterator);

    if (m_readIterator != m_writeIterator) {
        // Move a pixel out of the array
        pixelData = *m_readIterator;

        m_readIterator = afterReadIterator;
        --m_size;
    }
    else {
        // TODO: What to do?
    }
}

template<class ContainedItem, size_t BufferSize>
bool gbtest::CircularBuffer<ContainedItem, BufferSize>::empty() const
{
    return m_size == 0;
}

template<class ContainedItem, size_t BufferSize>
size_t gbtest::CircularBuffer<ContainedItem, BufferSize>::getSize() const
{
    return m_size;
}

template<class ContainedItem, size_t BufferSize>
void gbtest::CircularBuffer<ContainedItem, BufferSize>::clear()
{
    m_size = 0;

    m_readIterator = m_fifo.begin();
    m_writeIterator = m_fifo.begin();
}

template<class ContainedItem, size_t BufferSize>
typename gbtest::CircularBuffer<ContainedItem, BufferSize>::RawBuffer::iterator
gbtest::CircularBuffer<ContainedItem, BufferSize>::increaseIterator(typename RawBuffer::iterator iter)
{
    // Increase the iterator
    std::advance(iter, 1);

    if (iter == m_fifo.end()) {
        // Loop the iterator if necessary
        iter = m_fifo.begin();
    }

    return iter;
}

} // namespace gbtest

#endif //GBTEST_CIRCULARBUFFER_HPP
