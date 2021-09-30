#include "SpriteBuffer.h"

gbtest::SpriteBuffer::SpriteBuffer()
        : m_buffer()
        , m_size(0)
{

}

void gbtest::SpriteBuffer::push(const gbtest::OAMEntry& oamEntry)
{
    if (m_size < m_buffer.size()) {
        m_buffer[m_size] = oamEntry;
        ++m_size;
    }
}

const gbtest::OAMEntry& gbtest::SpriteBuffer::at(size_t idx) const
{
    return m_buffer.at(idx);
}

gbtest::OAMEntry& gbtest::SpriteBuffer::at(size_t idx)
{
    return m_buffer.at(idx);
}

const gbtest::SpriteBuffer::RawSpriteBuffer& gbtest::SpriteBuffer::getRawBuffer() const
{
    return m_buffer;
}

gbtest::SpriteBuffer::RawSpriteBuffer& gbtest::SpriteBuffer::getRawBuffer()
{
    return m_buffer;
}

size_t gbtest::SpriteBuffer::getSize() const
{
    return m_size;
}

void gbtest::SpriteBuffer::clear()
{
    m_size = 0;
}
